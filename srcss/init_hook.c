/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 06:14:02 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/17 14:00:13 by pnamnil          ###   ########.fr       */
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
	mlx_destroy_image(cub->mlx, cub->wall.img);
	mlx_destroy_image(cub->mlx, cub->mini.img);
	mlx_destroy_image(cub->mlx, cub->main.img);
	mlx_destroy_window(cub->mlx, cub->win);
	free_map(cub);
	exit (0);
}

//both camera direction and camera plane must be rotated
void	rotate(t_cub *cub, double a)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(a) - cub->dir_y * sin(a);
	cub->dir_y = old_dir_x * sin(a) + cub->dir_y * cos(a);
	old_plane_x = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(a) - cub->plane_y * sin(a);
	cub->plane_y = old_plane_x * sin(a) + cub->plane_y * cos(a);
}

void	move(t_cub *cub, double x, double y)
{
	double next_pos_x;
	double next_pos_y;

	next_pos_x = cub->pos_x + x * MOVE_SPEED;
	next_pos_y = cub->pos_y + y * MOVE_SPEED;
	if (cub->map[(int)next_pos_x][(int)cub->pos_y] == 0)
		cub->pos_x += x * MOVE_SPEED;
	if (cub->map[(int)cub->pos_x][(int)next_pos_y] == 0)
		cub->pos_y += y * MOVE_SPEED;
	// printf("cub->pos_x: %f, cub->pos_y: %f\n", cub->pos_x, cub->pos_y);
}

int	key_hook(int key, void *param)
{
	t_cub		*cub;

	cub = (t_cub *) param;
	if (key == KEY_ESCAPE)
		return (on_destroy(cub));
	if (key == KEY_W)
		move(cub, cub->dir_x, cub->dir_y);
	if (key == KEY_S)
		move(cub, -cub->dir_x, -cub->dir_y);
	if (key == KEY_A)
		move(cub, -(cub->plane_x / 0.66), -cub->plane_y / 0.66);
	if (key == KEY_D)
		move(cub, (cub->plane_x / 0.66), cub->plane_y / 0.66);
	if (key == KEY_LEFT)
		rotate(cub, ROTATE_SPEED);
	if (key == KEY_RIGHT)
		rotate(cub, -ROTATE_SPEED);
	run_cub (cub);
	return (0);
}

int	init_hook(t_cub *cub)
{
	mlx_hook(cub->win, ON_KEYDOWN, 0, &key_hook, cub);
	mlx_hook(cub->win, ON_DESTROY, 0, &on_destroy, cub);
	return (0);
}
