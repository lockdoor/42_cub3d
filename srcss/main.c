/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:28:09 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/13 06:10:26 by pnamnil          ###   ########.fr       */
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


int	init_cub(t_cub *cub)
{
	cub->screen_w = screenWidth;
	cub->screen_h = screenHeight;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->screen_w, cub->screen_h, TITLE);
	cub->img = mlx_new_image(cub->mlx, cub->screen_w, cub->screen_h);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bpp, &cub->ll, &cub->endien);
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

// void print_pd(int key, t_player *p)
// {
// 	printf ("key: %d, pdx: %f, pdy: %f\n", key, p->pdx, p->pdy);
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
	// if (key == KEY_W)
	// {
	// 	// debug
	// 	// print_pd (key, p);
		
	// 	p->px += p->pdx;
	// 	p->py += p->pdy;
	// }
	// if (key == KEY_S)
	// {
	// 	// debug
	// 	// print_pd (key, p);
		
	// 	p->px -= p->pdx;
	// 	p->py -= p->pdy;
	// }
	// if (key == KEY_A)
	// {
	// 	// debug
	// 	// print_pd (key, p);
		
	// 	p->px += sin(M_PI - p->pa) * 5;
	// 	p->py += cos(M_PI - p->pa) * 5;
	// }
	// if (key == KEY_D)
	// {
	// 	// debug
	// 	// print_pd (key, p);
		
	// 	p->px -= sin(M_PI - p->pa) * 5;
	// 	p->py -= cos(M_PI - p->pa) * 5;
	// }
	// if (key == KEY_LEFT)
	// {
	// 	p->pa += 0.1;
	// 	if (p->pa > 2 * M_PI)
	// 		p->pa -= 2 * M_PI;
	// 	set_delta(p, LEN);
	// }
	// if (key == KEY_RIGHT)
	// {
	// 	p->pa -= 0.1;
	// 	if (p->pa < 0)
	// 		p->pa += 2 * M_PI;
	// 	set_delta(p, LEN);
	// }
	// draw(cub);
	return (0);
}

int	init_hook(t_cub *cub)
{
	mlx_hook(cub->win, ON_KEYDOWN, 0, &key_hook, cub);
	mlx_hook(cub->win, ON_DESTROY, 0, &on_destroy, cub);
	return (0);
}

void	verLine(t_cub *cub, int x, int drawStart, int drawEnd, int color)
{
	while(drawStart <= drawEnd)
	{
		my_mlx_pixel_put(cub, x, drawStart, color);
		drawStart++ ;
	}
}

int	main(void)
{
	t_cub	cub;

	init_cub(&cub);

	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	for (int x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		/* debug */
		// printf ("line: %3d, cameraX: %f, rayDirX: %f, rayDirY: %f\n", \
		// 	x, cameraX, rayDirX, rayDirY);

		
		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		
	
		//perform DDA
		while(hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(worldMap[mapX][mapY] > 0) hit = 1;
		}
		
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

		//choose wall color
		int color;
		switch(worldMap[mapX][mapY])
		{
		case 1:  color = 0xFF0000;    break; //red
		case 2:  color = 0xFF00;  break; //green
		case 3:  color = 0xFF;   break; //blue
		case 4:  color = 0xFFFFFF;  break; //white
		default: color = 0xFF0; break; //yellow
		}

		//give x and y sides different brightness
		if(side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		verLine(&cub, x, drawStart, drawEnd, color);
		
		// myfuntion
		// draw_line (&cub, posX * mapWidth, posY * mapHeight, \
		// 	sideDistX, sideDistY, 0xFF0000, 0);
		
		/* debug */
		// printf ("sideDistX: %f, sideDistY: %f\n", sideDistX, sideDistY);
	}

	// draw_line(&cub, 100, 100, 200, 200, 0xff0000, 0);
	mlx_put_image_to_window(cub.mlx, cub.win, cub.img, 0, 0);
	init_hook(&cub);
	mlx_loop(cub.mlx);
	return (0);
}