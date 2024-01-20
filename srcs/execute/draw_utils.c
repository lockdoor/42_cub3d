/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 07:15:40 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/20 10:52:55 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= img->scr_w || y >= img->scr_h || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

u_int32_t	my_mlx_pixel_get(t_img *img, int x, int y)
{
	u_int32_t	color;
	char		*dst;

	if (x >= img->scr_w || y >= img->scr_h || x < 0 || y < 0)
		return (0);
	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	draw_square(t_img *img, int px, int py, int color)
{
	int	y;
	int	x;

	y = -1;
	while (++y < img->pixel_y)
	{
		x = -1;
		while (++x < img->pixel_x)
			my_mlx_pixel_put(img, px + x, py + y, color);
	}
}

void	draw_line(t_img *img, t_line *line)
{
	double	step;
	double	dif[2];
	double	pos[2];
	int		i;

	dif[0] = line->px_2 - line->px_1;
	dif[1] = line->py_2 - line->py_1;
	step = fabs(dif[1]);
	if (fabs(dif[0]) > fabs(dif[1]))
		step = fabs(dif[0]);
	pos[0] = line->px_1;
	pos[1] = line->py_1;
	i = -1;
	while (++i < step)
	{
		my_mlx_pixel_put(img, pos[0], pos[1], line->color);
		pos[0] += dif[0] / step;
		pos[1] += dif[1] / step;
	}
}

void	clean_screen(t_img *img_1, t_img *img_2)
{
	ft_bzero(img_1->addr, img_1->scr_h * img_1->scr_w * (img_1->bpp / 8));
	ft_bzero(img_2->addr, img_2->scr_h * img_2->scr_w * (img_2->bpp / 8));
}
