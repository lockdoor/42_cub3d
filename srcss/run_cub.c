/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 06:19:00 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/16 15:05:16 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void	draw_player(t_cub *cub)
{
	double	x_1;
	double	y_1;
	double	x_2;
	double	y_2;

	x_1 = cub->pos_x * cub->pixel;
	y_1 = cub->pos_y * cub->pixel;
	// x_2 = x_1 + cub->pdx * 50;
	// y_2 = y_1 + cub->pdy * 50;
	x_2 = -sin(cub->plane_x) * 50;
	y_2 = cos(cub->plane_x) * 50;
	draw_line (cub, x_1, y_1, x_2, y_2, RGB_WHITE);
	// printf ("x_1: %f, y_1: %f, x_2: %f, y_2: %f\n", x_1, y_1, x_2, y_2);


	// draw_line(cub, x_1, y_1, x_1 + sin(M_PI - cub->pa)*30,\
	// 	y_1 - cos(M_PI - cub->pa)*50, RGB_BLUE);
	// draw_line(cub, x_1, y_1, x_1 - sin(M_PI - cub->pa)*30,\
	// 	y_1 + cos(M_PI - cub->pa)*50, RGB_BLUE);
}
*/

void	verLine(t_cub *cub, int x, int color)
{
	while(cub->draw_start <= cub->draw_end)
	{
		my_mlx_pixel_put(cub, x, cub->draw_start, color);
		cub->draw_start++ ;
	}
}

void	pre_run_1(t_cub *cub, int x)
{
		cub->camera_x = 2 * x / (double)cub->scr_w - 1;
		cub->ray_dir_x = cub->dir_x + cub->plane_x * cub->camera_x;
		cub->ray_dir_y = cub->dir_y + cub->plane_y * cub->camera_x;
		cub->map_x = (int) cub->pos_x;
		cub->map_y = (int) cub->pos_y;
		cub->delta_dist_x = (cub->ray_dir_x == 0) ? 1e30 : fabs(1 / cub->ray_dir_x);
		cub->delta_dist_y = (cub->ray_dir_y == 0) ? 1e30 : fabs(1 / cub->ray_dir_y);
}

void	pre_run_2(t_cub *cub)
{
	if(cub->ray_dir_x < 0)
	{
		cub->step_x = -1;
		cub->side_dist_x = (cub->pos_x - cub->map_x) * cub->delta_dist_x;
	}
	else
	{
		cub->step_x = 1;
		cub->side_dist_x = (cub->map_x + 1.0 - cub->pos_x) * cub->delta_dist_x;
	}
	if(cub->ray_dir_y < 0)
	{
		cub->step_y = -1;
		cub->side_dist_y = (cub->pos_y - cub->map_y) * cub->delta_dist_y;
	}
	else
	{
		cub->step_y = 1;
		cub->side_dist_y = (cub->map_y + 1.0 - cub->pos_y) * cub->delta_dist_y;
	}
}

void	cal_dda(t_cub *cub, int x)
{
	int	hit;
	(void)x;
	hit = 0;
	while(hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if(cub->side_dist_x < cub->side_dist_y)
		{
			cub->side_dist_x += cub->delta_dist_x;
			cub->map_x += cub->step_x;
			cub->side = 0;
		}
		else
		{	
			cub->side_dist_y += cub->delta_dist_y;
			cub->map_y += cub->step_y;
			cub->side = 1;
		}

		/* debug */
		// if (x == 0)
		
			my_mlx_pixel_put (cub, \
			cub->map_y * cub->pixel, \
			cub->map_x * cub->pixel, \
			RGB_WHITE);
		
		
		//Check if ray has hit a wall
		if(cub->map[cub->map_x][cub->map_y] > 0)
			hit = 1;
	}
}

void	cal_wall(t_cub *cub)
{
	int line_height;

	if(cub->side == 0)
		cub->perp_wall_dist = (cub->side_dist_x - cub->delta_dist_x);
	else
		cub->perp_wall_dist = (cub->side_dist_y - cub->delta_dist_y);

	//Calculate height of line to draw on screen
	line_height = (int)(cub->scr_h / cub->perp_wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	cub->draw_start = -line_height / 2 + cub->scr_h / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = line_height / 2 + cub->scr_h / 2;
	if (cub->draw_end >= cub->scr_h)
		cub->draw_end = cub->scr_h - 1;
}

int	wall_color(t_cub *cub)
{
	//choose wall color
	int color;
	
	color = cub->map[cub->map_x][cub->map_y];
	if (color == 1)
		color = RGB_RED;
	else if (color == 2)
		color = RGB_GREEN;
	else if (color == 3)
		color = RGB_BLUE;
	else if (color == 4)
		color = RGB_WHITE;
	else
		color = RGB_YELLOW;
	//give x and y sides different brightness
	if(cub->side == 1) {color = color / 2;}
	return (color);
}

void	map2d(t_cub *cub)
{
	draw_map_2_d(cub);

	draw_line(cub, \
		cub->pos_y * cub->pixel, \
		cub->pos_x * cub->pixel, \
		(cub->pos_y + cub->dir_y) * cub->pixel, \
		(cub->pos_x + cub->dir_x) * cub->pixel, \
		RGB_GREEN
	);

	draw_line(cub, \
		cub->pos_y * cub->pixel, \
		cub->pos_x * cub->pixel, \
		(cub->pos_y - cub->plane_y) * cub->pixel, \
		(cub->pos_x - cub->plane_x) * cub->pixel, \
		RGB_WHITE
	);
	
	draw_line(cub, \
		cub->pos_y * cub->pixel, \
		cub->pos_x * cub->pixel, \
		(cub->pos_y + cub->plane_y) * cub->pixel, \
		(cub->pos_x + cub->plane_x) * cub->pixel, \
		RGB_WHITE
	);
}

void	run_cub(t_cub *cub)
{
	ft_bzero(cub->addr, cub->scr_h * cub->scr_w * (cub->bpp / 8));
	
	map2d(cub);
	
	for (int x = 0; x < cub->scr_w; x++)
	{
		pre_run_1 (cub, x);
		pre_run_2 (cub);
		cal_dda (cub, x);	
		cal_wall (cub);
		//draw the pixels of the stripe as a vertical line
		// verLine(cub, x, wall_color(cub));
		/* debug */
		if (x == 0)
			printf ("px: %f, py: %f, wall_dist: %f, side: %d , dist_x = %f\n", \
			cub->pos_x, cub->pos_y, cub->perp_wall_dist, cub->side, cub->side_dist_x);

	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
}
