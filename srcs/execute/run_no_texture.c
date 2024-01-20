/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_no_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:18:41 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/20 10:49:23 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ver_line(t_cub *cub, t_img *img, int x, int color)
{
	while (cub->draw_start <= cub->draw_end)
	{
		my_mlx_pixel_put(img, x, cub->draw_start, color);
		cub->draw_start++ ;
	}
}

//give x and y sides different brightness
//choose wall color
int	wall_color(t_cub *cub)
{
	int	color;

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
	if (cub->side == 1)
		color = color / 2;
	return (color);
}
