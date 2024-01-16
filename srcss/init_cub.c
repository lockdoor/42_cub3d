/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 06:09:27 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/15 14:20:53 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_cub(t_cub *cub)
{
	cub->map = make_map();
	cub->pixel = 24;
	cub->map_w = MAP_W;
	cub->map_h = MAP_H;
	cub->scr_w = MAP_W * 24;
	cub->scr_h = MAP_H * 24;
	
	/* mlx */
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->scr_w, cub->scr_h, TITLE);
	cub->img = mlx_new_image(cub->mlx, cub->scr_w, cub->scr_h);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bpp, &cub->ll, &cub->endien);
	
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
