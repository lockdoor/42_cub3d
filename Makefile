# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 12:51:12 by pnamnil           #+#    #+#              #
#    Updated: 2024/01/19 14:42:13 by pnamnil          ###   ########.fr        #
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

MAP = map/map_01.cub

HEADER = srcss/cub3d.h

SRCS = srcss/cub3d.c srcss/map.c srcss/debug.c srcss/init_cub.c \
		srcss/init_hook.c srcss/run_cub.c srcss/draw_utils.c \
		srcss/draw_map_2_d.c srcss/run_no_texture.c srcss/run_texture.c \
		srcss/read_map.c srcss/init_wall.c srcss/init_utils.c \
		srcss/init_floor_ceiling.c srcss/init_map.c srcss/ft_free.c
		
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
	leaks --atExit -- ./$(NAME) $(MAP)

# v:
# 	valgrind --leak-check=full ./$(NAME) $(MAP)

m:
	./$(NAME) $(MAP)

# norminette:
# 	@norminette -R CheckForbiddenSourceHeader $(LIB_PATH)/*.c
# 	@norminette -R CheckDefine $(LIB_PATH)/includes/libft.h
# 	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*
# 	@norminette -R CheckDefine $(SRC_DIR)/minishell.h

re: fclean all

