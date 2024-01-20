/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:58:47 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/20 11:13:38 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*find_texture(t_list *lst, char *name)
{
	char	**sp;
	char	*s;

	if (!lst)
		return (NULL);
	sp = ft_split((char *)lst->content, 32);
	if (!sp)
		return (NULL);
	if (split_len(sp) != 2)
	{
		free_split(sp);
		return (NULL);
	}
	if (ft_strncmp(sp[0], name, -1))
	{
		free_split(sp);
		return (NULL);
	}
	s = ft_strtrim(sp[1], "\n");
	free_split(sp);
	return (s);
}

// if can not get file name it clean everything exit program 
void	init_file_wall(t_file *file, t_list **lst)
{
	file->wall_n = find_texture(*lst, "NO");
	if (!file->wall_n)
		error_init_file(file, lst, "init_file_wall: cannot find wall: NO");
	*lst = free_one_node(*lst);
	file->wall_s = find_texture(*lst, "SO");
	if (!file->wall_s)
		error_init_file(file, lst, "init_file_wall: cannot find wall: SO");
	*lst = free_one_node(*lst);
	file->wall_w = find_texture(*lst, "WE");
	if (!file->wall_w)
		error_init_file(file, lst, "init_file_wall: cannot find wall: WE");
	*lst = free_one_node(*lst);
	file->wall_e = find_texture(*lst, "EA");
	if (!file->wall_e)
		error_init_file(file, lst, "init_file_wall: cannot find wall: EA");
	*lst = free_one_node(*lst);
}

// utility from init_map
void	count_size(t_file *file, t_list *lst)
{
	int	len;

	while (lst)
	{
		file->map_h += 1;
		len = (int) ft_strlen((char *)lst->content);
		if (len > file->map_w)
			file->map_w = len;
		lst = lst->next;
	}
}

// utility from init_map
char	**clone_map(t_file *file)
{
	char	**map;
	int		i;

	map = (char **) malloc (sizeof(char *) * file->map_h);
	if (!map)
		return (NULL);
	i = -1;
	while (++i < file->map_h)
	{
		map[i] = (char *) malloc (file->map_w);
		if (!map[i])
		{
			free_split_n(map, i);
			return (NULL);
		}
		ft_memmove(map[i], file->map[i], file->map_w);
	}
	return (map);
}
