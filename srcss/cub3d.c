/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 05:44:12 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/18 10:18:24 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
	{
		ft_putendl_fd("CUB3D must have only one map.", 2);
		return (EXIT_FAILURE);
	}
	read_map(&cub, argv[1]);
	// (void) argv;
	// init_cub(&cub);
	// init_hook(&cub);
	// run_cub(&cub);
	// mlx_loop(cub.mlx);
	return (0);
}