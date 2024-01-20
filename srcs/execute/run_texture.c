/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:23:50 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/20 13:49:25 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//calculate value of wallX
//where exactly the wall was hit
static double	wall_hit(t_cub *cub)
{
	double	wall_x;

	if (cub->side == 0)
		wall_x = cub->pos_y + cub->perp_wall_dist * cub->ray_dir_y;
	else
		wall_x = cub->pos_x + cub->perp_wall_dist * cub->ray_dir_x;
	wall_x -= floor((wall_x));
	return (wall_x);
}

static t_img	*collect_wall(t_cub *cub)
{
	if (cub->side)
	{
		if (cub->pos_y > (double) cub->map_y)
			return (&cub->wall_w);
		else
			return (&cub->wall_e);
	}
	else
	{
		if (cub->pos_x > (double) cub->map_x)
			return (&cub->wall_s);
		else
			return (&cub->wall_n);
	}
}

void	draw_floor_ceiling(t_cub *cub, t_img *img)
{
	int	y;
	int	x;

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

// texturing calculations
// 1 subtracted from it so that texture 0 can be used!
void	write_texture(t_cub *cub, t_img *img, int x)
{
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	u_int32_t	color;

	tex_x = (int)(wall_hit(cub) * (double)TEXTURE_W);
	if (cub->side == 0 && cub->ray_dir_x > 0)
		tex_x = TEXTURE_W - tex_x - 1;
	if (cub->side == 1 && cub->ray_dir_y < 0)
		tex_x = TEXTURE_W - tex_x - 1;
	step = 1.0 * TEXTURE_H / cub->line_height;
	tex_pos = (cub->draw_start - img->scr_h / 2 + cub->line_height / 2) * step;
	while (cub->draw_start <= cub->draw_end)
	{
		tex_y = (int)tex_pos & (TEXTURE_H - 1);
		tex_pos += step;
		color = my_mlx_pixel_get(collect_wall(cub), tex_x, tex_y);
		if (cub->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(img, x, cub->draw_start, color);
		cub->draw_start++ ;
	}
}
