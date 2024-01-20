/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 05:52:12 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/20 09:11:54 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_list_map(void *content)
{
	printf("%s", (char *)content);
}

void	print_file_wall(t_file *file)
{
	printf ("print_file_wall file->wall_n: %s\n", file->wall_n);
	printf ("print_file_wall file->wall_s: %s\n", file->wall_s);
	printf ("print_file_wall file->wall_w: %s\n", file->wall_w);
	printf ("print_file_wall file->wall_e: %s\n", file->wall_e);
}

void	print_map_char(t_file *file)
{
	char	**map;
	int		y;
	int		x;

	map = file->map;
	y = 0;
	while (y < file->map_h)
	{
		x = 0;
		while (x < file->map_w)
		{
			ft_putchar_fd(map[y][x], 1);
			x++ ;
		}
		ft_putchar_fd('\n', 1);
		y++ ;
	}
}

void	print_split(char **sp)
{
	while (*sp)
		printf ("%s\n", *sp++);
}
