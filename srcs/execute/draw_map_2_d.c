/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 07:16:56 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/20 10:24:48 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_map_2_d(t_cub *cub, t_img *img)
{
	int		y;
	int		x;
	t_line	line;

	y = -1;
	while (++y < cub->map_h)
	{
		x = -1;
		while (++x < cub->map_w)
		{
			line.px_1 = x * img->pixel_x;
			line.py_1 = y * img->pixel_y;
			line.color = RGB_BLUE;
			if (cub->map[(int)y][(int)x] == '1')
				draw_square(img, line.px_1, line.py_1, RGB_RED);
			line.px_2 = line.px_1 + img->pixel_x;
			line.py_2 = line.py_1;
			draw_line(img, &line);
			line.px_2 = line.px_1;
			line.py_2 = line.py_1 + img->pixel_y;
			draw_line(img, &line);
		}
	}
}

static int	exactly_x(t_cub *cub)
{
	if (cub->ray_dir_x < 0)
		return (cub->map_x + 1);
	else
		return (cub->map_x);
}

static int	exactly_y(t_cub *cub)
{
	if (cub->ray_dir_y < 0)
		return (cub->map_y + 1);
	else
		return (cub->map_y);
}

// here exactly the wall was hit
void	draw_ray_2_d(t_cub *cub, t_img *img)
{
	double	wall_x;
	t_line	line;

	line.color = RGB_WHITE;
	if (cub->side == 0)
	{
		wall_x = cub->pos_y + cub->perp_wall_dist * cub->ray_dir_y;
		wall_x -= floor(wall_x);
		line.px_1 = cub->pos_y * img->pixel_x;
		line.py_1 = cub->pos_x * img->pixel_y;
		line.px_2 = (cub->map_y + wall_x) * img->pixel_x;
		line.py_2 = exactly_x(cub) * img->pixel_y;
	}
	else
	{
		wall_x = cub->pos_x + cub->perp_wall_dist * cub->ray_dir_x;
		wall_x -= floor(wall_x);
		line.px_1 = cub->pos_y * img->pixel_x;
		line.py_1 = cub->pos_x * img->pixel_y;
		line.px_2 = exactly_y(cub) * img->pixel_x;
		line.py_2 = (cub->map_x + wall_x) * img->pixel_y;
	}
	draw_line (img, &line);
}

void	map_2_d(t_cub *cub, t_img *img)
{
	t_line	line;

	draw_map_2_d(cub, img);
	line.px_1 = cub->pos_y * img->pixel_x;
	line.py_1 = cub->pos_x * img->pixel_y;
	line.px_2 = (cub->pos_y + cub->dir_y) * img->pixel_x;
	line.py_2 = (cub->pos_x + cub->dir_x) * img->pixel_y;
	line.color = RGB_GREEN;
	draw_line(img, &line);
	line.px_2 = (cub->pos_y - cub->plane_y) * img->pixel_x;
	line.py_2 = (cub->pos_x - cub->plane_x) * img->pixel_y;
	line.color = RGB_WHITE;
	draw_line(img, &line);
	line.px_2 = (cub->pos_y + cub->plane_y) * img->pixel_x;
	line.py_2 = (cub->pos_x + cub->plane_x) * img->pixel_y;
	draw_line(img, &line);
}
