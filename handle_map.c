/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:52:58 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/02 10:11:58 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	count_rows(char *file)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Map");
		return (0);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

static int	read_file(char *file, int *fd, char **map, char **line)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		perror("Map");
		free(map);
		return (0);
	}
	*line = get_next_line(*fd);
	if (!*line)
	{
		free(map);
		perror("Error\nInvalid map");
		close(*fd);
		return (0);
	}
	return (1);
}

int	handle_file(char *file, t_vars *vars, char **map, int *r)
{
	char	*line;
	int		fd;

	line = NULL;
	if (!read_file(file, &fd, map, &line))
		return (0);
	*r = fill_map(vars, map, line, fd);
	if (*r == 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

char	**count_elements(t_vars *vars, char *file)
{
	int		r;
	int		row_count;
	char	**map;

	init_vars(vars);
	row_count = count_rows(file);
	if (row_count == 0)
		return (handle_invalid_map(NULL, NULL, 0));
	map = (char **)malloc(sizeof(char *) * row_count);
	if (!map)
		return (NULL);
	if (handle_file(file, vars, map, &r) == 0)
		return (NULL);
	if (vars->character_count != 1
		|| vars->floor_count == 0 || vars->wall_count == 0)
		return (handle_invalid_map(map, NULL, r));
	// free_memory(map, NULL, r);
	return (map);
}

