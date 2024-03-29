/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 06:09:27 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/20 15:18:04 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_img(t_cub *cub)
{
	cub->mini.scr_w = MINI_W;
	cub->mini.scr_h = MINI_H;
	cub->mini.pixel_x = (double)MINI_W / cub->map_w;
	cub->mini.pixel_y = (double)MINI_H / cub->map_h;
	cub->mini.img = mlx_new_image(cub->mlx, cub->mini.scr_w, cub->mini.scr_h);
	cub->mini.addr = mlx_get_data_addr(cub->mini.img, &cub->mini.bpp, \
		&cub->mini.ll, &cub->mini.endien);
	cub->main.scr_w = SCR_W;
	cub->main.scr_h = SCR_H;
	cub->main.pixel_x = (double)SCR_W / cub->map_w;
	cub->main.pixel_y = (double)SCR_H / cub->map_h;
	cub->main.img = mlx_new_image(cub->mlx, cub->main.scr_w, cub->main.scr_h);
	cub->main.addr = mlx_get_data_addr(cub->main.img, &cub->main.bpp, \
		&cub->main.ll, &cub->main.endien);
	return (0);
}

static int	wall_to_img(t_cub *cub, t_img *img, char *file)
{
	int		x;
	int		y;

	x = TEXTURE_W;
	y = TEXTURE_H;
	img->img = mlx_xpm_file_to_image(cub->mlx, file, &x, &y);
	if (!img->img)
	{
		ft_putstr_fd (file, 2);
		ft_putendl_fd (": can not get image", 2);
		return (EXIT_FAILURE);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endien);
	img->scr_h = y;
	img->scr_w = x;
	return (0);
}

static void	error_init_wall_img(t_cub *cub, t_file *file)
{
	if (cub->wall_n.img)
		mlx_destroy_image(cub->mlx, cub->wall_n.img);
	if (cub->wall_e.img)
		mlx_destroy_image(cub->mlx, cub->wall_e.img);
	if (cub->wall_w.img)
		mlx_destroy_image(cub->mlx, cub->wall_w.img);
	if (cub->wall_s.img)
		mlx_destroy_image(cub->mlx, cub->wall_s.img);
	free_file (file);
	exit (EXIT_FAILURE);
}

static void	init_all_wall(t_cub *cub, t_file *file)
{
	if (wall_to_img(cub, &cub->wall_n, file->wall_n))
		error_init_wall_img(cub, file);
	if (wall_to_img(cub, &cub->wall_e, file->wall_e))
		error_init_wall_img(cub, file);
	if (wall_to_img(cub, &cub->wall_w, file->wall_w))
		error_init_wall_img(cub, file);
	if (wall_to_img(cub, &cub->wall_s, file->wall_s))
		error_init_wall_img(cub, file);
}

int	init_cub(t_cub *cub)
{
	cub->map = cub->file.map;
	cub->map_w = cub->file.map_w;
	cub->map_h = cub->file.map_h;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SCR_W, SCR_H, TITLE);
	init_all_wall(cub, &cub->file);
	init_img (cub);
	cub->pos_x = (double) cub->file.player_y + 0.5;
	cub->pos_y = (double) cub->file.player_x + 0.5;
	init_plan(cub);
	cub->floor = cub->file.floor;
	cub->ceiling = cub->file.ceiling;
	return (0);
}
