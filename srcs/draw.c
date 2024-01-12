/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:20:15 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/11 08:29:19 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->addr + (y * cub->ll + x * (cub->bpp / 8));
	*(unsigned int*)dst = color;
}

static void draw_line(t_cub *cub, double px_1, double py_1, double px_2, \
	double py_2, int color, int debug)
{
	double	step;
	double	dx;
	double	dy;

	dx = px_2 - px_1;
	dy = py_2 - py_1;
	step = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	// debug
	if (debug)
		printf("step: %f\n", step);
	for (int i = 0; i < step; i++)
	{
		my_mlx_pixel_put(cub, px_1, py_1, color);
		px_1 += dx / step;
		py_1 += dy / step;
	}
}

void	draw_square(t_cub *cub, int px, int py, int size, int color)
{
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			// my_mlx_pixel_put(cub, px + cos(cub->p.pa)*x, py + sin(cub->p.pa)*y, color);
			my_mlx_pixel_put(cub, px + x, py + y, color);
		}
	}
}

/*
void	draw_square_player(t_cub *cub, int px, int py, int size, int color)
{
	for (int y = 0; y < size; y++)
	{
		// for (int x = 0; x < size; x++)
		// {
		// 	// my_mlx_pixel_put(cub, px + cos(cub->p.pa)*x, py + sin(cub->p.pa)*y, color);
		// 	my_mlx_pixel_put(cub, px + x, py + y, color);
		// }
		draw_line(cub, px, py, px + cos(M_PI - cub->p.pa) * 5, \
			py + y + sin(M_PI - cub->p.pa) * 5, color, 0);
	}
}
*/

int cal_index(t_cub *cub, double dx, double dy)
{
	return ((int) (((int)(dy / (double)cub->map_s) * cub->map_x) + (int)(dx / (double)cub->map_s)));
}

void	draw_wall(t_cub *cub, double dx, double dy, int color, int col)
{
	(void) dx;
	(void) dy;
	(void) color;
	(void) col;
	double wall_person = 1.5;
	double dist_y = dy - cub->p.py;
	double wall_hight_percent = fabs(SCREEN_HEIGHT - dist_y)  * 100 / SCREEN_HEIGHT;
	double wall_hight = SCREEN_HEIGHT * wall_person * (fabs(dist_y)  * 100 / SCREEN_HEIGHT) / 100;
	printf ("wall_hight_percent: %f, dist_y: %f\n", wall_hight_percent, dist_y);
	for (int y = 0; y < cub->map_y * cub->map_s; y++ )
	{
		if (y > wall_hight)
			my_mlx_pixel_put(cub, col, y, color);
	}
}

void	draw_ray(t_cub *cub)
{
	int	hit = 0;

	double	dx;
	double	dy;
	// double 	width = cub->map_x * cub->map_s;
	double	ra = (M_PI / 3) / (double)SCREEN_WIDTH;
	// printf ("line: %f\n", line);
	double	i = M_PI / 6;
	for (int col = 0; col < SCREEN_WIDTH; col++)
	{
		dx = cub->p.px;
		dy = cub->p.py;
		while (hit == 0)
		{
			dx += cos(cub->p.pa + i);
			dy -= sin(cub->p.pa + i);
			if (cub->map[cal_index(cub, dx, dy)] == 1)
			{
				// printf("===============hit==============");
				hit = 1;
			}

		}
		// draw_line(cub, cub->p.px, cub->p.py, dx, dy, RED, 0);
		draw_wall(cub, dx, dy, RED, col);
		// printf ("i: %f\n", i);
		i -= ra ;
		hit = 0;
	}
	// debug
	// printf ("px: %f, py: %f\n", cub->p.px, cub->p.py);
	// printf ("dx: %f, dy: %f\n", dx, dy);
	// printf ("index: %d\n", cal_index(cub, dx, dy));
}


void	draw_player (t_cub *cub)
{
	// draw_square_player(cub, cub->p.px, cub->p.py, 10, RED);
	// draw_square(cub, cub->p.pdx*3, cub->p.pdy*3, 7, RED);

	/* view direction */
	// draw_line(cub, cub->p.px, cub->p.py, cub->p.px + cub->p.pdx*5, \
	// 	cub->p.py + cub->p.pdy*5, RED, 0);
	
	/* point direction */
	my_mlx_pixel_put(cub, cub->p.px + cub->p.pdx*5, cub->p.py + cub->p.pdy*5, GREEN);

	/* point of view */
	draw_line(cub, cub->p.px, cub->p.py, cub->p.px + sin(M_PI - cub->p.pa)*10,\
		cub->p.py - cos(M_PI - cub->p.pa)*10, BLUE, 0);
	draw_line(cub, cub->p.px, cub->p.py, cub->p.px - sin(M_PI - cub->p.pa)*10,\
		cub->p.py + cos(M_PI - cub->p.pa)*10, BLUE, 0);

	
}

void	draw_map (t_cub *cub)
{
	int	px;
	int	py;
	
	for (int y = 0; y < cub->map_y; y++)
	{
		for (int x = 0; x <cub->map_x; x++)
		{
			px = x * cub->map_s;
			py = y * cub->map_s;
			if (cub->map[(y * cub->map_x) + x] == 1)
				draw_square(cub, px, py, cub->map_s, 0xffffff);
			draw_line(cub, px, py, px + cub->map_s, py, 0xff, 0);
			draw_line(cub, px, py, px, py + cub->map_s, 0xff, 0);
		}
	}
}



void    draw(t_cub *cub)
{
	ft_bzero(cub->addr, SCREEN_HEIGHT * SCREEN_WIDTH * (cub->bpp / 8));
	// draw_player(cub);
	draw_ray(cub);
	// draw_map(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
}
