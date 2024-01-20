/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:19:34 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/20 11:13:03 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	make_map_arr_2(t_file *file, char *map, char *line)
{
	char	*s;
	int		len;

	ft_memset (map, 32, file->map_w);
	s = ft_strchr(line, '\n');
	if (s)
		len = ft_strlen(line) - 1;
	else
		len = ft_strlen(line);
	ft_memmove(map, line, len);
}

static int	make_map_arr(t_file *file, t_list *lst)
{
	char	**map;
	int		i;

	map = (char **) ft_calloc (file->map_h, sizeof(char *));
	if (!map)
		return (EXIT_FAILURE);
	i = -1;
	while (lst)
	{
		map[++i] = (char *) malloc (file->map_w);
		if (!map[i])
		{
			free_split_n(map, i);
			return (EXIT_FAILURE);
		}
		make_map_arr_2(file, map[i], (char *)lst->content);
		lst = lst->next;
	}
	file->map = map;
	return (0);
}

static int	find_player(t_file *file, char **map)
{
	int	i;
	int	j;
	int	player_found;

	i = -1;
	player_found = 0;
	while (++i < file->map_h)
	{
		j = -1;
		while (++j < file->map_w)
		{
			if (ft_strchr("NEWS", map[i][j]))
			{
				file->player_x = j;
				file->player_y = i;
				file->player_view = map[i][j];
				player_found++ ;
				map[i][j] = '0';
			}
		}
	}
	if (player_found != 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	flood_fill(t_file *file, t_list **lst, int x, int y)
{
	if (x >= file->map_w || y >= file->map_h || x < 0 || y < 0)
		error_init_file (file, lst, "map error on flood fill");
	if (file->map[y][x] == '1')
		return ;
	if (file->map[y][x] != '0')
		error_init_file (file, lst, "map error on flood fill");
	file->map[y][x] = '1';
	flood_fill(file, lst, x + 1, y);
	flood_fill(file, lst, x - 1, y);
	flood_fill(file, lst, x, y + 1);
	flood_fill(file, lst, x, y - 1);
}

void	init_map(t_file *file, t_list **lst)
{
	char	**map;

	count_size(file, *lst);
	if (file->map_h < 3 || file->map_w < 3)
		error_init_file(file, lst, "map error map should more 3 raw 3 cal");
	if (make_map_arr(file, *lst))
		error_init_file(file, lst, "map error can not make map");
	if (find_player(file, file->map))
		error_init_file(file, lst, "map error on player position");
	map = clone_map(file);
	if (!map)
		error_init_file(file, lst, "map error can not clone map");
	flood_fill(file, lst, file->player_x, file->player_y);
	free_split_n(file->map, file->map_h);
	file->map = map;
}
