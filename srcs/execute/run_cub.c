/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 06:19:00 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/20 10:48:18 by pnamnil          ###   ########.fr       */
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
	cub->delta_dist_x = fabs(1 / cub->ray_dir_x);
	if (cub->ray_dir_x == 0)
		cub->delta_dist_x = 1e30;
	cub->delta_dist_y = fabs(1 / cub->ray_dir_y);
	if (cub->ray_dir_y == 0)
		cub->delta_dist_y = 1e30;
}

static void	pre_run_2(t_cub *cub)
{
	if (cub->ray_dir_x < 0)
	{
		cub->step_x = -1;
		cub->side_dist_x = (cub->pos_x - cub->map_x) * cub->delta_dist_x;
	}
	else
	{
		cub->step_x = 1;
		cub->side_dist_x = (cub->map_x + 1.0 - cub->pos_x) * cub->delta_dist_x;
	}
	if (cub->ray_dir_y < 0)
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
	while (hit == 0)
	{
		if (cub->side_dist_x < cub->side_dist_y)
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
		if (cub->map[cub->map_x][cub->map_y] > '0')
			hit = 1;
	}
}

//Calculate height of line to draw on screen
//calculate lowest and highest pixel to fill in current stripe
static void	cal_wall(t_cub *cub, t_img *img)
{
	if (cub->side == 0)
		cub->perp_wall_dist = (cub->side_dist_x - cub->delta_dist_x);
	else
		cub->perp_wall_dist = (cub->side_dist_y - cub->delta_dist_y);
	cub->line_height = (int)(img->scr_h / cub->perp_wall_dist);
	cub->draw_start = -cub->line_height / 2 + img->scr_h / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = cub->line_height / 2 + img->scr_h / 2;
	if (cub->draw_end >= img->scr_h)
		cub->draw_end = img->scr_h - 1;
}

// can use funtion
// ver_line(cub, &cub->main, x, wall_color(cub));
// write_texture(cub, &cub->main, x);
void	run_cub(t_cub *cub)
{
	int	x;

	clean_screen (&cub->mini, &cub->main);
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
		write_texture(cub, &cub->main, x);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->main.img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini.img, 0, 0);
}
