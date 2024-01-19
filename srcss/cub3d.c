/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 05:44:12 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/19 15:44:16 by pnamnil          ###   ########.fr       */
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
	ft_bzero(&cub, sizeof(t_cub));
	read_map(&cub.file, argv[1]);
	// (void) argv;
	init_cub(&cub);
	init_hook(&cub);
	run_cub(&cub);
	mlx_loop(cub.mlx);
	return (0);
}