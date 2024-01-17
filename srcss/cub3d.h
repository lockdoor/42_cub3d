/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:33:52 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/17 15:58:39 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include "mlx.h"
# include <math.h>
# include <stdlib.h>

# define TITLE "CUB3D"

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

// can setting window size here.
# define MAP_W 24
# define MAP_H 24
# define SCR_W 1200
# define SCR_H 800
# define MINI_H 240
# define MINI_W 240
# define TEXTURE_H 64
# define TEXTURE_W 64

# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.1

/* color */
#define RGB_RED 0xFF0000
#define RGB_GREEN 0x00FF00
#define RGB_BLUE 0x0000FF
#define RGB_WHITE 0xFFFFFF
#define RGB_YELLOW 0xFFFF00

typedef struct s_img
{
	void	*img;

	int		scr_w;
	int		scr_h;
	int		pixel_x;
	int		pixel_y;
	
	// addr group
	char	*addr;
	int		bpp;
	int		ll;
	int		endien;
}	t_img;

typedef struct s_cub
{
	// map
	int		map_w;
	int		map_h;
	int		**map;
	int		map_x;
	int		map_y;
	
	// mlx
	void	*mlx;
	void	*win;
	
	t_img	mini;
	t_img	main;
	t_img	wall;

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
	int		line_height;
}	t_cub;

// debug.c
void	print_map(int **map, int y, int x);

// init_cub.c
int	init_cub(t_cub *cub);

// init_hook.c
int	init_hook(t_cub *cub);

// run_cub.c
void	run_cub(t_cub *cub);

// run_no_texture.c
void	verLine(t_cub *cub, t_img *img, int x, int color);
int	wall_color(t_cub *cub);

// run_texture.c
void	write_texture(t_cub *cub, t_img *img, int x);

// map.c
int **make_map(void);

// draw_map_2_d.c
void	map_2_d(t_cub *cub, t_img *img);
void	draw_ray_2_d(t_cub *cub, t_img *img);

// draw_utils.c
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_square(t_img *img, int px, int py, int color);
void	draw_line(t_img *img, double px_1, double py_1, double px_2, \
		double py_2, int color);

#endif
