/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:00:07 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/03 10:43:39 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	fill_map(t_vars *vars, char **map, char *line, int fd)
{
	int	i;
	int	r;

	r = 0;
	while (line != NULL)
	{
		i = 0;
		map[r] = ft_strdup(line);
		if (!map[r])
			return ((int)free_memory(map, line, r));
		while (line[i] != '\0' && line[i] != '\n')
		{
			if (fill_count(vars, line[i], i, r) == 0)
			{
				perror("Error\nInvalid map");
				printf("here\n");
				free(map[r]);
				return ((int)free_memory(map, line, r));
			}
			i++;
		}
		r++;
		free(line);
		line = get_next_line(fd);
	}
	return (r);
}

void	init_vars(t_vars *vars)
{
	vars->door_count = 0;
	vars->character.rotation_a = 0;
	vars->character.mv_side = 0;
	vars->character.mv_degree = 0;
	vars->character.mv_dir = 0;
	vars->floor_count = 0;
	vars->wall_count = 0;
	vars->monster_count = 0;
	vars->character_count = 0;
}

int	fill_count(t_vars *vars, char c, int i, int r)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		vars->floor_count++;
	if (c == '1')
		vars->wall_count++;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		c = '0';
		vars->character_count++;
		vars->character.side = c;
		vars->character.x = i;
		vars->character.y = r;
	}
	// else if (c != ' ')
	// 	return (0);
	return (1);
}
