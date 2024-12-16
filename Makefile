GREEN=\033[32m
YELLOW=\033[33m
RED=\033[31m
BLUE=\033[34m
BACK=\033[42m
BOLD=\033[1m
RESET=\033[0m

SRCS = parser.c utils.c tokenizer.c data.c env_table.c

HEAD = parser.h

NAME = parser

CC = cc

RM = rm -f

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra -g

all: ${NAME}

%.o:	%.c
		@echo "${BLUE}${BOLD}Compiling $<${RESET}"
		@${CC} ${CFLAGS} -c  $< -o $@

${NAME}: $(OBJS)
		@${CC} ${CFLAGS} ${OBJS} -o $@ -lreadline
		@echo "${BACK}${RED}${BOLD} Successfuly built ${NAME} ${RESET}"

clean:
		@echo "${YELLOW}${BOLD}Deleting object files${RESET}" 
		@${RM} ${OBJS}

fclean: clean
		@echo "${RED}${BOLD}Deleting executable${RESET}"
		@${RM} philo

re:		fclean all

.PHONY:	all clean fclean re