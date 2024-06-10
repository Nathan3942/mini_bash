# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 04:50:58 by njeanbou          #+#    #+#              #
#    Updated: 2024/06/10 17:13:04 by njeanbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = $(wildcard srcs/ms_utils/*.c srcs/ms_parsing/*.c srcs/ms_exec/*.c srcs/ms_cmds/*.c srcs/ms_errors/*.c main.c)

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Werror -Wextra -Wall -fsanitize=address -static-libsan -g	

#-fsanitize=address -static-libsan
RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
				@${MAKE} -C ./ms_libft
				@${CC} ${CFLAGS} ${OBJS} ./ms_libft/libft.a -o ${NAME} -lreadline

clean:
				@${MAKE} -C ./ms_libft fclean
				@${RM} ${OBJS}

fclean:	clean	
				@${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re