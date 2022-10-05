/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:12:59 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/04 21:43:49 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

int	ft_pwd(int argc, char **argv, char **envp)
{
	char	buf[BUFSIZ];

	(void)argc;
	(void)argv;
	(void)envp;
	if (getcwd(buf, BUFSIZ) == NULL)
		return (EXIT_FAILURE);
	else
		printf("%s\n", buf);
	return (EXIT_SUCCESS);
}
