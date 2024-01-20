/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:17:34 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/20 09:12:34 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **sp)
{
	int	i;

	i = -1;
	while (sp[++i])
		free (sp[i]);
	free (sp);
}

void	free_split_n(char **sp, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free (sp[i++]);
	free (sp);
}

void	free_file(t_file *file)
{
	if (file->wall_n)
		free (file->wall_n);
	if (file->wall_e)
		free (file->wall_e);
	if (file->wall_w)
		free (file->wall_w);
	if (file->wall_s)
		free (file->wall_s);
	if (file->map)
		free_split_n(file->map, file->map_h);
}
