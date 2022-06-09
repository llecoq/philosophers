# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/04 14:53:59 by llecoq            #+#    #+#              #
#    Updated: 2021/10/21 15:28:29 by llecoq           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	=	main.c\
				utils/error.c\
				utils/ft_atoi.c\
				utils/print_action.c\
				utils/sleep.c\
				utils/time.c\
				utils/life_vs_death.c\
				utils/mutex.c\
				parsing/parser.c\
				execution/executor.c\
				execution/actions.c

SRCSPATH= srcs/

OBJS_FILES = $(SRCS_FILES:.c=.o)

OBJSPATH= .objs/

SRCS = $(addprefix $(SRCSPATH),$(SRCS_FILES))

OBJS = $(addprefix $(OBJSPATH),$(OBJS_FILES))

NAME	= philo

CC		= gcc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror -g -pthread
#  -fsanitize=thread 

DIR		=	.objs/parsing\
			.objs/execution\
			.objs/utils

$(OBJSPATH)%.o:		$(SRCSPATH)%.c includes/philosophers.h includes/enum.h
			@mkdir -p $(OBJ_PATH) $(DIR)
			$(CC) $(CFLAGS) -c $< -o $@ -I includes/

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJSPATH)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all $(NAME)

.PHONY:		all clean fclean re
