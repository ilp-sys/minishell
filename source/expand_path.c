/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:17:41 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/20 20:07:40 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>

#include "../libft/include/libft.h"
#include "../include/executor.h"

static t_list	*make_pattern(char *text)
{
	int		i;
	int		found;
	char	flag;
	t_list	*pattern;

	i = 0;
	flag = 0;
	found = 0;
	pattern = NULL;
	while (text[i])
	{
		ctl_quote_flag(&flag, text[i]);
		if (!(flag & S_QUOTE + D_QUOTE) && text[i] == '*')
		{
			if (i != 0)
				ft_lstadd_back(&pattern, \
						ft_lstnew(ft_strndup(text + found, i - found)));
			ft_lstadd_back(&pattern, \
					ft_lstnew(ft_strndup("*", 1)));
			while (text[i + 1] == '*')
				i++;
			found = i;
		}
		i++;
	}
	if (found != 0 && (found != i))
		ft_lstadd_back(&pattern, \
				ft_lstnew(ft_strndup(text + found, i - found)));
	return (pattern);
}

#include <stdio.h>
static int	match_pattern(t_list *pattern, char *str)
{
	int	len;
	int	flag;

	flag = 0;
	while (pattern)
	{
		//printf("pattern match with (%s) and (%s)\n", pattern->content, str);
		if (ft_strcmp(pattern->content, "*") == 0)
		{
			flag = 1;
		}
		else
		{
			len = ft_strlen(pattern->content);
			if (flag)
			{
				str = ft_strnstr(str, pattern->content, len);
				if (str == NULL)
					return (0);
			}
			else
			{
				if (ft_strncmp(str, pattern->content, len))
					return (0);
			}
			str += len;
			flag = 0;
		}
		pattern = pattern->next;
	}
	if (!flag && *str)
		return (0);
	return (1);
}

static t_list	*find_matches(t_list *pattern)
{
	DIR				*d;
	t_list			*matches;
	struct dirent	*dirent;

	matches = NULL;
	d = opendir(".");
	if (d == NULL)
		err_exit("dir open failed");
	while (1)
	{
		dirent = readdir(d);
		if (dirent == NULL)
			break ;
		if (ft_strncmp(dirent->d_name, ".", 1) == 0)
			continue ;
		if (match_pattern(pattern, dirent->d_name))
			//ft_lstadd_back(&matches, ft_lstnew(dirent->d_name));
			ft_lstadd_back(&matches, ft_lstnew(ft_strdup(dirent->d_name)));
	}
	closedir(d);
	return (matches);
}

static t_token	*insert_matches(t_token *toks, t_list *matches)
{
	t_token	*new;
	t_token	*last;

	new = NULL;
	while (matches)
	{
		tok_add_back(&new, get_new_token(WORD, matches->content));
		matches = matches->next;
	}
	if (new == NULL)
		return (toks);
	last = get_last_token(new);
	new->prev = toks->prev;
	last->next = toks->next;
	if (toks->prev)
		toks->prev->next = new;
	if (toks->next)
		toks->next->prev = get_last_token(new);
	free(toks->text);
	free(toks);
	return (last);
}

void	print_pattern(t_list *pattern)
{
	if (!pattern)
		return ;
	printf("\ncheck pattern\n");
	while (pattern)
	{
		printf("%s\n", pattern->content);
		pattern = pattern->next;
	}
}

void	expand_pathname(t_tree *root)
{
	t_token	*toks;
	t_list	*pattern;
	t_list	*matches;

	toks = root->toks;
	while (toks)
	{
		if (toks->type == WORD)
		{
			pattern = make_pattern(toks->text);
			print_pattern(pattern);
			matches = find_matches(pattern);
			//insert_matches(&toks, matches);
			toks = insert_matches(toks, matches);
		}
		toks = toks->next;
	}
	ft_lstclear(&pattern, free);
	ft_lstclear(&matches, NULL);
}
