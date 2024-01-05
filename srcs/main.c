/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:04:43 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/04 17:02:41 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map[] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 'P', 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

int	init_player(t_cub *cub)
{
	for (int y = 0; y < cub->map_y; y++ )
	{
		for (int x = 0; x < cub->map_x; x++)
		{
			if (cub->map[(y * cub->map_x) + x] == 'P')
			{
				cub->p.px = x * cub->map_s + (cub->map_s / 2);
				cub->p.py = y * cub->map_s + (cub->map_s / 2);
				cub->p.pa = 3 * M_PI / 2;
				cub->p.pdx = cos(cub->p.pa) * 5;
				cub->p.pdy = sin(cub->p.pa) * 5;
				return (0);
			}
		}
	}
	return (1);
}

int	init_cub(t_cub *cub)
{
	ft_memset (cub, 0, sizeof(t_cub));
	// cub->map = map;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	cub->img = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bpp, &cub->ll, &cub->endien);
	cub->map = map;
	cub->map_x = 8;
	cub->map_y = 8;
	cub->map_s = 64;
	init_player(cub);
	return (0);
}

int	on_destroy(void *param)
{
	t_cub	*cub;

	cub = (t_cub *) param;
	mlx_destroy_image(cub->mlx, cub->img);
	mlx_destroy_window(cub->mlx, cub->win);
	exit (0);
}

int	key_hook(int key, void *param)
{
	t_cub		*cub;
	t_player 	*p;

	cub = (t_cub *) param;
	p = &cub->p;
	// printf ("key: %d\n", key);
	if (key == KEY_ESCAPE)
		return (on_destroy(cub));
	/*
	if (key == KEY_W)
		cub->p.py -= 5;
	if (key == KEY_S)
		cub->p.py += 5;
	if (key == KEY_A)
		cub->p.px -= 5;
	if (key == KEY_D)
		cub->p.px += 5;
	*/
	if (key == KEY_W)
	{
		p->px += p->pdx;
		p->py += p->pdy;
	}
	if (key == KEY_S)
	{
		p->px -= p->pdx;
		p->py -= p->pdy;
	}
	if (key == KEY_A)
	{
		p->pa -= 0.1;
		if (p->pa < 0)
			p->pa += 2 * M_PI;
		p->pdx = cos(p->pa) * 5;
		p->pdy = sin(p->pa) * 5;
	}
	if (key == KEY_D)
	{
		p->pa += 0.1;
		if (p->pa > 2 * M_PI)
			p->pa -= 2 * M_PI;
		p->pdx = cos(p->pa) * 5;
		p->pdy = sin(p->pa) * 5;
	}

	draw(cub);
	return (0);
}

int	init_hook(t_cub *cub)
{
	mlx_hook(cub->win, ON_KEYDOWN, 0, &key_hook, cub);
	mlx_hook(cub->win, ON_DESTROY, 0, &on_destroy, cub);
	return (0);
}

int	main(void)
{
	t_cub	cub;

	init_cub(&cub);
	init_hook(&cub);
	draw(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
