/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:39:23 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/29 15:05:34 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


void	process_walls(t_vars *vars, char character, int i, int l)
{
	static int	wall_count;

	if (character == '1')
	{
		vars->wall_position[wall_count].x = l * 32;
		vars->wall_position[wall_count].y = i * 32;
		wall_count++;
	}
}

void	process_floor_and_player(t_vars *vars, char character, int i, int l)
{
	static int	floor_count;

	if (character == '0' || character == 'N' || character == 'S' || character == 'E' || character == 'W')
	{
		vars->floor_position[floor_count].x = l * 32;
		vars->floor_position[floor_count].y = i * 32;
		floor_count++;
	}
	if (character == 'N' || character == 'S' || character == 'E' || character == 'W')
	{
		vars->character.x = l * 32;
		vars->character.y = i * 32;
	}
}

static void	read_file(char *file_name, t_vars *vars, char **line, int *fd)
{
	*fd = open(file_name, O_RDONLY);
	if (*fd == -1)
	{
		free_vars(vars);
		perror("Map");
		exit(3);
	}
	*line = get_next_line(*fd);
	if (!*line)
	{
		free_vars(vars);
		perror("Error\nInvalid map");
		close(*fd);
		exit(4);
	}
}

void	process_lines(t_vars *vars, char *filename)
{
	int	l;
	char *line;
	int	fd;
	int i;
	int j;

	i = 0;
	line = NULL;
	read_file(filename, vars, &line, &fd);
	j = ft_strlen(line) - 1;
	while (line != NULL)
	{
		l = 0;
		while (line[l] != '\0' && line[l] != '\n')
		{
			process_floor_and_player(vars, line[l], i, l);
			process_walls(vars, line[l], i, l);
			l++;
		}
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	start_game(vars, i, j);
}
