/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:36:21 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/09 14:02:13 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <math.h>

# define TITLE "cub3d"

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640

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

# define LEN 5

# define RED 0xff0000
# define GREEN 0xff00
# define BLUE 0xff

typedef struct s_player
{
	double	px;
	double	py;
	double	pdx;
	double	pdy;
	double	pa;
}	t_player;

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	void	*img;

	// addr group
	char	*addr;
	int		bpp;
	int		ll;
	int		endien;

	// map group
	int		*map;
	int		map_x;
	int		map_y;
	int		map_s;
	
	t_player	p;
}	t_cub;


// draw.c
void	draw(t_cub *cub);

#endif