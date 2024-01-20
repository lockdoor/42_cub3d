# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 12:51:12 by pnamnil           #+#    #+#              #
#    Updated: 2024/01/20 15:15:21 by pnamnil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

MLX_DIR = minilibx
LIB_DIR = libft
SRC_DIR = srcs
HEADER = srcs/cub3d.h
INCLUDES = 	-I$(LIB_DIR)/includes \
			-I$(MLX_DIR) \
			-I$(SRC_DIR)
			
LINK_LIB = -L$(LIB_DIR) -lft -L$(MLX_DIR) -lmlx
FRAMEWORK = -framework OpenGL -framework AppKit

CC = cc
# CFLAGS = -Wall -Werror -Wextra $(INCLUDES) -g -fsanitize=address
CFLAGS = -Wall -Werror -Wextra $(INCLUDES)

MAP = map/map_01.cub

SRCS = srcs/cub3d.c \
		srcs/debug.c \
		srcs/ft_free.c \
		srcs/parser/read_map.c \
		srcs/parser/init_wall.c \
		srcs/parser/init_floor_ceiling.c \
		srcs/parser/init_map.c \
		srcs/init/init_cub.c \
		srcs/init/init_hook.c \
		srcs/init/init_plan.c \
		srcs/init/init_utils.c \
		srcs/execute/run_cub.c \
		srcs/execute/draw_map_2_d.c \
		srcs/execute/draw_utils.c \
		srcs/execute/run_no_texture.c \
		srcs/execute/run_texture.c \

OBJS = $(SRCS:.c=.o) 

all: $(NAME)

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
	leaks --atExit -- ./$(NAME) $(MAP)

# v:
# 	valgrind --leak-check=full ./$(NAME) $(MAP)

m:
	./$(NAME) $(MAP)

norminette:
	@norminette -R CheckForbiddenSourceHeader $(LIB_DIR)/*.c
	@norminette -R CheckDefine $(LIB_DIR)/includes/libft.h
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)
	@norminette -R CheckDefine $(SRC_DIR)/cub3d.h

re: fclean all

.PHONY: all clean fclean re
