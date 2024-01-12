# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 12:51:12 by pnamnil           #+#    #+#              #
#    Updated: 2024/01/11 09:21:47 by pnamnil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

MLX_DIR = minilibx
LIB_DIR = libft
INCLUDES = 	-I$(LIB_DIR)/includes \
			-I$(MLX_DIR)
			
LINK_LIB = -L$(LIB_DIR) -lft -L$(MLX_DIR) -lmlx
FRAMEWORK = -framework OpenGL -framework AppKit

CC = cc
# CFLAGS = -Wall -Werror -Wextra $(INCLUDES) -g -fsanitize=address
CFLAGS = $(INCLUDES) -g -fsanitize=address

# SRCS = srcs/main.c \
# 		srcs/draw.c
		
SRCS = srcss/main.c \
		
OBJS = $(SRCS:.c=.o)

HEADER = srcs/cub3d.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(MAKE) -C $(LIB_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(LINK_LIB) $(FRAMEWORK) $(OBJS) -o $(NAME)

clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(LIB_DIR)/libft.a
	rm -rf $(MLX_DIR)/libmlx.a
	rm -rf $(NAME)

re: fclean all

