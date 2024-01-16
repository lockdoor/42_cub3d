/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 05:52:12 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/13 06:58:21 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	print_map(int map[MAP_H][MAP_W])
// {
// 	for (int i = 0; i < MAP_H; i++)
// 	{
// 		for (int j = 0; j < MAP_W; j++)
// 		{
// 			printf ("%2d", map[i][j]);
// 		}
// 		printf ("\n");
// 	}
// }

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
