/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:27:24 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/09 15:53:23 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void draw_line(t_vars *vars, int x1, int y1, int x2, int y2, int c)
{
    if (vars == NULL || vars->win == NULL)
    {
        printf("Error: NULL pointer\n");
        return;
    }

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
        mlx_put_pixel(vars->map_img, x1, y1, c);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y1 += sy;
        }
    }
}

int	is_wall(t_vars *vars, int x, int y)
{
	// printf("y wall -> %d | x wall -> %d\n", y, x);
	// mlx_put_pixel(vars->win, x, y, 0xFF0000FF);
	int x_axis = x / (32);
	int y_axis = y / (32);
	return (vars->map[y_axis][x_axis] == '1');
}

double	get_line_len(t_vars *vars, double x, double y)
{
	int my_x = vars->character.frames[0].img->instances[0].x;
	int my_y = vars->character.frames[0].img->instances[0].y;
	
	return (sqrt((x - my_x) * (x - my_x) + (y - my_y) * (y - my_y)));
}

void	get_v_intersect(t_vars *vars, double rotation)
{
	int my_x = vars->character.frames[0].img->instances[0].x;
	int my_y = vars->character.frames[0].img->instances[0].y;
	double x_intersect = ((my_x / 32) * 32);
	double y_intersect = 0;
	double view_field = 60 * (M_PI / 180);
	double rays = fmod((rotation - (view_field / 2)), M_PI * 2);
	if (rays < 0)
		rays += 2 * M_PI;
	if (rays < 0.5 * M_PI || rays > 1.5 * M_PI)
		x_intersect += (8);
	if (fabs(tan(rays)) < 0.000001)
		rays += 0.0001;
	y_intersect = my_y + ((x_intersect - my_x) * tan(rays));
	double next_x = 32;
	if (!(rays < (0.5 * M_PI) || rays > (1.5 * M_PI)))
		next_x *= -1;
	double next_y = (tan(rays) * 32);
	if (rays > M_PI && next_y > 0)
		next_y *= -1;
	if (rays <= M_PI && next_y < 0)
		next_y *= -1;
	double v_x = x_intersect;
	double v_y = y_intersect;
	if (!(rays < (0.5 * M_PI) || rays > (1.5 * M_PI)))
		v_x--; 
	while (v_x < vars->s_width && v_y < vars->s_height && v_x > 0 && v_y > 0)
	{
		if (is_wall(vars, v_x, v_y))
			break;
		v_y += (next_y);
		v_x += (next_x);
	}
	// printf("len -> %f\n", get_line_len(vars, vars->wall_x, vars->wall_y));
	// // if (vars->wall_x < INT_MAX)
	// // 	mlx_put_pixel(vars->win, vars->wall_x, vars->wall_y, 0x00FF00FF);
	// printf("len 2-> %f\n", get_line_len(vars, v_x, v_y));
	// printf("v_x -> %f | v_y -> %f\n", v_x, v_y);
	// printf("h_x -> %f | h_y -> %f\n", vars->wall_x, vars->wall_y);
	// if (vars->wall_x == 2147483647.000000)
	// {
	// 	if (!(rays < (0.5 * M_PI) || rays > (1.5 * M_PI)))
	// 		vars->wall_x = v_x + 1;
	// 	else
	// 		vars->wall_x = v_x;
	// 	vars->wall_y = v_y;
	// 	// return ;
	// }
	if ((get_line_len(vars, vars->wall_x, vars->wall_y) > get_line_len(vars, v_x, v_y)) && v_x < vars->s_width && v_y < vars->s_height && v_x > 0 && v_y > 0)
	{
		// printf("inside\n");
		if (!(rays < (0.5 * M_PI) || rays > (1.5 * M_PI)))
			vars->wall_x = v_x + 1;
		else
			vars->wall_x = v_x;
		vars->wall_y = v_y;
	}
	// if (v_x <= 0)
	// {
	// 	vars->wall_x = 0;
	// 	vars->wall_y = v_y;
	// }
	// else if (v_y <= 0)
	// {
	// 	vars->wall_x = v_x;
	// 	vars->wall_y = 0;
	// }
		
	
}

