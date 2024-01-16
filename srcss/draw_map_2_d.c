/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 07:16:56 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/15 13:40:16 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pick_color(int color)
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

void	draw_map_2_d(t_cub *cub)
{
	double	y;
	double	x;
	// double pixel_x;
	// double pixel_y;
	int color;

	y = 0;
	// pixel_x = (double)cub->scr_w / cub->map_w;
	// pixel_y = (double)cub->scr_h / cub->map_h;
	
	/* debug */
	// printf ("pixel_x: %f, pixel_y: %f\n", pixel_x, pixel_y);
	
	while (y < (double)cub->map_h)
	{
		x = 0;
		while (x < (double)cub->map_w)
		{
			int px = x * cub->pixel;
			int py = y * cub->pixel;
			color = pick_color(cub->map[(int)y][(int)x]);
			if (color)
			{
				draw_square(cub, x * cub->pixel, y * cub->pixel, cub->pixel, cub->pixel, color);	
				// draw_square(cub, x * pixel_x, y * pixel_y, pixel_y, pixel_x, color);
			}
			draw_line(cub, px, py, px + cub->pixel, py, RGB_YELLOW);
			draw_line(cub, px, py, px, py + cub->pixel, RGB_YELLOW);	
			x++ ;
		}
		y++ ;
	}
	
}
