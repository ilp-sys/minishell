/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:05:29 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/07 17:05:22 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "../include/parser.h"

void	parser(t_token *toks, t_tree **root)
{

}

#include <stdio.h>
#include <readline/readline.h>

void	print_toks(t_token *toks)
{
	while (toks)
	{
		printf("[%d]%s->", toks->type, toks->text);
		toks = toks->next;
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	t_token		*toks;
	t_tree		*root;
	char		*input;

	toks = NULL;
	input = readline("input>> ");
	scanner(&toks, input);
	parser(toks, &root);
	print_toks(toks);
	system("leaks a.out");
	free(input);
	return (0);
}
