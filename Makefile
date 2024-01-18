# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 12:51:12 by pnamnil           #+#    #+#              #
#    Updated: 2024/01/18 08:11:04 by pnamnil          ###   ########.fr        #
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
CFLAGS = -Wall -Werror -Wextra $(INCLUDES) -g -fsanitize=address
# CFLAGS = -Wall -Werror -Wextra $(INCLUDES)
# CFLAGS = $(INCLUDES) -g -fsanitize=address

# SRCS = srcs/main.c \
# 		srcs/draw.c
		
# SRCS = srcss/main.c
HEADER = srcss/cub3d.h

SRCS = srcss/cub3d.c srcss/map.c srcss/debug.c srcss/init_cub.c \
		srcss/init_hook.c srcss/run_cub.c srcss/draw_utils.c \
		srcss/draw_map_2_d.c srcss/run_no_texture.c srcss/run_texture.c
		
OBJS = $(SRCS:.c=.o) 

all: $(NAME) $(HEADER)

$(NAME): $(OBJS) $(HEADER) Makefile
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

l:
	leaks --atExit -- ./$(NAME)

re: fclean all

