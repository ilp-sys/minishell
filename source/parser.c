/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:05:29 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/11 15:59:17 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

#include "../include/parser.h"
#include "../libft/libft.h"

t_tree	*get_new_node(int type, int flag, t_token *toks)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(t_tree));
	node->type = type;
	node->flag = flag;
	node->toks = toks;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	parse_list(t_toks *toks, t_tree *root)
{
	int				success;
	const t_toks	*origin = toks;

	success = 0;
	while (*toks)
	{
		if ((*toks)->type == OP && !(root->flag & PAREN)\
				(!ft_strncmp(toks->text, "&&", 2) || \
				 !ft_strncmp(toks->text, "||", 2)))
			success = 1;
		else if ((*toks)->type == OP && \
				(!ft_strncmp(toks->text, "(", 1) || \
				  !ft_strncmp(toks->text, "(", 1)))
			(root->flag) ^= PAREN;
		*toks = (root->flag & LEFT) ? (*toks)->prev : (*toks)->next;
	}
	if (root->flag & PAREN)
		err_exit("syntax err");
	if (!success)
	{
		*toks = origin;
		toks->type = PIPELINE;
	}
}

void	parser(t_toks *toks, t_tree *root)
{
	t_tree	*left = NULL;
	t_tree	*right = NULL;;

	if ((root->flag) & TERM)
		return ;
	if (toks->type == LIST)
		parse_list(toks, root);
	if (toks->type == PIPELINE)
		parse_pipeline(toks, root);
	if (toks->type == CMD)
		parser_cmd(toks, root);
	root->left = left;
	root->right = right;
	parser(toks->prev, root->right);
	parser(toks->next, root->left);
}
