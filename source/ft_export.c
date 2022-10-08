/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:41:23 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/08 16:48:36 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"

static void	swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	sort_env(t_env_list **envl)
{
	t_env	*end;
	t_env	*cur;
	char	*tmp;

	if (!*envl)
		return (0);
	end = (*envl)->tail;
	while (end != (*envl)->head)
	{
		cur = (*envl)->head;
		while (cur->next)
		{
			if (ft_strcmp(cur->key, cur->next->key) > 0)
			{
				swap_str(&cur->key, &cur->next->key);
				swap_str(&cur->value, &cur->next->value);
			}
			cur = cur->next;
		}
		end = end->prev;
	}
	return (1);
}

static int	print_export(t_env_list *envl)
{
	t_env	*env;

	if (!envl)
		return (0);
	env = envl->head;
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}	
	return (1);
}

static int	key_vaildation(char *key)
{
	while (*key)
	{
		if (!ft_isalnum(*key))
			return (0);
		key++;
	}
	return (1);
}

int	ft_export(int argc, char **argv, t_env_list *envl)
{
	char	**ret;
	t_env	*new;

	if (argc == 1)
	{
		if (!sort_env(&envl))
			return (EXIT_FAILURE);
		if (!print_export(envl))
			return (EXIT_FAILURE);
	}
	else
	{
		new = new_env(argv[0]);
		if (!key_vaildation(new->key))
			ft_puterr(ft_strjoin(ft_strjoin(SHELL_NAME": export: `", \
							new->key), "': not a vali identifier\n"));
		if (!set_env(&envl, new_env(argv[1])))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
