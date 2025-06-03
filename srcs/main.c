/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:25:31 by mpazouki          #+#    #+#             */
/*   Updated: 2025/06/03 11:26:33 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

static void printGameStruct(t_game *game) {
	printf("n_wall_path: %s\n", game->textures_info.n_wall_path);
	printf("w_wall_path: %s\n", game->textures_info.w_wall_path);
	printf("s_wall_path: %s\n", game->textures_info.s_wall_path);
	printf("e_wall_path: %s\n", game->textures_info.e_wall_path);
	printf("floor_color: %f\n", game->textures_info.floor_color);
	printf("ceiling_color: %f\n", game->textures_info.ceiling_color);
	printf("player_count: %d\n", game->player_count);
	printf("map_width: %d\n", game->map_width);
	printf("map_height: %d\n", game->map_height);
	printf("pos_x: %f\n", game->pos_x);
	printf("pos_y: %f\n", game->pos_y);
	printf("dir_angle: %f\n", game->dir_angle);
	printf("dir_x: %f\n", game->dir_x);
	printf("dir_y: %f\n", game->dir_y);
	printf("temp_x_move: %f\n", game->temp_x_move);
	printf("temp_y_move: %f\n", game->temp_y_move);
	printf("map_rows: %d\n", game->map_rows);
	printf("map_cols: %d\n", game->map_cols);
	print_map(game->map);
}


//here is the last version 
int main(int argc, char **argv)
{
	t_game game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3d map_file\n", STDERR_FILENO);
		return (1);
	}
	if (extract_map_info(argv[1], &game) == 0)
	{
		ft_putstr_fd("Error: Invalid map\n", STDERR_FILENO);
		return (1);
	}
	if (!game.map)
	{
		ft_putstr_fd("Error: Invalid map\n", STDERR_FILENO);
		return (1);
	}
	//print_map(game.map);
	printGameStruct(&game);
	if (initialize_mlx_and_launch_game(&game) == -1)
	{
		ft_putstr_fd("Error: Failed to initialize graphics\n", STDERR_FILENO);
		ft_free_map(game.map);
		return (1);
	}
	free_textures_info(&game.textures_info);
	ft_free_map(game.map);
	return (0);
}

// make a 2D window with walls and player looking at a direction
// define the size of each square in the map and change color of the square based on type
