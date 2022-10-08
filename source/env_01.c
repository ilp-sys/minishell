/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:30:46 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/08 23:21:52 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/env.h"

t_env	*new_env(char *key_val)
{
	t_env	*new;
	char	*equl;

	if (!key_val)
		return (NULL);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	equl = ft_strchr(key_val, '=');
	if (equl)
	{
		new->key = ft_strndup(key_val, equl - key_val);
		new->value = ft_strdup(equl + 1);
	}
	else
	{
		new->key = ft_strdup(key_val);
		new->value = NULL;
	}
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	del_env(t_env_list **envl, char *key)
{
	t_env	*env;

	env = get_env(*envl, key);
	if (!env)
		return (FAILURE);
	if (env == (*envl)->head)
	{
		env->next->prev = NULL;
		(*envl)->head = env->next;
	}
	else if (env == (*envl)->tail)
	{
		env->prev->next = NULL;
		(*envl)->tail = env->prev;
	}
	else
	{
		env->prev->next = env->next;
		env->next->prev = env->prev;
	}
	free_env(env);
	return (SUCCESS);
}

int	set_env(t_env_list **envl, t_env *new)
{
	if (!new)
		return (FAILURE);
	if (!*envl)
	{
		*envl = (t_env_list *)malloc(sizeof(t_env_list));
		if (!*envl)
			return (FAILURE);
		(*envl)->head = new;
		(*envl)->tail = new;
	}
	else if (get_env(*envl, new->key))
	{
		if (replace_env(envl, new) == FAILURE)
			return (FAILURE);
	}
	else
	{
		(*envl)->tail->next = new;
		new->prev = (*envl)->tail;
		(*envl)->tail = new;
	}
	return (SUCCESS);
}

t_env	*get_env(t_env_list *envl, char *key)
{
	t_env	*env;

	env = envl->head;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	parse_env(t_env_list **envl, char **envp)
{
	if (!envp)
		return (FAILURE);
	while (*envp)
	{
		if (set_env(envl, new_env(*envp)) == FAILURE)
			return (FAILURE);
		envp++;
	}
	return (SUCCESS);
}
