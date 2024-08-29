/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:01:29 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/29 14:00:39 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*free_memory(char **map, char *line, int r)
{
	while (r != 0)
		free(map[--r]);
	free(map);
	free(line);
	return (NULL);
}

void	free_vars(t_vars *vars)
{
	free(vars->floor_position);
	free(vars->wall_position);
}

void	*handle_invalid_map(char **map, char *line, int r)
{
	perror("Error\nInvalid map");
	return (free_memory(map, line, r));
}

void	free_and_perror(t_vars *vars, char *str)
{
	free_vars(vars);
	perror(str);
	exit(6);
}