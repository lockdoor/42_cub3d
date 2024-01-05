/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:20:15 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/04 17:11:48 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define RED 0xff0000

static void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->addr + (y * cub->ll + x * (cub->bpp / 8));
	*(unsigned int*)dst = color;
}

static void draw_line(t_cub *cub, double px_1, double py_1, double px_2, \
	double py_2, int color, int debug)
{
	double	step;
	double	dx;
	double	dy;

	dx = px_2 - px_1;
	dy = py_2 - py_1;
	step = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	// debug
	if (debug)
		printf("step: %f\n", step);
	for (int i = 0; i < step; i++)
	{
		my_mlx_pixel_put(cub, px_1, py_1, color);
		px_1 += dx / step;
		py_1 += dy / step;
	}
}

void	draw_square(t_cub *cub, int px, int py, int size, int color)
{
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			my_mlx_pixel_put(cub, px + x, py + y, color);
		}
	}
}

void	draw_player (t_cub *cub)
{
	draw_square(cub, cub->p.px, cub->p.py, 10, RED);
	my_mlx_pixel_put(cub, cub->p.px + cub->p.pdx*5, cub->p.py + cub->p.pdy*5, RED);
	draw_line(cub, cub->p.px, cub->p.py, cub->p.px + cub->p.pdx*5, \
		cub->p.py + cub->p.pdy*5, RED, 0);
}

void	draw_map (t_cub *cub)
{
	int	px;
	int	py;
	
	for (int y = 0; y < cub->map_y; y++)
	{
		for (int x = 0; x <cub->map_x; x++)
		{
			px = x * cub->map_s;
			py = y * cub->map_s;
			if (cub->map[(y * cub->map_x) + x] == 1)
				draw_square(cub, px, py, cub->map_s, 0xffffff);
			draw_line(cub, px, py, px + cub->map_s, py, 0xff, 0);
			draw_line(cub, px, py, px, py + cub->map_s, 0xff, 0);
		}
	}
}

void    draw(t_cub *cub)
{
	ft_bzero(cub->addr, SCREEN_HEIGHT * SCREEN_HEIGHT * (cub->bpp / 8));
	draw_map(cub);
	draw_player(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
}
