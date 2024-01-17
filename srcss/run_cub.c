/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 06:19:00 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/17 09:47:16 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	verLine(t_cub *cub, t_img *img, int x, int color)
{
	while(cub->draw_start <= cub->draw_end)
	{
		my_mlx_pixel_put(img, x, cub->draw_start, color);
		cub->draw_start++ ;
	}
}

void	pre_run_1(t_cub *cub, t_img *img, int x)
{
		cub->camera_x = 2 * x / (double)img->scr_w - 1;
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
		
		// my_mlx_pixel_put (cub, \
		// cub->map_y * cub->pixel, \
		// cub->map_x * cub->pixel, \
		// RGB_WHITE);
		
		
		//Check if ray has hit a wall
		if(cub->map[cub->map_x][cub->map_y] > 0)
			hit = 1;
	}
}

void	cal_wall(t_cub *cub, t_img *img)
{
	int line_height;

	if(cub->side == 0)
		cub->perp_wall_dist = (cub->side_dist_x - cub->delta_dist_x);
	else
		cub->perp_wall_dist = (cub->side_dist_y - cub->delta_dist_y);

	//Calculate height of line to draw on screen
	line_height = (int)(img->scr_h / cub->perp_wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	cub->draw_start = -line_height / 2 + img->scr_h / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = line_height / 2 + img->scr_h / 2;
	if (cub->draw_end >= img->scr_h)
		cub->draw_end = img->scr_h - 1;
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

void	map2d(t_cub *cub, t_img *img)
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

void	draw_ray(t_cub *cub, t_img *img)
{
	double wall_x; // here exactly the wall was hit
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
	// printf ("wall_x: %f, dir_x: %f, dir_y: %f\n", \
	// wall_x, cub->dir_x, cub->dir_y);
}

void	run_cub(t_cub *cub)
{
	ft_bzero(cub->mini.addr, cub->mini.scr_h * cub->mini.scr_w * (cub->mini.bpp / 8));
	ft_bzero(cub->main.addr, cub->main.scr_h * cub->main.scr_w * (cub->main.bpp / 8));
	
	map2d(cub, &cub->mini);	
	for (int x = 0; x < cub->mini.scr_w; x++)
	{
		pre_run_1 (cub, &cub->mini, x);
		pre_run_2 (cub);
		cal_dda (cub, x);	
		cal_wall (cub, &cub->mini);

		/* debug */
		// if (x == cub->scr_w / 2 || x == 0)
		// {
			// printf ("px: %f, py: %f, wall_dist: %f, side: %d , dist_x = %f\n", \
			// cub->pos_x, cub->pos_y, cub->perp_wall_dist, cub->side, cub->side_dist_x);
			draw_ray (cub, &cub->mini);
		// }
	}
	
	for(int x = 0; x < cub->main.scr_w; x++)
	{
		pre_run_1 (cub, &cub->main, x);
		pre_run_2 (cub);
		cal_dda (cub, x);	
		cal_wall (cub, &cub->main);
		//draw the pixels of the stripe as a vertical line
		verLine(cub, &cub->main, x, wall_color(cub));
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->main.img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini.img, 0, 0);
}
