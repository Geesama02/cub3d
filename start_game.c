/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:27:24 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/04 15:02:11 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void draw_line(t_vars *vars, int x1, int y1, int x2, int y2)
{
    if (vars == NULL || vars->win == NULL)
    {
        printf("Error: NULL pointer\n");
        return;
    }
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int p = 2 * dy - dx;
	int x,y,xEnd;
    
    if (x1 > x2) {
        x = x2;
        y = y2;
        xEnd = x1;
    } else {
        x = x1;
        y = y1;
        xEnd = x2;
    }
    mlx_put_pixel(vars->win, x, y, 0xFF0000FF);
    
    while (x < xEnd) {
        x++;
        if (p < 0) {
            p += 2 * dy;
        } else {
            y++;
            p += 2 * (dy - dx);
        }
        mlx_put_pixel(vars->win, x, y, 0xFF0000FF);
    }
}

int	is_wall(t_vars *vars, int x, int y)
{
	return (vars->map[y / 32][x / 32] == '1');
}

void	get_h_intersect(t_vars *vars)
{
	int my_x = vars->character.frames[0].img->instances[0].x;
	int my_y = vars->character.frames[0].img->instances[0].y;
	int y_intersect = (my_y / 32) * 32;
	int x_intersect = 0;
	double view_field = 60 * (M_PI / 180);
	double rays = fmod((view_field / 2), M_PI * 2);
	if (rays < 0)
		rays += 2 * M_PI;
	if (rays < M_PI)
		y_intersect += 32;
	if (fabs(tan(rays)) < 0.000001)
		rays += 0.0001;
	x_intersect = my_x + ((my_y - y_intersect) / tan(rays));
	int next_y = 32;
	if (rays > M_PI)
		next_y *= -1;
	int next_x = 32 / tan(rays);
	if ((rays < (0.5 * M_PI) || rays > (1.5 * M_PI)) && next_x < 0)
		next_x *= -1;
	else if (!(rays < (0.5 * M_PI) || rays > (1.5 * M_PI)) && next_x > 0)
		next_x *= -1;
	printf("ray %lf\n", rays);
	printf("tan %lf\n", tan(rays));
	// mlx_put_pixel(vars->win, x_intersect, y_intersect, 0xFF0000FF);
	int h_x = x_intersect;
	int h_y = y_intersect;
	
	while (h_x <= vars->s_width && h_y <= vars->s_height && h_x > 0 && h_y > 0)
	{
		if (is_wall(vars, h_x, h_y))
		{
			mlx_put_pixel(vars->win, h_x, h_y, 0xFF0000FF);
			// draw_line(vars,my_x, my_y, h_x, h_y);
			printf("h_x %d\n", h_x);
			printf("h_y %d\n", h_y);
			break;
		}
		else
		{
			h_y += next_y;
			h_x += next_x;
		}
		// mlx_put_pixel(vars->win, h_x, h_y, 0xFF0000FF);
	}
}

