/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:33:52 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/10 13:05:35 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include "mlx.h"
# include <math.h>

# define ON_KEYUP 3
# define ON_KEYDOWN 2
# define ON_DESTROY 17
# define KEY_ESCAPE 53
# define KEY_W 13
# define KEY_S 1
# define KEY_D 2
# define KEY_A 0
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define TITLE "CUB3D"

typedef struct s_cub
{
	// map
	int		map_w;
	int		map_h;
	int		screen_w;
	int		screen_h;
	
	// mlx
	void	*mlx;
	void	*win;
	void	*img;

	// addr group
	char	*addr;
	int		bpp;
	int		ll;
	int		endien;

	// // map group
	// int		*map;
	// int		map_x;
	// int		map_y;
	// int		map_s;
}	t_cub;

#endif