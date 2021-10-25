# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/17 18:33:58 by vbackyet          #+#    #+#              #
#    Updated: 2021/10/22 19:49:42 by vbackyet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
NAME_BONUS = 	philo_bonus


CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror

SRCS_MAIN		=	check.c common_utils.c common_utils2.c common_utils3.c utils_for_check.c
SRCS_BONUS		=	philo_bonus.c common_utils.c common_utils2.c common_utils3.c utils_for_check.c
OBJS		=	$(SRCS_MAIN:.c=.o)
OBJS_BONUS		=	$(SRCS_BONUS:.c=.o)


$(NAME)	:	$(OBJS)
			$(CC) $(FLAGS) -pthread -o $(NAME) $(OBJS)

$(NAME_BONUS)	:	$(OBJS_BONUS)
			$(CC) $(FLAGS) -pthread -o $(NAME_BONUS) $(OBJS_BONUS)


all		: 	$(NAME)


bonus 	:	$(NAME_BONUS)


%.o		:	%.c
			$(CC) $(FLAGS) -o $@ -c $<

clean	:	
				rm -rf $(OBJS)
				rm -rf $(OBJS_BONUS)

fclean	:	clean
				rm -rf $(NAME)
				rm -rf $(NAME_BONUS)

re		:	fclean all

.PHONY	:	all clean fclean re bonus