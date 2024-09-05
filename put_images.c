/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:42:50 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/05 11:56:15 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_image(int count, t_vars *vars, void *path,
					t_stuff_position *position)
{
	int	i;

	i = 0;
	while (i < count)
	{
		mlx_image_to_window(vars->mlx,
			path, position[i].x, position[i].y);
		i++;
	}
}

int	wall_check(int x, int y, int wall_count, t_vars *vars)
{
	int	i;

	i = 0;
	while (i != wall_count)
	{
		if (x < vars->wall_position[i].x + 5
			&& x + 5 > vars->wall_position[i].x
			&& y < vars->wall_position[i].y + 5
			&& y + 5 > vars->wall_position[i].y)
			return (1);
		i++;
	}
	return (0);
}
