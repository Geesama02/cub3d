/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:47:51 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/15 09:38:56 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <limits.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "get-next-line/get_next_line.h"

// const int g_size = 32;

typedef struct s_stuff_position
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		x;
	int		y;
}	t_stuff_position;

typedef struct s_data
{
	mlx_image_t	*img;
	int		width;
	int		height;
}	t_data;

typedef struct s_character
{
	t_data		frames[6];
	int			current_frame;
	char		side;
	double		rotation_a;
	double		x;
	double		y;
	int			mv_side;
	int			mv_degree;
	int			mv_dir;
}	t_character;

typedef struct s_vars
{
	t_stuff_position	*floor_position;
	t_stuff_position	*wall_position;
	t_character			character;
	t_stuff_position	door;
	mlx_texture_t		*front_wall;
	mlx_texture_t		*back_wall;
	mlx_texture_t		*left_wall;
	mlx_texture_t		*right_wall;
	char 				**map;
	void				*mlx;
	mlx_image_t				*win;
	mlx_image_t				*map_img;
	double					wall_x;
	double					wall_y;
	int					s_width;
	int					s_height;
	double					view_field;
	int					character_count;
	int					monster_count;
	int					door_count;
	int					floor_count;
	int					wall_count;
	int					chest_count;
}	t_vars;

void	*free_memory(char **map, char *line, int r);
void	free_vars(t_vars *vars);
char	**count_elements(t_vars *vars, char *file);
int		get_map(t_vars *vars, char *filename);
void	*handle_invalid_map(char **map, char *line, int r);
void	init_vars(t_vars *vars);
int		fill_map(t_vars *vars, char **map, char *line, int fd);
int		fill_count(t_vars *vars, char c, int i, int r);
void	process_lines(t_vars *vars, char *filename);
void	allocate_memory(t_vars *vars);
void	put_image(int count, t_vars *vars, void *path,
					t_stuff_position *position);
void	start_game(t_vars *vars, int i, int j);
void	free_and_perror(t_vars *vars, char *str);
int	wall_check(int x, int y, int wall_count, t_vars *vars);
void	move_sides(int keycode, t_vars *vars);
void	set_imgs(t_vars *vars);
int get_rgba(int r, int g, int b, int a);
int get_r(int rgba);
int get_g(int rgba);
int get_b(int rgba);
int get_a(int rgba);

#endif