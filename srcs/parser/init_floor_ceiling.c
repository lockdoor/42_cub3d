/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:26:46 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/20 13:45:11 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	1 trim the line with space and newline
	2 make sure first character is F or S
		if not clean everything then exit
	3 sent address behind first character to split with comma
	4 if array of split not equel 3 exit program
		trim all string
	5 check all string is digit if not exit program
	6 check if digit more then 3 character exit program
	7 sent digit to atoi if more then 255 exit program
	8 bitwise all string to color u_int 32
	9 set color to cub
*/

/* check all digit and digit length must less then four */
static int	check_all_digit(char **sp)
{
	int		i;
	char	*s;

	while (*sp)
	{
		s = ft_strtrim(*sp, " \n");
		if (!s)
			return (EXIT_FAILURE);
		i = -1;
		while (s[++i])
		{
			if (!ft_isdigit(s[i]) || i > 2)
			{
				ft_putstr_fd (s, 2);
				ft_putendl_fd(": check_all_digit", 2);
				free (s);
				return (EXIT_FAILURE);
			}
		}
		free (s);
		sp++ ;
	}
	return (0);
}

static int	get_color(int *c, char **sp)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(sp[0]);
	g = ft_atoi(sp[1]);
	b = ft_atoi(sp[2]);
	if (r > 255 || g > 255 || b > 255)
	{
		ft_putendl_fd("get_color", 2);
		return (3);
	}
	*c = r << 16 | g << 8 | b;
	return (0);
}

static int	get_floor_ceil_color_1(int *c, char **sp)
{
	if (split_len(sp) != 3)
	{
		free_split(sp);
		return (5);
	}
	if (check_all_digit(sp))
	{
		free_split(sp);
		return (2);
	}
	if (get_color(c, sp))
	{
		free_split(sp);
		return (6);
	}
	free_split(sp);
	return (EXIT_SUCCESS);
}

static int	get_floor_ceil_color(int *c, t_list *lst, int a)
{
	char	*s;
	char	**sp;

	s = ft_strtrim((char *)lst->content, " \n");
	if (!s)
		return (8);
	if (*s != a)
	{
		free (s);
		return (7);
	}
	sp = ft_split(s + 1, ',');
	free (s);
	if (!sp)
		return (EXIT_FAILURE);
	return (get_floor_ceil_color_1(c, sp));
}

void	init_floor_ceil(t_file *file, t_list **lst)
{
	if (get_floor_ceil_color(&file->floor, *lst, 'F'))
		error_init_file(file, lst, "cub3d: cannot init Floor");
	*lst = free_one_node(*lst);
	if (get_floor_ceil_color(&file->ceiling, *lst, 'C'))
		error_init_file(file, lst, "cub3d: cannot init Ceiling");
	*lst = free_one_node(*lst);
}
