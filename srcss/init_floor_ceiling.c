/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:26:46 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/18 16:40:47 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
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
*/
int	get_floor_ceil_color(int *c, t_list *lst, int a)
{
	char	*s;
	int		i;

	s = ft_strtrim((char *)lst->content, " \n");
	if (!s)
		return (EXIT_FAILURE);
	if (*s != a)
	{
		free (s);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (s[i])
}

void	init_floor_ceil(t_cub *cub, t_list **lst)
{
	if (get_floor_ceil_color(&cub->floor, *lst, 'F'))
		
}