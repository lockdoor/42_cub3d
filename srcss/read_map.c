/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 08:52:47 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/18 10:50:40 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	fd = open_1(file);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (*line == '\n')
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
		ft_lstadd_back(lst, ft_lstnew(line));
	}
	close(fd);
}

// debug
void	print_list_map(void *content)
{
	char	*s;

	s = (char *)content;
	printf("%s", s);
}

int	read_map(t_cub *cub, char *file)
{
	t_list	*lst;

	// (void) file;
	(void) cub;
	lst = NULL;
	get_list(&lst, file);

	// debug
	if (lst)
		ft_lstiter(lst, &print_list_map);
	ft_lstclear(&lst, &free);

	return (0);
	// exit (0);
}