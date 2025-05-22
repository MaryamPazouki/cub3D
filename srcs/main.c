#include "main_header.h"

int main(int argc, char **argv)
{
	t_game game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3d map_file\n", STDERR_FILENO);
		return (1);
	}
	if (extract_map_info(argv[1], &game) == -1)
	{
		ft_putstr_fd("Error: Invalid map\n", STDERR_FILENO);
		return (1);
	}
	if (!game.map)
	{
		ft_putstr_fd("Error: Invalid map\n", STDERR_FILENO);
		return (1);
	}
	print_map(game.map);
	if (initialize_mlx_and_launch_game(&game) == -1)
	{
		ft_putstr_fd("Error: Failed to initialize graphics\n", STDERR_FILENO);
		free_map(game.map);
		return (1);
	}
	return (0);
}

// make a 2D window with walls and player looking at a direction
// define the size of each square in the map and change color of the square based on type
