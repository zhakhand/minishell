GREEN=\033[32m
YELLOW=\033[33m
RED=\033[31m
BLUE=\033[34m
BACK=\033[42m
BOLD=\033[1m
RESET=\033[0m

SRCS = parser.c utils.c tokenizer.c data.c env_table.c env_table_utils.c expansion.c vars_tokens_tokenizer.c expansion_2.c

HEAD = parser.h

NAME = parser

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
		@${CC} ${CFLAGS} ${OBJS} -o $@ ./libft/libft.a -lreadline
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