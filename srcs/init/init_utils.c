/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:39:24 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/20 10:56:08 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	split_len(char **sp)
{
	int		i;

	i = 0;
	while (sp[i])
		i++ ;
	return (i);
}

int	on_destroy(void *param)
{
	t_cub	*cub;

	cub = (t_cub *) param;
	mlx_destroy_image(cub->mlx, cub->wall_n.img);
	mlx_destroy_image(cub->mlx, cub->wall_e.img);
	mlx_destroy_image(cub->mlx, cub->wall_w.img);
	mlx_destroy_image(cub->mlx, cub->wall_s.img);
	mlx_destroy_image(cub->mlx, cub->mini.img);
	mlx_destroy_image(cub->mlx, cub->main.img);
	mlx_destroy_window(cub->mlx, cub->win);
	free_file(&cub->file);
	exit (0);
}