void	get_h_intersect(t_vars *vars, double rotation)
{
	int my_x = vars->character.frames[0].img->instances[0].x;
	int my_y = vars->character.frames[0].img->instances[0].y;
	double y_intersect = (my_y / 32) * 32;
	double x_intersect = 0;
	double view_field = 60 * (M_PI / 180);
	double rays = fmod((rotation - (view_field / 2)), M_PI * 2);
	if (rays < 0)
		rays += 2 * M_PI;
	if (rays < M_PI)
		y_intersect += 32;
	if (fabs(tan(rays)) < 0.000001)
		rays += 0.0001;
	x_intersect = my_x + ((y_intersect - my_y) / tan(rays));
	double next_y = 32;
	if (rays > M_PI) 
		next_y *= -1;
	double next_x = (32 / tan(rays));
	if ((rays < (0.5 * M_PI) || rays > (1.5 * M_PI)) && next_x < 0)
		next_x *= -1;
	else if (!(rays < (0.5 * M_PI) || rays > (1.5 * M_PI)) && next_x > 0)
		next_x *= -1;
	double h_x = x_intersect;
	double h_y = y_intersect;
	if (rays > M_PI)
		h_y--;
	while (h_x < vars->s_width && h_y < vars->s_height && h_x > 0 && h_y > 0)
	{
		if (is_wall(vars, h_x, h_y))
			break;
		h_y += (next_y);
		h_x += (next_x);
	}
	if (h_x < vars->s_width && h_y < vars->s_height && h_x > 0 && h_y > 0)
	{
		vars->wall_x = h_x;
		if (rays > M_PI)
			vars->wall_y = (h_y + 1);
		else
			vars->wall_y = h_y;
	}
	else
	{
		vars->wall_x = INT_MAX;
		vars->wall_y = INT_MAX;
	}
}
void draw_rectangle(void *mlx, int start_x, int start_y, int width, int height)
{
    int x;
	int y;

	x = start_x;
	y = start_y;
	// printf("start_x > %d | start_y > %d\n", start_x, start_y);
	// printf("width > %d | heigth > %d\n", width, height);
    while (y < start_y + height && y > 0)
    {
		x = start_x;
        while (x < start_x + width && x > 0)
        {
			// printf("x > %d | y > %d\n", x, y);
            mlx_put_pixel(mlx, x, y, 0xFFFFFFFF);
			x++;
        }
		y++;
    }
}

// void	render_walls(t_vars *vars, double angle)
// {

	
	
// }

