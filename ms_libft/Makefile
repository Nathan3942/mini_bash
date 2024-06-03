# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 16:19:31 by njeanbou          #+#    #+#              #
#    Updated: 2024/04/02 05:15:18 by njeanbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 				= $(wildcard *.c)

OBJS 				= $(SRCS:.c=.o)

NAME 				= libft.a
CC 					= gcc
CFLAGS 				= -Wall -Wextra -Werror
LIBC 				= ar rcs
RM 					= rm -f

.c.o: 
					${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:			${OBJS}
					${LIBC} ${NAME} ${OBJS}

all: 				${NAME}

clean:				
					${RM} ${OBJS} ${OBJSB}

fclean:				clean
					${RM} ${NAME} ${bonus}

re:					fclean all

.PHONY : all clean fclean re

