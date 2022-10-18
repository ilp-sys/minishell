# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 19:45:18 by hyeongki          #+#    #+#              #
#    Updated: 2022/10/17 18:34:55 by hyeongki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
#CFLAGS = -Wall -Wextra -Werror
CFLAGS = -g -fsanitize=address
SRCS_PATH = ./source/
SRCS_NAME = main.c ft_echo.c ft_pwd.c ft_cd.c ft_export.c ft_unset.c ft_env.c ft_exit.c built_in.c env_01.c env_02.c env_03.c error.c util.c signal.c execute.c parser.c scanner.c scanner_utils.c token_utils.c tree_utils.c execute_pipe.c execute_utils.c
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS = $(SRCS:.c=.o)
RM = rm -rf
AR = ar rcs
NAME = minishell
READLINE_LIB = -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC = -I/opt/homebrew/opt/readline/include
LIBFT_PATH = ./libft/
LIBFT = libft.a
LIBFT_FLAG = $(LIBFT_PATH)$(LIBFT)

# Colors
GREEN = \x1b[32m
RED = \x1b[31m
RESET = \x1b[0m

%.o : %.c
	@$(CC) $(CFLAGS) -c $< $(READLINE_INC) -o $@
	@echo "$(GREEN).$(RESET)\c"

all : $(NAME)

$(NAME) :  $(OBJS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $^ $(READLINE_LIB) $(LIBFT_FLAG) -o $@
	@echo "$@: $(GREEN)$@ was created$(RESET)"

clean :
	@make clean -C $(LIBFT_PATH)
	@$(RM) $(OBJS)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean : clean
	@$(RM) $(LIBFT_PATH)$(LIBFT)
	@$(RM) $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re : fclean all

.PHONY :
	all clean fclean re
