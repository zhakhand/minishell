GREEN=\033[32m
YELLOW=\033[33m
RED=\033[31m
BLUE=\033[34m
BACK=\033[42m
BOLD=\033[1m
RESET=\033[0m

SRCS = minishell.c parser/parser.c parser/utils.c parser/tokenizer.c parser/data.c parser/env_table.c parser/env_table_utils.c \
		parser/expansion.c parser/vars_tokens_tokenizer.c parser/expansion_2.c parser/expansion_3.c parser/build_cmd_table.c \
		parser/built_in_check.c parser/errors.c parser/clean_up.c \
		exec/exec_new.c exec/exec.c exec/exec_utils.c exec/redirects.c exec/envp.c \
		buildins/buildins_utils.c buildins/echo.c buildins/pwd.c buildins/env.c \
		buildins/unset.c buildins/export.c buildins/ft_exit.c\
		buildins/changedir.c \
		 
		
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