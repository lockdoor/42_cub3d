/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 06:14:02 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/15 13:10:32 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_cub *cub)
{
	int	y;

	y = 0;
	while (y < cub->map_h)
	{
		free (cub->map[y++]);
	}
	free (cub->map);
}

int	on_destroy(void *param)
{
	t_cub	*cub;

	cub = (t_cub *) param;
	mlx_destroy_image(cub->mlx, cub->img);
	mlx_destroy_window(cub->mlx, cub->win);
	free_map(cub);
	exit (0);
}

// static void	fdf_isometric(float *x, float *y, float angle)
// {
// 	float	temp;

// 	temp = *x;
// 	*x = (*x - *y) * cos(angle);
// 	*y = ((temp + *y) * sin(angle));
// }

int	key_hook(int key, void *param)
{
	t_cub		*cub;
	// t_player 	*p;

	(void) key;
	cub = (t_cub *) param;
	// p = &cub->p;
	// printf ("key: %d\n", key);
	if (key == KEY_ESCAPE)
		return (on_destroy(cub));
	/*if (key == KEY_W)
	{
		// debug
		// print_pd (key, p);
		
		// p->px += p->pdx;
		// p->py += p->pdy;
		// cub->pos_x += cub->pdx * 1.0 / cub->pixel;
		// cub->pos_y += cub->pdy * 1.0 / cub->pixel;
		cub->pos_x += cub->dir_x * SPEED;
		cub->pos_y += cub->dir_y * SPEED;
	}
	if (key == KEY_S)
	{
		// debug
		// print_pd (key, p);
		
		// p->px -= p->pdx;
		// p->py -= p->pdy;
		// cub->pos_x -= cub->pdx * 1.0 / cub->pixel;
		// cub->pos_y -= cub->pdy * 1.0 / cub->pixel;
		cub->pos_x -= cub->dir_x * SPEED;
		cub->pos_y -= cub->dir_y * SPEED;
	}
	if (key == KEY_A)
	{
		// debug
		// print_pd (key, p);
		
		cub->pos_x -= sin(M_PI - cub->pa) * 1.0 / cub->pixel;
		cub->pos_y -= cos(M_PI - cub->pa) * 1.0 / cub->pixel;
	}
	if (key == KEY_D)
	{
		// debug
		// print_pd (key, p);
		
		cub->pos_x += sin(M_PI - cub->pa) * 1.0 / cub->pixel;
		cub->pos_y += cos(M_PI - cub->pa) * 1.0 / cub->pixel;
	}
	if (key == KEY_LEFT)
	{
		cub->pa += 1.0 / cub->pixel;
		if (cub->pa > 2 * M_PI)
			cub->pa -= 2 * M_PI;
		cub->pdx = cos(cub->pa);
		cub->pdy = -sin(cub->pa);
		
	}
	if (key == KEY_RIGHT)
	{
		cub->pa -= 1.0 / cub->pixel;
		if (cub->pa < 0)
			cub->pa += 2 * M_PI;
		cub->pdx = cos(cub->pa);
		cub->pdy = -sin(cub->pa);
	}*/
	// draw(cub);
	run_cub (cub);
	return (0);
}

int	init_hook(t_cub *cub)
{
	mlx_hook(cub->win, ON_KEYDOWN, 0, &key_hook, cub);
	mlx_hook(cub->win, ON_DESTROY, 0, &on_destroy, cub);
	return (0);
}
