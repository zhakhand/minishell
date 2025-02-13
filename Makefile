GREEN=\033[32m
YELLOW=\033[33m
RED=\033[31m
BLUE=\033[34m
BACK=\033[42m
BOLD=\033[1m
RESET=\033[0m

SRCS = minishell.c parser/parser.c parser/utils.c parser/tokenizer.c parser/quoted_tokens.c \
		parser/data.c parser/env_table.c parser/env_table_utils.c parser/cmd_table_utils.c \
		parser/expansion.c parser/vars_tokens_tokenizer.c parser/expansion_2.c parser/clean_up_2.c \
		parser/expansion_3.c parser/build_cmd_table.c parser/built_in_check.c parser/tokenizer_3.c \
		parser/errors.c parser/clean_up.c parser/signals.c parser/tokenizer_2.c \
		exec/exec.c exec/execve.c exec/exec_utils.c exec/envp.c exec/exec_child.c \
		buildins/buildins_utils.c buildins/echo.c buildins/pwd.c buildins/env.c \
		buildins/unset.c buildins/export.c buildins/export_utils.c buildins/export_utils_2.c \
		buildins/changedir.c buildins/ft_exit.c buildins/cd_utils.c buildins/buildins_utils_2.c \
		heredoc/heredoc.c heredoc/heredoc_clean.c heredoc/heredoc_expansion.c \
		exec/redirects.c exec/redirects_in.c exec/redirects_out.c exec/redirects_prepare.c 
		 
		 
		
HEAD = parser.h minishell.h

NAME = minishell

CC = cc

RM = rm -f

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra -g

all: ${NAME}

libft:
		make -C libft

%.o:	%.c
		@echo "${BLUE}${BOLD}Compiling $<${RESET}"
		@${CC} ${CFLAGS} -Ilibft -c  $< -o $@

${NAME}: $(OBJS)
		@${MAKE} -s -C libft
		@${CC} ${CFLAGS} ${OBJS} -o $@ libft/libft.a -lreadline
		@echo "${BACK}${RED}${BOLD} Successfuly built ${NAME} ${RESET}"


clean:
		@echo "${YELLOW}${BOLD}Deleting object files${RESET}" 
		@make clean -s -C libft
		@${RM} ${OBJS}

fclean: clean
		@echo "${RED}${BOLD}Deleting executable${RESET}"
		@${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re