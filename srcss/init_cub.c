/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 06:09:27 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/17 09:43:18 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_cub(t_cub *cub)
{
	cub->map = make_map();
	cub->map_w = MAP_W;
	cub->map_h = MAP_H;
	// cub->scr_w = MAP_W * 24;
	// cub->scr_h = MAP_H * 24;
	// cub->pixel = 24;
	// cub->scr_w = SCR_W;
	// cub->scr_h = SCR_H;
	// cub->pixel_x = SCR_W / MAP_W;
	// cub->pixel_y = SCR_H / MAP_H; 
	
	/* mlx */
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SCR_W, SCR_H, TITLE);
	// cub->img = mlx_new_image(cub->mlx, cub->scr_w, cub->scr_h);

	// mini map
	cub->mini.scr_w = MINI_W;
	cub->mini.scr_h = MINI_H;
	cub->mini.pixel_x = MINI_W / MAP_W;
	cub->mini.pixel_y = MINI_H / MAP_H;
	cub->mini.img = mlx_new_image(cub->mlx, cub->mini.scr_w, cub->mini.scr_h);
	cub->mini.addr = mlx_get_data_addr(cub->mini.img, &cub->mini.bpp, \
		&cub->mini.ll, &cub->mini.endien);

	// main map
	cub->main.scr_w = SCR_W;
	cub->main.scr_h = SCR_H;
	cub->main.pixel_x = SCR_W / MAP_W;
	cub->main.pixel_y = SCR_H / MAP_H;
	cub->main.img = mlx_new_image(cub->mlx, cub->main.scr_w, cub->main.scr_h);
	cub->main.addr = mlx_get_data_addr(cub->main.img, &cub->main.bpp, \
		&cub->main.ll, &cub->main.endien);
	
	cub->pos_x = 22;
	cub->pos_y = 12;
	cub->dir_x = -1;
	cub->dir_y = 0;
	cub->plane_x = 0;
	cub->plane_y = 0.66;
	// cub->pa = M_PI_2;
	// cub->pdx = cos(cub->pa);
	// cub->pdy = -sin(cub->pa);
	
	// print_map(cub->map, cub->map_h, cub->map_w);
	
	return (0);
}
