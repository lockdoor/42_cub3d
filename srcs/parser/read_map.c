/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 08:52:47 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/20 13:44:24 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	1. openfile if error it exit
	2. get_next_line to t_list if error it clean list and exit
	3. if list = NULL becouse file is empty or have only newline
		it exit
	4. begin collect filename for wall image
*/
t_list	*free_one_node(t_list *lst)
{
	t_list	*next;

	next = lst->next;
	free (lst->content);
	free (lst);
	return (next);
}

void	error_init_file(t_file *file, t_list **lst, char *mes)
{
	if (file)
		free_file(file);
	ft_lstclear(lst, &free);
	ft_putendl_fd (mes, 2);
	exit (EXIT_FAILURE);
}

static int	open_1(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror (file);
		exit (EXIT_FAILURE);
	}
	return (fd);
}

static void	get_list(t_list **lst, char *file)
{
	int		fd;
	char	*line;
	t_list	*lstnew;
	int		size;

	size = 0;
	fd = open_1(file);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line == '\n' && size < 7)
		{
			free (line);
			continue ;
		}
		lstnew = ft_lstnew(line);
		if (!lstnew)
			error_init_file(NULL, lst, "error on get_list");
		ft_lstadd_back(lst, lstnew);
		size++ ;
	}
	close(fd);
}

void	read_map(t_file *file, char *filename)
{
	t_list	*lst;

	lst = NULL;
	get_list(&lst, filename);
	if (!lst)
		error_init_file(file, &lst, "file format error");
	init_file_wall(file, &lst);
	init_floor_ceil(file, &lst);
	init_map(file, &lst);
	ft_lstclear(&lst, &free);
}
