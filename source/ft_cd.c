/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:16:30 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/10 12:22:30 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

#define HOME 1
#define OLDPWD 2

static int	put_cd_error(char *arg, char *path, int flag)
{
	if (flag == HOME)
		put_error_cmd(arg, "HOME not set");
	else if (flag == OLDPWD)
		put_error_cmd(arg, "OLDPWD not set");
	else
		put_error_arg(arg, path, strerror(errno));
	return (EXIT_FAILURE);
}

static int	cd_path(char *path, t_env_list *envl, int flag)
{
	char	*tmp;
	int		ret;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("OLDPWD=", pwd);
	ret = chdir(path);
	if (ret != -1)
	{
		set_env(&envl, new_env(tmp));
		free(tmp);
		free(pwd);
		pwd = getcwd(NULL, 0);
		tmp = ft_strjoin("PWD=", pwd);
		set_env(&envl, new_env(tmp));
	}
	if (flag == OLDPWD)
		printf("%s\n", pwd);
	free(tmp);
	free(pwd);
	return (ret);
}

int	ft_cd(int argc, char **argv, t_env_list *envl)
{
	t_env	*env;
	char	*path;
	int		flag;

	(void)argc;
	env = NULL;
	path = NULL;
	flag = 0;
	if (argv[1] == NULL || ft_strcmp(argv[1], "~") == 0)
	{
		env = get_env(envl, "HOME");
		flag = HOME;
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		env = get_env(envl, "OLDPWD");
		flag = OLDPWD;
	}
	if (env)
		path = env->value;
	else
		path = argv[1];
	if (cd_path(path, envl, flag) == -1)
		return (put_cd_error(argv[0], path, flag));
	return (EXIT_SUCCESS);
}
