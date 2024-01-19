/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:19:34 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/19 13:25:05 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    count_size(t_file *file, t_list *lst)
{
    int  len;

    while (lst)
    {
        file->map_h += 1;
        len = (int) ft_strlen((char *)lst->content);
        if (len > file->map_w)
            file->map_w = len;
        lst = lst->next;
    }
}

void	make_map_arr_2(t_file *file, char *map, char *line)
{
	char	*s;
	int		len;

	ft_memset (map, 32, file->map_w);
	s = ft_strchr(line, '\n');
	if (s)
		len = ft_strlen(line) - 1;
	else
		len = ft_strlen(line);
	ft_strlcpy(map, line, len);
}

int     make_map_arr(t_file *file, t_list *lst)
{
	char	**map;
	int		i;

	map = (char **) ft_calloc (file->map_h,  sizeof(char *));
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

void	init_map(t_file *file, t_list **lst)
{
	// printf("init_map: map: %p\n", file->map);
    count_size(file, *lst);
    if (file->map_h < 3 || file->map_w < 3)
        error_init_file(file, lst, "map error 1");
    if (make_map_arr(file, *lst))
		error_init_file(file, lst, "map error 2");

	// flood_fill here
}
