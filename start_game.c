/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:27:24 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/31 09:39:50 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	key_hook(mlx_key_data_t keydata, void *vars)
{
	t_vars *my_vars = vars;
	// if (keycode == 53)
	// 	close_program(vars);
	// if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	// 	my_vars->character.rotation_a += (3 * (M_PI / 180)) * my_vars->character.mv_side;
	// if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	my_vars->character.rotation_a += (3 * (M_PI / 180)) * my_vars->character.mv_side;
	my_vars->character.frames[0].img->instances[0].x += cos(my_vars->character.rotation_a) * 5 * my_vars->character.mv_dir;
	my_vars->character.frames[0].img->instances[0].y += sin(my_vars->character.rotation_a) * 5 * my_vars->character.mv_dir;
	if (keydata.key == MLX_KEY_W)
	{
		my_vars->character.mv_dir = 1;
	}
	if (keydata.key == MLX_KEY_S)
	{
		my_vars->character.mv_dir = -1;
	}
	if (keydata.key == MLX_KEY_A)
	{
		my_vars->character.mv_side = 1;
	}
	if (keydata.key == MLX_KEY_D)
	{
		my_vars->character.mv_side = -1;
	}
	if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_A) && keydata.action == MLX_RELEASE)
		my_vars->character.mv_side = 0;
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S) && keydata.action == MLX_RELEASE)
		my_vars->character.mv_dir = 0;
}

void	move_sides(int keycode, t_vars *vars)
{
	if (keycode == 0 && wall_check(vars->character.x - 25,
			vars->character.y, vars->wall_count, vars) == 0)
	{
		vars->character.side = 'l';
		vars->character.x -= 25;
		vars->steps++;
	}
	else if (keycode == 2 && wall_check(vars->character.x + 25,
			vars->character.y, vars->wall_count, vars) == 0)
	{
		vars->character.side = 'r';
		vars->character.x += 25;
		vars->steps++;
	}
}
int	render_next_frame(t_vars *vars)
{
	put_image(vars->floor_count, vars, vars->floor_position->img,
		vars->floor_position);
	return (0);
}

static void	set_imgs(t_vars *vars)
{
	mlx_texture_t *img = mlx_load_png("./imgs/floor.png");
	mlx_texture_t *img2 = mlx_load_png("./imgs/wall.png");
	mlx_texture_t *img3 = mlx_load_png("./imgs/ball.png");
	vars->floor_position->img = mlx_texture_to_image(vars->mlx, img);
	vars->wall_position->img = mlx_texture_to_image(vars->mlx, img2);
	vars->character.frames[0].img = mlx_texture_to_image(vars->mlx, img3);
	if (vars->floor_position->img == NULL || vars->wall_position->img == NULL)
	{
		perror("Error\nInvalid textures");
		free_vars(vars);
		exit(5);
	}
}

void	start_game(t_vars *vars, int i, int j)
{
	// vars->chest_collected = 0;
	vars->mlx = mlx_init(j * 32, i * 32, "cub3d", false);
	if (vars->mlx == NULL)
		free_and_perror(vars, "Error\nmlx init failed");
	// vars->win = mlx_new_window(vars->mlx, j * 50, i * 50, "My Game");
	// if (vars->win == NULL)
	// 	free_and_perror(vars, "Error\nmlx window failed");
	mlx_key_hook(vars->mlx, key_hook, vars);
	set_imgs(vars);
	vars->character.current_frame = 0;
	put_image(vars->wall_count, vars, vars->wall_position->img,
		vars->wall_position);
	put_image(vars->floor_count, vars, vars->floor_position->img,
		vars->floor_position);
	mlx_image_to_window(vars->mlx,
			vars->character.frames[0].img, vars->character.x, vars->character.y);
	// mlx_hook(vars->win, 17, 0, close_program, vars);
	// mlx_loop_hook(vars->mlx, render_next_frame, vars);
	mlx_loop(vars->mlx);
}
