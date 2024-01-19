/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:58:47 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/19 15:20:31 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// new algorithim collect all file before mlx_init
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

/*
int	init_wall(t_cub *cub, t_img *img, t_list **lst, char *name)
{
	char	*wall_file;
	t_list	*tmp;

	tmp = *lst;
	wall_file = find_texture((char *)tmp->content, name);
	if (!wall_file)
	{
		ft_putstr_fd ("cub3d: init_wall: cannot find wall: ", 2);
		ft_putendl_fd ("NO", 2);
		return (EXIT_FAILURE);
	}
	if (wall_to_img(cub, img, wall_file))
	{
		free (wall_file);
		return (EXIT_FAILURE);
	}
	*lst = tmp->next;
	free (tmp->content);
	free (tmp);
	return (0);
}
*/

// new algorithim collect all file before mlx_init
void	error_init_file(t_file *file, t_list **lst, char *mes)
{
	free_file(file);
	ft_lstclear(lst, &free);
	ft_putendl_fd (mes, 2);
	exit (EXIT_FAILURE);
}

// new algorithim collect all file before mlx_init
t_list	*free_one_node(t_list *lst)
{
	t_list	*next;

	next = lst->next;
	free (lst->content);
	free (lst);
	return (next);
}

// new algorithim collect all file before mlx_init
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