void	key_hook(mlx_key_data_t keydata, void *vars)
{
	t_vars *my_vars = vars;
	// int rays_num = my_vars->s_width;
	// double view_field = 60 * (M_PI / 180);
	int my_x = my_vars->character.frames[0].img->instances[0].x;
	int my_y = my_vars->character.frames[0].img->instances[0].y;

	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(my_vars->mlx);
		exit(0);
	}
	my_vars->character.rotation_a += (5 * (M_PI / 180)) * my_vars->character.mv_degree;
	int x_move = ((cos(my_vars->character.rotation_a) * my_vars->character.mv_dir) + (sin(my_vars->character.rotation_a) * my_vars->character.mv_side)) * 8;
	int y_move = ((sin(my_vars->character.rotation_a) * my_vars->character.mv_dir) - (cos(my_vars->character.rotation_a) * my_vars->character.mv_side)) * 8;
	// if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	// 	my_vars->character.rotation_a += (3 * (M_PI / 180)) * my_vars->character.mv_side;
	// if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	int x_axis = (my_x + x_move);
	int y_axis = (my_y + y_move);
	// printf("my_x -> %d\n", my_x);
	// printf("my_y -> %d\n", my_y);
	// printf("x_axis -> %d\n", x_axis);
	// printf("y_axis -> %d\n", y_axis);
	if (!is_wall(my_vars, x_axis, y_axis))
	{
		// printf("degree -> %f\n", my_vars->character.rotation_a);
		// double view_field = 60 * (M_PI / 180);
		// printf("ray degree -> %f\n", my_vars->character.rotation_a);
		// double ray_step = view_field / rays_num;
		// int ray_end_x = my_x + cos(my_vars->character.rotation_a) * 60;
		// int ray_end_y = my_y + sin(my_vars->character.rotation_a) * 60;
		// printf("x -> %d\n", ray_end_x);
		// printf("y -> %d\n", ray_end_y);
		// mlx_put_pixel(my_vars->win, ray_end_x, ray_end_y, 0xFF0000FF);
		// draw_line(vars, my_x, my_y, ray_end_x, ray_end_y);
		my_vars->character.frames[0].img->instances[0].x += x_move;
		my_vars->character.frames[0].img->instances[0].y += y_move;

		// int i = 1;
		// double ray = ; 
		// double rays = fmod(my_vars->character.rotation_a - (view_field / 2), M_PI * 2);
		// // printf("rotation -> %f | vf -> %f\n", my_vars->character.rotation_a, view_field / 2);
		// if (fabs(tan(rays)) < 0.000001)
		// 	rays += 0.01;
		
		// printf("next_x %d\n", next_x);

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

void clear_image(mlx_image_t* img) {
	int x = 0;
	int y = 0;
    while (y < (int)img->height) 
	{
		x = 0;
        while (x < (int)img->width) 
		{
            mlx_put_pixel(img, x, y, 0x000000FF);
			x++;
        }
		y++;
    }
}
void	render_next_frame(void *var)
{
	t_vars *vars = var;
	int my_x = vars->character.frames[0].img->instances[0].x;
	int my_y = vars->character.frames[0].img->instances[0].y;
	double ray_step = vars->view_field / vars->s_width;
	// clear_image(vars->map_img);
	clear_image(vars->win);
	// clear_image(vars->wall_position->img);
	// clear_image(vars->floor_position->img);
	// clear_image(vars->character.frames[0].img);
	// mlx_delete_image(vars->mlx, vars->wall_position->img);
	// mlx_delete_image(vars->mlx, vars->floor_position->img);
	// mlx_delete_image(vars->mlx, vars->character.frames[0].img);
	// mlx_delete_image(vars->mlx, vars->map_img);
	// mlx_delete_image(vars->mlx, vars->win);
	// vars->win = mlx_new_image(vars->mlx, vars->s_width, vars->s_height);
	// set_imgs(vars);
	// put_image(vars->wall_count, vars, vars->wall_position->img,
	// 	vars->wall_position);
	// put_image(vars->floor_count, vars, vars->floor_position->img,
	// 	vars->floor_position);
	// vars->map_img = mlx_new_image(vars->mlx, vars->s_width * 0.25, vars->s_height * 0.25);
	// mlx_image_to_window(vars->mlx,
	// 	vars->win, 0, 0);
	// mlx_image_to_window(vars->mlx,
	// 	vars->map_img, 0, 0);
	// // set_imgs(vars);
	// mlx_image_to_window(vars->mlx,
	// vars->character.frames[0].img, my_x, my_y);
	// printf("width %d\n", vars->s_width);
	double distancePlane;
	// printf("height %d\n", vars->s_height);
	int i = 0;
	while (i < vars->s_width)
	{
		double ray_angle = vars->character.rotation_a + (ray_step * i);
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		get_h_intersect(vars, ray_angle);
		get_v_intersect(vars, ray_angle);
		if (fabs(tan(vars->view_field / 2)) < 0.000001)
			distancePlane = (vars->s_width / 2) / 0.0001;
		else
			distancePlane = (vars->s_width / 2) / tan(vars->view_field / 2);
		double distance = get_line_len(vars, vars->wall_x, vars->wall_y);
		double wall_height = (32 / distance) * distancePlane;
		// printf("vars->wall_x -> %f\n", vars->wall_x);
		// printf("vars->wall_y -> %f\n", vars->wall_y);
		// mlx_put_pixel(vars->win, vars->wall_x, vars->wall_y, 0xFF0000FF);
		draw_rectangle(vars->win, i, (((vars->s_height) / 2) - (wall_height / 2)), 1, wall_height);
		draw_line(vars, (my_x) * 0.25, (my_y) * 0.25, vars->wall_x * 0.25, vars->wall_y * 0.25, 0xFF0000FF);
		i++;
	}
}

void	set_imgs(t_vars *vars)
{
	mlx_texture_t *img = mlx_load_png("./imgs/floor.png");
	mlx_texture_t *img2 = mlx_load_png("./imgs/wall.png");
	mlx_texture_t *img3 = mlx_load_png("./imgs/ball.png");
	// img->height = 32;
	// img->width = 32;
	// img2->height = 32;
	// img2->width = 32;
	img->height *= 0.25;
	img->width *= 0.25;
	img2->height *= 0.25;
	img2->width *= 0.25;
	img3->height *= 0.25;
	img3->width *= 0.25;
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
	vars->mlx = mlx_init(j * 32, i * 32, "cub3d", false);
	if (vars->mlx == NULL)
		free_and_perror(vars, "Error\nmlx init failed");
	// vars->win = mlx_new_window(vars->mlx, j * 50, i * 50, "My Game");
	vars->s_height = i * 32;
	vars->s_width = j * 32;
	// printf("width -> %d | height -> %d\n", vars->s_width, vars->s_height);
	// if (!vars->win)
	// 	printf("Error\n");
	// if (vars->win == NULL)
	// 	free_and_perror(vars, "Error\nmlx window failed");
	mlx_key_hook(vars->mlx, key_hook, vars);
	set_imgs(vars);
	vars->character.current_frame = 0;
	put_image(vars->wall_count, vars, vars->wall_position->img,
		vars->wall_position);
	put_image(vars->floor_count, vars, vars->floor_position->img,
		vars->floor_position);
	vars->win = mlx_new_image(vars->mlx, j * 32, i * 32);
	vars->map_img = mlx_new_image(vars->mlx, j * 8, i * 8);
	mlx_image_to_window(vars->mlx,
			vars->character.frames[0].img, vars->character.x, vars->character.y);
	mlx_image_to_window(vars->mlx,
		vars->win, 0, 0);
	mlx_image_to_window(vars->mlx,
		vars->map_img, 0, 0);
	// mlx_image_to_window(vars->mlx,
	// 		vars->character.frames[0].img, 654, 248);
	// mlx_put_pixel(vars->win, 0, 0, 0xFF0000FF);
	// mlx_hook(vars->win, 17, 0, close_program, vars);
	mlx_loop_hook(vars->mlx, render_next_frame, vars);
	mlx_loop(vars->mlx);
}