void	key_hook(mlx_key_data_t keydata, void *vars)
{
	t_vars *my_vars = vars;
	// int rays_num = my_vars->s_width / 3;
	// double view_field = 60 * (M_PI / 180);
	int my_x = my_vars->character.frames[0].img->instances[0].x;
	int my_y = my_vars->character.frames[0].img->instances[0].y;

	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(my_vars->mlx);
		exit(0);
	}
	my_vars->character.rotation_a += (3 * (M_PI / 180)) * my_vars->character.mv_degree ;
	int x_move = ((cos(my_vars->character.rotation_a) * my_vars->character.mv_dir) + (sin(my_vars->character.rotation_a) * my_vars->character.mv_side)) * 5;
	int y_move = ((sin(my_vars->character.rotation_a) * my_vars->character.mv_dir) - (cos(my_vars->character.rotation_a) * my_vars->character.mv_side)) * 5;
	// if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	// 	my_vars->character.rotation_a += (3 * (M_PI / 180)) * my_vars->character.mv_side;
	// if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	if (my_vars->map[(my_y + 5 + y_move)/ 32][(my_x + 5 + x_move) / 32] != '1')
	{
		printf("degree -> %f\n", my_vars->character.rotation_a);
		// double view_field = 60 * (M_PI / 180);
		printf("ray degree -> %f\n", my_vars->character.rotation_a);
		// double ray_step = view_field / rays_num;
		int ray_end_x = my_x + cos(my_vars->character.rotation_a) * 60;
		int ray_end_y = my_y + sin(my_vars->character.rotation_a) * 60;
		printf("x -> %d\n", ray_end_x);
		printf("y -> %d\n", ray_end_y);
		draw_line(vars, my_x, my_y, ray_end_x, ray_end_y);

		// for (int i = 0; i < rays_num; i++) {
		// 	double ray_angle = my_vars->character.rotation_a + (ray_step * i); // Calculate the angle of the current ray
		// 	if (ray_angle < 0)
		// 		ray_angle += 2 * M_PI;
		// 	// Calculate the end point of the ray
		// 	int ray_end_x = my_x + cos(ray_angle) * 60;
		// 	int ray_end_y = my_y + sin(ray_angle) * 60;

		// 	// Draw the ray
		// 	draw_line(vars, my_x, my_y, ray_end_x, ray_end_y);
		// }
		// int i = 1;
		// double ray = ; 
		// double rays = fmod(my_vars->character.rotation_a - (view_field / 2), M_PI * 2);
		// // printf("rotation -> %f | vf -> %f\n", my_vars->character.rotation_a, view_field / 2);
		// if (fabs(tan(rays)) < 0.000001)
		// 	rays += 0.01;
		
		// printf("next_x %d\n", next_x);
		// printf("width %d\n", my_vars->s_width);
		// printf("height %d\n", my_vars->s_height);

		// x_intersect = (my_x / 32) * 32;
		// y_intersect = my_y + ((my_x - x_intersect) * tan(rays));
		// mlx_put_pixel(my_vars->win, x_intersect, y_intersect, 0xFF0000FF);
		// while (i < rays_num)
		// {
		// 	if (fabs(tan(rays)) >= 0.000001)
		// 	{
		// 		x_intersect = my_x + ((my_y - y_intersect) / tan(rays));
		// 		printf("ray %f\n", rays);
		// 		printf("tan %f\n", tan(rays));
		// 		printf("x_inter %d | y_inter %d\n", x_intersect, y_intersect);
		// 		draw_line(my_vars,my_x, my_y, x_intersect, y_intersect);
		// 		mlx_put_pixel(my_vars->win, x_intersect, y_intersect, 0xFF0000FF);
		// 	} 
		// 	rays += view_field / rays_num;
		// 	i++;
		// }
		// printf("x -> %f\n", ((cos(my_vars->character.rotation_a) * my_vars->character.mv_dir) + (sin(my_vars->character.rotation_a) * my_vars->character.mv_side)) * 5);
		// printf("y -> %f\n", ((sin(my_vars->character.rotation_a) * my_vars->character.mv_dir) - (cos(my_vars->character.rotation_a) * my_vars->character.mv_side)) * 5);
        // mlx_put_pixel(my_vars->win, my_x, my_y, 0xFF0000FF);
		my_vars->character.frames[0].img->instances[0].x += x_move;
		my_vars->character.frames[0].img->instances[0].y += y_move;
		// get_h_intersect(my_vars);
	}
	// my_vars->character.frames[0].img->instances[0].x += sin(my_vars->character.rotation_a) * 5 * my_vars->character.mv_side;
    // my_vars->character.frames[0].img->instances[0].y -= cos(my_vars->character.rotation_a) * 5 * my_vars->character.mv_side;
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
	if (keydata.key == MLX_KEY_LEFT)
		my_vars->character.mv_degree = 1;
	if (keydata.key == MLX_KEY_RIGHT)
		my_vars->character.mv_degree = -1;
	if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_A) && keydata.action == MLX_RELEASE)
		my_vars->character.mv_side = 0;
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S) && keydata.action == MLX_RELEASE)
		my_vars->character.mv_dir = 0;
	if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT) && keydata.action == MLX_RELEASE)
		my_vars->character.mv_degree = 0;
}

void	move_sides(int keycode, t_vars *vars)
{
	if (keycode == 0 && wall_check(vars->character.x - 25,
			vars->character.y, vars->wall_count, vars) == 0)
	{
		vars->character.side = 'l';
		vars->character.x -= 25;
	}
	else if (keycode == 2 && wall_check(vars->character.x + 25,
			vars->character.y, vars->wall_count, vars) == 0)
	{
		vars->character.side = 'r';
		vars->character.x += 25;
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
	vars->win = mlx_new_image(vars->mlx, j * 32, i * 32);
	vars->s_height = i * 32;
	vars->s_width = j * 32;
	if (!vars->win)
		printf("Error\n");
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
	mlx_image_to_window(vars->mlx,
		vars->win, 0, 0);
	// mlx_put_pixel(vars->win, 0, 0, 0xFF0000FF);
	// mlx_hook(vars->win, 17, 0, close_program, vars);
	// mlx_loop_hook(vars->mlx, render_next_frame, vars);
	mlx_loop(vars->mlx);
}
