/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 07:15:40 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/15 11:12:50 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x >= cub->scr_w || y >= cub->scr_h || x < 0 || y < 0)
		return ;
	// if (y == cub->scr_h - 1)
	// 	printf ("x: %d\n", x);
	dst = cub->addr + (y * cub->ll + x * (cub->bpp / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_cub *cub, int px, int py, int size_y, int size_x, int color)
{
	for (int y = 0; y < size_y; y++)
	{
		for (int x = 0; x < size_x; x++)
			my_mlx_pixel_put(cub, px + x, py + y, color);
	}
}

void	draw_line(t_cub *cub, double px_1, double py_1, double px_2, \
	double py_2, int color)
{
	double	step;
	double	dx;
	double	dy;

	dx = px_2 - px_1;
	dy = py_2 - py_1;
	step = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	for (int i = 0; i < step; i++)
	{
		my_mlx_pixel_put(cub, px_1, py_1, color);
		px_1 += dx / step;
		py_1 += dy / step;
	}
}
