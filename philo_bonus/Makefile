# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/15 14:22:01 by hyap              #+#    #+#              #
#    Updated: 2022/08/25 14:37:53 by hyap             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ${wildcard srcs/*.c}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = philo

RM = rm -f

FSANITIZE = -fsanitize=thread

all: ${NAME}

${NAME}: ${SRCS}
	${CC} ${CFLAGS} -pthread -I includes ${SRCS} -o ${NAME}

clean:
	${RM} ${NAME}

fclean:
	${RM} ${NAME}

sanitize:
	${CC} ${CFLAGS} ${FSANITIZE} -I includes ${SRCS} -o ${NAME}

re: clean all

.PHONY: all clean re