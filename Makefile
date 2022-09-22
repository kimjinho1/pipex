# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 13:02:19 by jinhokim          #+#    #+#              #
#    Updated: 2022/09/22 15:17:17 by jinhokim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex

SRCS			= ./mandatory/pipex.c \
				./mandatory/utils.c

BONUS_SRCS 		= ./bonus/pipex_bonus.c \
				./bonus/utils_bonus.c \
				./bonus/gnl_bonus.c

HEADER			= ./mandatory/pipex.h

BONUS_HEADER	= ./bonus/pipex_bonus.h

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -f

LIBS			= -L ./ft_printf -lftprintf

OBJS			= $(SRCS:.c=.o)

BONUS_OBJS		= $(BONUS_SRCS:.c=.o)

$(NAME):		$(OBJS) $(HEADER)
					@make all -C ./ft_printf
					@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

bonus:			$(BONUS_OBJS) $(BONUS_HEADER)
					@make all -C ./ft_printf
					@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(NAME) $(LIBS)

all:			$(NAME)

clean:
				@$(RM) $(OBJS)
				@$(RM) $(BONUS_OBJS)
					@make fclean -C ./ft_printf

fclean:			clean
					@$(RM) $(NAME) $(OBJS)

re:				fclean all

.PHONY:			bonus all clean fclean re
