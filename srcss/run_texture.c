/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:23:50 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/17 15:24:46 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static u_int32_t	my_mlx_pixel_get(t_img *img, int x, int y)
{
	u_int32_t	color;
	char		*dst;

	if (x >= img->scr_w || y >= img->scr_h || x < 0 || y < 0)
		return (0);
	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	color = *(unsigned int*)dst;
	return (color);
}

//calculate value of wallX
static double	wall_hit(t_cub *cub)
{
	double wall_x; //where exactly the wall was hit
	if (cub->side == 0) 
		wall_x = cub->pos_y + cub->perp_wall_dist * cub->ray_dir_y;
	else
		wall_x = cub->pos_x + cub->perp_wall_dist * cub->ray_dir_x;
	wall_x -= floor((wall_x));
	return(wall_x);
}

void	write_texture(t_cub *cub, t_img *img, int x)
{
	
	int	tex_x;
	int	tex_y;
	double step;
	double tex_pos;
	u_int32_t	color;
	// texturing calculations
	// int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

	tex_x = (int)(wall_hit(cub) * (double)TEXTURE_W);
	if(cub->side == 0 && cub->ray_dir_x > 0)
		tex_x = TEXTURE_W - tex_x - 1;
	if(cub->side == 1 && cub->ray_dir_y < 0)
		tex_x = TEXTURE_W - tex_x - 1;
	step = 1.0 * TEXTURE_H / cub->line_height;
	tex_pos = (cub->draw_start - img->scr_h / 2 + cub->line_height / 2) * step;
	while (cub->draw_start <= cub->draw_end)
	{
		tex_y = (int)tex_pos & (TEXTURE_H - 1);
		tex_pos += step;
		color = my_mlx_pixel_get(&cub->wall, tex_x, tex_y);
		if (cub->side == 1)
			color = (color >> 1) & 8355711;		
		my_mlx_pixel_put(img, x, cub->draw_start, color);
		cub->draw_start++ ;
	}
}