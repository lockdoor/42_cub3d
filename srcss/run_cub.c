/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 06:19:00 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/17 14:46:19 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	verLine(t_cub *cub, t_img *img, int x, int color)
{
	while(cub->draw_start <= cub->draw_end)
	{
		my_mlx_pixel_put(img, x, cub->draw_start, color);
		cub->draw_start++ ;
	}
}

void	pre_run_1(t_cub *cub, t_img *img, int x)
{
		cub->camera_x = 2 * x / (double)img->scr_w - 1;
		cub->ray_dir_x = cub->dir_x + cub->plane_x * cub->camera_x;
		cub->ray_dir_y = cub->dir_y + cub->plane_y * cub->camera_x;
		cub->map_x = (int) cub->pos_x;
		cub->map_y = (int) cub->pos_y;
		cub->delta_dist_x = (cub->ray_dir_x == 0) ? 1e30 : fabs(1 / cub->ray_dir_x);
		cub->delta_dist_y = (cub->ray_dir_y == 0) ? 1e30 : fabs(1 / cub->ray_dir_y);
}

void	pre_run_2(t_cub *cub)
{
	if(cub->ray_dir_x < 0)
	{
		cub->step_x = -1;
		cub->side_dist_x = (cub->pos_x - cub->map_x) * cub->delta_dist_x;
	}
	else
	{
		cub->step_x = 1;
		cub->side_dist_x = (cub->map_x + 1.0 - cub->pos_x) * cub->delta_dist_x;
	}
	if(cub->ray_dir_y < 0)
	{
		cub->step_y = -1;
		cub->side_dist_y = (cub->pos_y - cub->map_y) * cub->delta_dist_y;
	}
	else
	{
		cub->step_y = 1;
		cub->side_dist_y = (cub->map_y + 1.0 - cub->pos_y) * cub->delta_dist_y;
	}
}

void	cal_dda(t_cub *cub)
{
	int	hit;

	hit = 0;
	while(hit == 0)
	{
		if(cub->side_dist_x < cub->side_dist_y)
		{
			cub->side_dist_x += cub->delta_dist_x;
			cub->map_x += cub->step_x;
			cub->side = 0;
		}
		else
		{	
			cub->side_dist_y += cub->delta_dist_y;
			cub->map_y += cub->step_y;
			cub->side = 1;
		}
		if(cub->map[cub->map_x][cub->map_y] > 0)
			hit = 1;
	}
}

void	cal_wall(t_cub *cub, t_img *img)
{

	if(cub->side == 0)
		cub->perp_wall_dist = (cub->side_dist_x - cub->delta_dist_x);
	else
		cub->perp_wall_dist = (cub->side_dist_y - cub->delta_dist_y);

	//Calculate height of line to draw on screen
	cub->line_height = (int)(img->scr_h / cub->perp_wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	cub->draw_start = -cub->line_height / 2 + img->scr_h / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = cub->line_height / 2 + img->scr_h / 2;
	if (cub->draw_end >= img->scr_h)
		cub->draw_end = img->scr_h - 1;
}

//give x and y sides different brightness
//choose wall color
int	wall_color(t_cub *cub)
{
	int color;
	
	color = cub->map[cub->map_x][cub->map_y];
	if (color == 1)
		color = RGB_RED;
	else if (color == 2)
		color = RGB_GREEN;
	else if (color == 3)
		color = RGB_BLUE;
	else if (color == 4)
		color = RGB_WHITE;
	else
		color = RGB_YELLOW;

	if(cub->side == 1) {color = color / 2;}
	return (color);
}

u_int32_t	my_mlx_pixel_get(t_img *img, int x, int y)
{
	u_int32_t	color;
	char		*dst;

	if (x >= img->scr_w || y >= img->scr_h || x < 0 || y < 0)
		return (0);
	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void	write_texture(t_cub *cub, t_img *img, int x)
{
	
      //texturing calculations
    //   int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
	double wallX; //where exactly the wall was hit
	if (cub->side == 0) wallX = cub->pos_y + cub->perp_wall_dist * cub->ray_dir_y;
	else wallX = cub->pos_x + cub->perp_wall_dist * cub->ray_dir_x;
	wallX -= floor((wallX));

	//x coordinate on the texture
	int tex_x = (int)(wallX * (double)TEXTURE_W);
	
	// debug
	// printf ("x: %d, tex_x: %d\n", x, tex_x);
	
	if(cub->side == 0 && cub->ray_dir_x > 0) tex_x = TEXTURE_W - tex_x - 1;
	if(cub->side == 1 && cub->ray_dir_y < 0) tex_x = TEXTURE_W - tex_x - 1;

	double step = 1.0 * TEXTURE_H / cub->line_height;
	double tex_pos = (cub->draw_start - img->scr_h / 2 + cub->line_height / 2) * step;
	for (int y = cub->draw_start; y < cub->draw_end; y++)
	{
		int tex_y = (int)tex_pos & (TEXTURE_H - 1);
		
		tex_pos += step;
		u_int32_t color = my_mlx_pixel_get(&cub->wall, tex_x, tex_y);
		if (cub->side == 1) color = (color >> 1) & 8355711;
		
		// debug
		// if (x == img->scr_w / 2)
		// {
		// 	printf ("write_texture: tex_x: %d, tex_y: %d, color: %u\n", \
		// 		tex_x, tex_y, color);
		// }
		
		my_mlx_pixel_put(img, x, y, color);
	}
}

void	run_cub(t_cub *cub)
{
	ft_bzero(cub->mini.addr, \
		cub->mini.scr_h * cub->mini.scr_w * (cub->mini.bpp / 8));
	ft_bzero(cub->main.addr, \
		cub->main.scr_h * cub->main.scr_w * (cub->main.bpp / 8));
	map_2_d(cub, &cub->mini);
	for (int x = 0; x < cub->mini.scr_w; x++)
	{
		pre_run_1 (cub, &cub->mini, x);
		pre_run_2 (cub);
		cal_dda (cub);	
		cal_wall (cub, &cub->mini);
		draw_ray_2_d (cub, &cub->mini);
	}
	for(int x = 0; x < cub->main.scr_w; x++)
	{
		pre_run_1 (cub, &cub->main, x);
		pre_run_2 (cub);
		cal_dda (cub);	
		cal_wall (cub, &cub->main);
		// verLine(cub, &cub->main, x, wall_color(cub));
		write_texture(cub, &cub->main, x);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->main.img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini.img, 0, 0);
}
