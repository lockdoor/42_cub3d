/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 07:16:56 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/17 09:25:04 by pnamnil          ###   ########.fr       */
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

void	draw_map_2_d(t_cub *cub, t_img *img)
{
	double	y;
	double	x;
	int color;

	y = 0;
	while (y < (double)cub->map_h)
	{
		x = 0;
		while (x < (double)cub->map_w)
		{
			int px = x * img->pixel_x;
			int py = y * img->pixel_y;
			color = pick_color(cub->map[(int)y][(int)x]);
			if (color)
			{
				draw_square(img, px, py, color);	
			}
			draw_line(img, px, py, px + img->pixel_x, py, RGB_YELLOW);
			draw_line(img, px, py, px, py + img->pixel_y, RGB_YELLOW);	
			x++ ;
		}
		y++ ;
	}
	
}
