/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 05:52:12 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/18 16:12:17 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(int **map, int y, int x)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			printf ("%2d", map[i][j]);
		}
		printf ("\n");
	}
}

void	print_list_map(void *content)
{
	char	*s;

	s = (char *)content;
	printf("%s", s);
}

void	print_file_wall(t_file *file)
{
	printf ("print_file_wall file->wall_n: %s\n", file->wall_n);
	printf ("print_file_wall file->wall_s: %s\n", file->wall_s);
	printf ("print_file_wall file->wall_w: %s\n", file->wall_w);
	printf ("print_file_wall file->wall_e: %s\n", file->wall_e);
}
