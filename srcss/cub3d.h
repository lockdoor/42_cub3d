/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:33:52 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/17 07:59:36 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include "mlx.h"
# include <math.h>
# include <stdlib.h>

# define ON_KEYUP 3
# define ON_KEYDOWN 2
# define ON_DESTROY 17
# define KEY_ESCAPE 53
# define KEY_W 13
# define KEY_S 1
# define KEY_D 2
# define KEY_A 0
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define TITLE "CUB3D"
# define MAP_W 24
# define MAP_H 24
# define SCR_W 640
# define SCR_H 480

# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.1

/* color */
#define RGB_RED 0xFF0000
#define RGB_GREEN 0xFF00
#define RGB_BLUE 0xFF
#define RGB_WHITE 0xFFFFFF
#define RGB_YELLOW 0xFF0
// map.c
// extern int	worldMap[MAP_H][MAP_W];

typedef struct s_cub
{
	// map
	int		map_w;
	int		map_h;
	int		scr_w;
	int		scr_h;
	int		**map;
	int		pixel;
	int		map_x;
	int		map_y;
	
	// mlx
	void	*mlx;
	void	*win;
	void	*img;
	// void	*img_mini;

	// addr group
	char	*addr;
	int		bpp;
	int		ll;
	int		endien;

	// // map group
	// int		*map;
	// int		map_x;
	// int		map_y;
	// int		map_s;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		draw_start;
	int		draw_end;
	// double	pdx;
	// double	pdy;
	// double	pa;
}	t_cub;

// debug.c
// void	print_map(int map[MAP_H][MAP_W]);
void	print_map(int **map, int y, int x);

// init_cub.c
int	init_cub(t_cub *cub);

// init_hook.c
int	init_hook(t_cub *cub);

// run_cub.c
void	run_cub(t_cub *cub);

// map.c
int **make_map(void);

// draw_map_2_d.c
void	draw_map_2_d(t_cub *cub);

// draw_utils.c
void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
void	draw_square(t_cub *cub, int px, int py, int size_y, int size_x, int color);
void	draw_line(t_cub *cub, double px_1, double py_1, double px_2, \
		double py_2, int color);

#endif
