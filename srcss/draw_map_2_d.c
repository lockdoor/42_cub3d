/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 07:16:56 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/18 07:46:59 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	pick_color(int color)
{
	if (color == 1)
		return (RGB_RED);
	else if (color == 2)
		return (RGB_GREEN);
	else if (color == 3)
		return (RGB_BLUE);
	else if (color == 4)
		return (RGB_YELLOW);
	return (0);
}

static void	draw_map_2_d(t_cub *cub, t_img *img)
{
	int	y;
	int	x;
	int color;
	double	px;
	double	py;

	// debug
	// printf ("draw_map_2_d: pixel_x: %f, pixel_y: %f\n", \
	// 	img->pixel_x, img->pixel_y);
	y = 0;
	while (y < cub->map_h)
	{
		x = 0;
		while (x < cub->map_w)
		{
			px = x * img->pixel_x;
			py = y * img->pixel_y;
			color = pick_color(cub->map[(int)y][(int)x]);
			if (color)
				draw_square(img, px, py, color);	
			draw_line(img, px, py, px + img->pixel_x, py, RGB_BLUE);
			draw_line(img, px, py, px, py + img->pixel_y, RGB_BLUE);
			x++ ;
		}
		y++ ;
	}
}

// here exactly the wall was hit
void	draw_ray_2_d(t_cub *cub, t_img *img)
{
	double wall_x; 
	if(cub->side == 0)
	{
		wall_x = cub->pos_y + cub->perp_wall_dist * cub->ray_dir_y;
		wall_x -= floor(wall_x);
		draw_line(img, \
		cub->pos_y * img->pixel_x, \
		cub->pos_x * img->pixel_y, \
		(cub->map_y + wall_x) * img->pixel_x,
		(cub->ray_dir_x < 0 ? cub->map_x + 1 : cub->map_x) * img->pixel_y, \
		RGB_WHITE);
	}
	else 
	{
		wall_x = cub->pos_x + cub->perp_wall_dist * cub->ray_dir_x;
		wall_x -= floor(wall_x);
		draw_line(img, \
		cub->pos_y * img->pixel_x, \
		cub->pos_x * img->pixel_y, \
		(cub->ray_dir_y < 0 ? cub->map_y + 1 : cub->map_y) * img->pixel_x, \
		(cub->map_x + wall_x) * img->pixel_y,
		RGB_WHITE);
	}
}

void	map_2_d(t_cub *cub, t_img *img)
{
	draw_map_2_d(cub, img);
	draw_line(img, \
		cub->pos_y * img->pixel_x, \
		cub->pos_x * img->pixel_y, \
		(cub->pos_y + cub->dir_y) * img->pixel_x, \
		(cub->pos_x + cub->dir_x) * img->pixel_y, \
		RGB_GREEN
	);
	draw_line(img, \
		cub->pos_y * img->pixel_x, \
		cub->pos_x * img->pixel_y, \
		(cub->pos_y - cub->plane_y) * img->pixel_x, \
		(cub->pos_x - cub->plane_x) * img->pixel_y, \
		RGB_WHITE
	);
	draw_line(img, \
		cub->pos_y * img->pixel_x, \
		cub->pos_x * img->pixel_y, \
		(cub->pos_y + cub->plane_y) * img->pixel_x, \
		(cub->pos_x + cub->plane_x) * img->pixel_y, \
		RGB_WHITE
	);
}
