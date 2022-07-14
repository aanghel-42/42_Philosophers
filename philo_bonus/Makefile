# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/08 23:37:46 by aanghel           #+#    #+#              #
#    Updated: 2022/07/08 23:41:44 by aanghel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo_bonus

SRC=

OBJS= $(SRC%.c=%.o)

CC= gcc

FLAGS= -Wall -Werror -Wextra

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) philo_bonus.c -o $(NAME)
	
all: $(NAME)

clean:
	rm -rf $(OBJS)
	
fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re