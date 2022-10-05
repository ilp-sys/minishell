/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:32:03 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/05 16:34:45 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct	s_env_list
{
	struct s_env	*head;
	struct s_env	*tail;
}	t_env_list;

/* env.c */
int		parse_env(t_env_list **envl, char **envp);
t_env	*get_env(t_env_list *envl, char *key);;
int		set_env(t_env_list **envl, t_env *env);
int		del_env(t_env_list **envl, char *key);
t_env	*new_env(char *key_val);

#endif
