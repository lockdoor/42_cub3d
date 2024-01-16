/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 06:19:00 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/15 17:10:37 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel(t_cub *cub, float x, int y)
{
	x = x * cub->pixel;
	// x = (int)x * cub->pixel;
	return (x + y);
}

/*
void	draw_player(t_cub *cub)
{
	double	x_1;
	double	y_1;
	double	x_2;
	double	y_2;

	x_1 = cub->pos_x * cub->pixel;
	y_1 = cub->pos_y * cub->pixel;
	// x_2 = x_1 + cub->pdx * 50;
	// y_2 = y_1 + cub->pdy * 50;
	x_2 = -sin(cub->plane_x) * 50;
	y_2 = cos(cub->plane_x) * 50;
	draw_line (cub, x_1, y_1, x_2, y_2, RGB_WHITE);
	// printf ("x_1: %f, y_1: %f, x_2: %f, y_2: %f\n", x_1, y_1, x_2, y_2);


	// draw_line(cub, x_1, y_1, x_1 + sin(M_PI - cub->pa)*30,\
	// 	y_1 - cos(M_PI - cub->pa)*50, RGB_BLUE);
	// draw_line(cub, x_1, y_1, x_1 - sin(M_PI - cub->pa)*30,\
	// 	y_1 + cos(M_PI - cub->pa)*50, RGB_BLUE);
}
*/

void	run_cub(t_cub *cub)
{
	ft_bzero(cub->addr, cub->scr_h * cub->scr_w * (cub->bpp / 8));
	// print_map(cub->map, cub->map_h, cub->map_w);
	draw_map_2_d(cub);
	// draw_player(cub);
	my_mlx_pixel_put(cub, cub->pos_x * cub->pixel, cub->pos_y * cub->pixel, RGB_GREEN);


	int w = cub->scr_w;
	// int w = 1;
	for (int x = 0; x < w; x++)
	{
		double cameraX = 2 * x / (double)w - 1;
		double rayDirX = cub->dir_x + cub->plane_x * cameraX;
		double rayDirY = cub->dir_y + cub->plane_y * cameraX;

		int mapX = (int) cub->pos_x;
		int mapY = (int) cub->pos_y;

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		
		/* debug */
// 		printf ("\ncameraX: %f, rayDirX: %f, rayDirY: %f\n\
// mapX: %d, mapY: %d, deltaDistX: %f, deltaDistY: %f\n\
// pos_x: %f, pos_y: %f\n", \
// 		cameraX, rayDirX, rayDirY, mapX, mapY, deltaDistX, deltaDistY, cub->pos_x, cub->pos_y);

		
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist

		double sideDistX;
		double sideDistY;
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (cub->pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub->pos_x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (cub->pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub->pos_y) * deltaDistY;
		}
		if (x == 0 || x == w - 1 || x == w / 2)
		{
			printf ("\nrayX, %f, rayY: %f, delX: %f, delY: %f\n", \
			rayDirX, rayDirY, deltaDistX, deltaDistY);
		}
		
		//perform DDA
		// double dx = cub->pos_x;
		// double dy = cub->pos_y;
		while(hit == 0)
		// while(cub->map[mapX][mapY] > 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				// dx += rayDirX;
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{	
				// dy += rayDirY;
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (x == 0 || x == w - 1 || x == w / 2)
			{
				my_mlx_pixel_put(cub, mapX * cub->pixel, mapY * cub->pixel, RGB_WHITE);
				printf ("x: %d, side: %d, mx: %d, my: %d, sideX: %f, sideY: %f\n", \
					x, side, mapX, mapY, sideDistX, sideDistY);
			}
			//Check if ray has hit a wall
			if(cub->map[mapX][mapY] > 0)
				hit = 1;
			// else{
			// 	if (!side)
			// 		dx += rayDirX;
			// 	else
			// 		dy += rayDirY;
			// }
		}

		// hit = 0;
		double dx = cub->pos_x;
		double dy = cub->pos_y;
		while (cub->map[(int) dy][(int) dx] == 0){
			dy += rayDirY;
			dx += rayDirX;
			// if ()
			// 	hit = 1;
		}

		if (x == 0 || x == w - 1 || x == w / 2){
			// printf ("x/w: %d/%d, px: %.2f, py: %.2f, mx: %d, my: %d, sdx: %.2f, sdy: %.2f, side: %d\n", \
			// x, w, cub->pos_x, cub->pos_y, mapX, mapY, sideDistX, sideDistY, side);
			// draw_line(cub, cub->pos_x * cub->pixel, cub->pos_y * cub->pixel, \
			// 	mapX * cub->pixel, mapY * cub->pixel, RGB_WHITE);
			printf ("dx: %f, dy: %f, dx: %d, dy: %d, var: %d\n", \
			dx, dy, (int)dx, (int)dy, cub->map[(int) dy][(int) dx]);
			double px = cub->pos_x * cub->pixel;
			double py = cub->pos_y * cub->pixel;
			double pdx = dx * cub->pixel;
			double pdy = dy * cub->pixel;
			draw_line(cub, px, py, pdx, pdy, RGB_WHITE);
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
}
