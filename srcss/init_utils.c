/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:39:24 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/18 14:40:51 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	split_len(char **sp)
{
	int		i;

	i = 0;
	while (sp[i])
		i++ ;
	return (i);
}

void	free_split(char **sp)
{
	int	i;

	i = -1;
	while (sp[++i])
		free (sp[i]);
	free (sp);
}
