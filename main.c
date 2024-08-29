#include "header.h"

int	main(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	// if (argc != 2)
	// {
	// 	// return (1);
	// }
	// mlx_t* mlx;
	t_vars vars;

	if (!count_elements(&vars, argv[1]))
		return (2);
	allocate_memory(&vars);
	process_lines(&vars, argv[1]);
	// printf("floor count -> %d\n", vars.floor_count);


	// mlx = mlx_init(600, 600, "MLX42", true);

	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	return (0);
}