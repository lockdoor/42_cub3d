/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 08:52:47 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/19 15:42:55 by pnamnil          ###   ########.fr       */
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

int		open_1(char *file)
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



void	get_list(t_list **lst, char *file)
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
			break;
		if (*line == '\n' && size < 7)
		{
			free (line);
			continue;
		}
		lstnew = ft_lstnew(line);
		if (!lstnew)
		{
			perror("get_list");
			free (line);
			ft_lstclear(lst, &free);
			exit(EXIT_FAILURE);
		}
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
	{
		ft_putstr_fd("cub3d: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putendl_fd(": file format error", 2);
		exit (EXIT_FAILURE);
	}
	
	// debug	
	// ft_lstiter(lst, &print_list_map);

	init_file_wall(file, &lst);

	// debug
	print_file_wall(file);

	init_floor_ceil(file, &lst);

	// debug
	printf ("F: %#X\n", file->floor);
	printf ("C: %#X\n", file->ceiling);

	init_map(file, &lst);

	// debug
	// print_map_char(file);
	
	// debug	
	// ft_lstiter(lst, &print_list_map);
	
	// free_file(file);
	ft_lstclear(&lst, &free);
}