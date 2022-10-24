/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:18:21 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/23 21:49:29 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/termios.h>
# include <termios.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>

# include "../libft/include/libft.h"
# include "env.h"
# include "parser.h"
# include "redir.h"

# define SHELL_NAME "fdf"

# define SUCCESS 1
# define FAILURE 0

# define TRUE 1
# define FALSE 0

# define HAN 0
# define DFL 1
# define IGN 2

# define CMD_NOT_FOUND 127

extern int	g_exit_code;

typedef void	(*t_tree_func)(t_tree *tree, t_env_list *envl);

typedef struct	s_lists
{
	struct s_env_list		*envl;
	struct s_redir_list		*redirl;
	struct s_heredoc_list	*heredocl;
}	t_lists;

/* main.c */
void	processing(t_tree *root, t_lists *list, int *prev_fd, int pipe_fd[2]);
char	**convert_toks(t_tree *root, t_lists *list);
void	minishell(char **envp);

/* error.c */
void	put_error_arg(char *cmd, char *arg, char *strerr);
void	put_error_cmd(char *cmd, char *strerr);
void	put_error_arg_exit(char *cmd, char *arg, char *strerr, int exit_code);
void	put_error_cmd_exit(char *cmd, char *strerr, int exit_code);

/* util.c */
int		get_argc(char **argv);
void	swap_str(char **a, char **b);

/* signal.c */
void	signal_handler(int sig);
void	set_signal(int sig_int, int sig_quit);

/* execute.c */
void	execute_command(char **argv, t_lists *list, pid_t pid);
void	execve_command(char **argv, t_env_list *envl, pid_t pid);
void	execute_subshell(char **envp);

/* execute_pipe.c */
void		excute_pipe(t_tree *node, t_lists *list, int pipe_in, int pipe_out);

/* execute_utils.c */
pid_t	ft_fork(void);
void	wait_child(void);
char	*get_command(char **paths, char *cmd);
int		dir_check(char *path, char *cmd);

#endif
