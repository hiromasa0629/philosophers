# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/15 14:22:01 by hyap              #+#    #+#              #
#    Updated: 2022/08/13 09:57:37 by hyap             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ${wildcard srcs/*.c}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

FSANITIZE = -fsanitize=thread

NAME = philo

RM = rm -f

all: ${NAME}

${NAME}: ${SRCS}
	${CC} ${CFLAGS} ${FSANITIZE} -pthread -I includes ${SRCS} -o ${NAME}

thread:
	${CC} ${CFLAGS} ${FSANITIZE} -pthread -I includes ${SRCS} -o ${NAME}

clean:
	${RM} ${NAME}

fclean:
	${RM} ${NAME}

sanitize:
	${CC} ${CFLAGS} ${FSANITIZE} -I includes ${SRCS} -o ${NAME}

re: clean all

.PHONY: all clean re