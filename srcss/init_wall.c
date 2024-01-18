/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:58:47 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/18 16:23:42 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// new algorithim collect all file before mlx_init
char	*find_texture(t_list *lst, char *name)
{
	char	**sp;
	char	*end_of_line;

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
	free (sp[0]);
	free (sp);
	end_of_line = ft_strchr(sp[1], '\n');
	*end_of_line = 0;
	return (sp[1]);
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
void	error_init_file_wall(t_file *file, t_list **lst, char *name)
{
	if (file->wall_n)
		free (file->wall_n);
	if (file->wall_e)
		free (file->wall_e);
	if (file->wall_w)
		free (file->wall_w);
	if (file->wall_s)
		free (file->wall_s);
	ft_lstclear (lst, &free);
	ft_putstr_fd ("cub3d: init_file_wall: cannot find wall: ", 2);
	ft_putendl_fd (name, 2);
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
		error_init_file_wall(file, lst, "NO");
	*lst = free_one_node(*lst);
	
	file->wall_s = find_texture(*lst, "SO");
	if (!file->wall_s)
		error_init_file_wall(file, lst, "SO");
	*lst = free_one_node(*lst);
	
	file->wall_w = find_texture(*lst, "WE");
	if (!file->wall_w)
		error_init_file_wall(file, lst, "WE");
	*lst = free_one_node(*lst);
	
	file->wall_e = find_texture(*lst, "EA");
	if (!file->wall_e)
		error_init_file_wall(file, lst, "EA");
	*lst = free_one_node(*lst);
}

/*
void	init_all_wall(t_cub *cub, t_list **lst)
{
	if (init_wall(cub, &cub->wall_n, lst, "NO"))
	{
		ft_lstclear(lst, &free);
		exit (EXIT_FAILURE);
	}
	if (init_wall(cub, &cub->wall_n, lst, "SO"))
	{
		ft_lstclear(lst, &free);
		mlx_destroy_image(cub->mlx, cub->wall_n.img);
		exit (EXIT_FAILURE);
	}
	if (init_wall(cub, &cub->wall_n, lst, "WE"))
	{
		ft_lstclear(lst, &free);
		mlx_destroy_image(cub->mlx, cub->wall_n.img);
		mlx_destroy_image(cub->mlx, cub->wall_s.img);
		exit (EXIT_FAILURE);
	}
	if (init_wall(cub, &cub->wall_n, lst, "EA"))
	{
		ft_lstclear(lst, &free);
		mlx_destroy_image(cub->mlx, cub->wall_n.img);
		mlx_destroy_image(cub->mlx, cub->wall_s.img);
		mlx_destroy_image(cub->mlx, cub->wall_w.img);
		exit (EXIT_FAILURE);
	}
}
*/