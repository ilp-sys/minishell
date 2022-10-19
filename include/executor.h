/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:20:56 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/19 18:44:13 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "parser.h"

//syntax.c
void	check_syntax(t_tree *root);

//expander.c
void	expand(t_tree *root, t_env_list *envl);
void	slit_field(t_tree *root);
void	expand_pathname(t_tree *root);
void	quote_removal(t_tree *root);

//expand_env.c
void	expand_env(t_tree *root, t_env_list *envl);
