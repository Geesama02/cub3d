/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:31:17 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/29 11:32:02 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	handle_error(t_vars *vars)
{
	perror("Malloc");
	free(vars->floor_position);
	free(vars->wall_position);
	exit(5);
}

void	allocate_memory(t_vars *vars)
{
	vars->floor_position = (t_stuff_position *)malloc(
			sizeof(t_stuff_position) * vars->floor_count);
	vars->wall_position = (t_stuff_position *)malloc(
			sizeof(t_stuff_position) * vars->wall_count);
	if (!vars->floor_position || !vars->wall_position)
		handle_error(vars);
}