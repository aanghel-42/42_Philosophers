# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/24 15:54:46 by aanghel           #+#    #+#              #
#    Updated: 2022/07/14 17:21:50 by aanghel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

SRCS= parsing.c \
	  threads.c \
	  utils.c \
	  activity.c \

OBJS= $(SRCS:%.c=%.o)

CC= gcc

FLAGS= -Wall -Werror -Wextra #-fsanitize=address

all: $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(FLAGS) $(SRCS) philo.c -o $(NAME)

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean flean re