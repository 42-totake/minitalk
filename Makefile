# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/12 17:59:18 by totake            #+#    #+#              #
#    Updated: 2025/07/17 17:44:45 by totake           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = all_targets
NAME_SERVER = server
NAME_CLIENT = client

SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(NAME_SERVER) $(NAME_CLIENT)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER) $(LIBFT)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT) $(LIBFT)

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
