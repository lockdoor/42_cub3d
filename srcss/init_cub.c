/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 06:09:27 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/18 07:46:36 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_img(t_cub *cub)
{
	// mini map
	cub->mini.scr_w = MINI_W;
	cub->mini.scr_h = MINI_H;
	cub->mini.pixel_x = (double)MINI_W / MAP_W;
	cub->mini.pixel_y = (double)MINI_H / MAP_H;
	cub->mini.img = mlx_new_image(cub->mlx, cub->mini.scr_w, cub->mini.scr_h);
	cub->mini.addr = mlx_get_data_addr(cub->mini.img, &cub->mini.bpp, \
		&cub->mini.ll, &cub->mini.endien);

	// main map
	cub->main.scr_w = SCR_W;
	cub->main.scr_h = SCR_H;
	cub->main.pixel_x = (double)SCR_W / MAP_W;
	cub->main.pixel_y = (double)SCR_H / MAP_H;
	cub->main.img = mlx_new_image(cub->mlx, cub->main.scr_w, cub->main.scr_h);
	cub->main.addr = mlx_get_data_addr(cub->main.img, &cub->main.bpp, \
		&cub->main.ll, &cub->main.endien);
	return (0);
}

int	init_wall(t_cub *cub, t_img *img, char *file)
{
	int		x;
	int		y;

	x = TEXTURE_W;
	y = TEXTURE_H;
	img->img = mlx_xpm_file_to_image(cub->mlx, file, &x, &y);
	if (!img->img)
	{
		printf ("init_wall: can not get img\n");
		return (1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endien);
	if (!img->addr)
	{
		printf ("init_wall: can not get address\n");
		return (1);
	}
	img->scr_h = y;
	img->scr_w = x;
	return (0);
}

int	init_cub(t_cub *cub)
{
	cub->map = make_map();
	cub->map_w = MAP_W;
	cub->map_h = MAP_H;
	/* mlx */
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SCR_W, SCR_H, TITLE);
	init_img (cub);

	init_wall (cub, &cub->wall_n, "img/wall_1.xpm");
	init_wall (cub, &cub->wall_e, "img/wall_2.xpm");
	init_wall (cub, &cub->wall_w, "img/wall_3.xpm");
	init_wall (cub, &cub->wall_s, "img/wall_4.xpm");
	
	cub->pos_x = 22;
	cub->pos_y = 12;
	cub->dir_x = -1;
	cub->dir_y = 0;
	cub->plane_x = 0;
	cub->plane_y = 0.66;
	cub->floor = 0x404040;
	cub->ceiling = 0x99FFFF;
	return (0);
}
