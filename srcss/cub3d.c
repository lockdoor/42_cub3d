/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 05:44:12 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/13 07:11:15 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_cub	cub;

	// print_map(worldMap);
	init_cub(&cub);
	init_hook(&cub);
	run_cub(&cub);
	mlx_loop(cub.mlx);
	return (0);
}