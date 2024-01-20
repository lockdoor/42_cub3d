/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_plan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:28:58 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/19 17:04:40 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	plan_n(t_cub *cub)
{
	cub->dir_x = -1;
	cub->dir_y = 0;
	cub->plane_x = 0;
	cub->plane_y = 0.66;
}

static void	plan_e(t_cub *cub)
{
	cub->dir_x = 0;
	cub->dir_y = -1;
	cub->plane_x = -0.66;
	cub->plane_y = 0;
}

static void	plan_w(t_cub *cub)
{
	cub->dir_x = 0;
	cub->dir_y = 1;
	cub->plane_x = 0.66;
	cub->plane_y = 0;
}

static void	plan_s(t_cub *cub)
{
	cub->dir_x = 1;
	cub->dir_y = 0;
	cub->plane_x = 0;
	cub->plane_y = 0.66;
}

void	init_plan(t_cub *cub)
{
	if (cub->file.player_view == 'N')
		plan_n (cub);
	else if (cub->file.player_view == 'E')
		plan_e (cub);
	else if (cub->file.player_view == 'W')
		plan_w (cub);
	else if (cub->file.player_view == 'S')
		plan_s (cub);
}
