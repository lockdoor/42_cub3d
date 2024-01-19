/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 06:19:00 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/19 15:47:10 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	pre_run_1(t_cub *cub, t_img *img, int x)
{
	cub->camera_x = 2 * x / (double)img->scr_w - 1;
	cub->ray_dir_x = cub->dir_x + cub->plane_x * cub->camera_x;
	cub->ray_dir_y = cub->dir_y + cub->plane_y * cub->camera_x;
	cub->map_x = (int) cub->pos_x;
	cub->map_y = (int) cub->pos_y;
	cub->delta_dist_x = (cub->ray_dir_x == 0) ? 1e30 : fabs(1 / cub->ray_dir_x);
	cub->delta_dist_y = (cub->ray_dir_y == 0) ? 1e30 : fabs(1 / cub->ray_dir_y);
}

static void	pre_run_2(t_cub *cub)
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

static void	cal_dda(t_cub *cub)
{
	int	hit;

	hit = 0;
	while(hit == 0)
	{
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
		if(cub->map[cub->map_x][cub->map_y] > '0')
			hit = 1;
	}
}

static void	cal_wall(t_cub *cub, t_img *img)
{

	if(cub->side == 0)
		cub->perp_wall_dist = (cub->side_dist_x - cub->delta_dist_x);
	else
		cub->perp_wall_dist = (cub->side_dist_y - cub->delta_dist_y);

	//Calculate height of line to draw on screen
	cub->line_height = (int)(img->scr_h / cub->perp_wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	cub->draw_start = -cub->line_height / 2 + img->scr_h / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = cub->line_height / 2 + img->scr_h / 2;
	if (cub->draw_end >= img->scr_h)
		cub->draw_end = img->scr_h - 1;
}

void	clean_screen(t_img *img)
{
	ft_bzero(img->addr, img->scr_h * img->scr_w * (img->bpp / 8));
}

void	draw_floor_ceiling(t_cub *cub, t_img *img)
{
	int	y;
	int x;

	x = 0;
	while (x < img->scr_w)
	{
		y = 0;
		while (y < img->scr_h / 2)
		{
			my_mlx_pixel_put(img, x, y, cub->ceiling);
			y++ ;
		}
		while (y < img->scr_h)
		{
			my_mlx_pixel_put(img, x, y, cub->floor);
			y++ ;
		}
		x++ ;
	}
	
}

void	run_cub(t_cub *cub)
{
	int x;

	clean_screen (&cub->mini);
	clean_screen (&cub->main);
	map_2_d(cub, &cub->mini);
	x = -1;
	while (++x < cub->mini.scr_w)
	{
		pre_run_1 (cub, &cub->mini, x);
		pre_run_2 (cub);
		cal_dda (cub);	
		cal_wall (cub, &cub->mini);
		draw_ray_2_d (cub, &cub->mini);
	}
	draw_floor_ceiling(cub, &cub->main);
	x = -1;
	while (++x < cub->main.scr_w)
	{
		pre_run_1 (cub, &cub->main, x);
		pre_run_2 (cub);
		cal_dda (cub);	
		cal_wall (cub, &cub->main);
		// verLine(cub, &cub->main, x, wall_color(cub));
		write_texture(cub, &cub->main, x);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->main.img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini.img, 0, 0);
}
