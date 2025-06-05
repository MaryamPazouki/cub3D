/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:25:31 by mpazouki          #+#    #+#             */
/*   Updated: 2025/06/04 09:27:03 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

// extract the mapfile and check for validation---------------

static int extract_map_info(char *map_file, t_game *game)
{
	if (!parse_map_file(map_file, game))
		return 0;
	if (!validate_map(game, game->map))
		return 0;
	return 1;
}

static int	init_game_from_args(int argc, char **argv, t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	if (argc != 2)
	{
		ft_putstr_fd("\033[31mUsage: ./cub3d map_file\033[0m\n", STDERR_FILENO);
		get_next_line_cleanup();
		return (0);
	}
	if (extract_map_info(argv[1], game) == 0)
	{
		get_next_line_cleanup();
		free_game(game);
		return (0);
	}
	if (!game->map)
	{
		ft_putstr_fd("\033[31mError: Invalid map\033[0m\n", STDERR_FILENO);
		free_game(game);
		get_next_line_cleanup();
		return (0);
	}
	game->map_rows = game->map_height;
	game->map_cols = game->map_width;
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!init_game_from_args(argc, argv, &game))
		return (0);
	if (initialize_mlx_and_launch_game(&game) == -1)
	{
		ft_putstr_fd("\033[31mError: Failed to initialize graphics\033[0m\n", STDERR_FILENO);
		free_game(&game);
		get_next_line_cleanup();
		return (0);
	}
	free_game(&game);
	get_next_line_cleanup();
	return (1);
}


// int main(int argc, char **argv)
// {
// 	t_game game;

// 	ft_memset(&game, 0, sizeof(t_game));
// 	if (argc != 2)
// 	{
// 		ft_putstr_fd("Usage: ./cub3d map_file\n", STDERR_FILENO);
// 		get_next_line_cleanup();
// 		return (0);
// 	}
// 	if (extract_map_info(argv[1], &game) == 0)
// 	{
// 		get_next_line_cleanup();
// 		free_game(&game);
// 		return(0);
// 	}
// 	if (!game.map)
// 	{
// 		ft_putstr_fd("Error: Invalid map\n", STDERR_FILENO);
// 		free_game(&game);
// 		get_next_line_cleanup();
// 		return (0);
// 	}
// 	game.map_rows = game.map_height;
// 	game.map_cols = game.map_width;
// 	if (initialize_mlx_and_launch_game(&game) == -1)
// 	{
// 		ft_putstr_fd("Error: Failed to initialize graphics\n", STDERR_FILENO);
// 		free_game(&game);
// 		get_next_line_cleanup();
// 		return (0);
// 	}
// 	free_game(&game);
// 	get_next_line_cleanup();
// 	return (1);
// }

// void printGameStruct(t_game *game) {
// 	printf("n_wall_path: %s\n", game->textures_info.n_wall_path);
// 	printf("w_wall_path: %s\n", game->textures_info.w_wall_path);
// 	printf("s_wall_path: %s\n", game->textures_info.s_wall_path);
// 	printf("e_wall_path: %s\n", game->textures_info.e_wall_path);
// 	printf("floor_color: %f\n", game->textures_info.floor_color);
// 	printf("ceiling_color: %f\n", game->textures_info.ceiling_color);
// 	printf("player_count: %d\n", game->player_count);
// 	printf("map_width: %d\n", game->map_width);
// 	printf("map_height: %d\n", game->map_height);
// 	printf("pos_x: %f\n", game->pos_x);
// 	printf("pos_y: %f\n", game->pos_y);
// 	printf("dir_angle: %f\n", game->dir_angle);
// 	printf("dir_x: %f\n", game->dir_x);
// 	printf("dir_y: %f\n", game->dir_y);
// 	printf("temp_x_move: %f\n", game->temp_x_move);
// 	printf("temp_y_move: %f\n", game->temp_y_move);
// 	printf("map_rows: %d\n", game->map_rows);
// 	printf("map_cols: %d\n", game->map_cols);
// 	print_map(game->map);
// } 


// void print_game(const t_game *game)
// {
// 	int i;

// 	printf("mlx: %p\n", game->mlx);
// 	printf("win: %p\n", game->win);
// 	printf("img: %p\n", game->img);
// 	printf("img_data: %p\n", (void *)game->img_data);
// 	printf("bpp: %d\n", game->bpp);
// 	printf("size_line: %d\n", game->size_line);
// 	printf("endian: %d\n", game->endian);
// 	printf("texture_bpp: %d\n", game->texture_bpp);
// 	printf("texture_size_line: %d\n", game->texture_size_line);
// 	printf("texture_endian: %d\n", game->texture_endian);
// 	printf("x_start_minimap: %d\n", game->x_start_minimap);
// 	printf("y_start_minimap: %d\n", game->y_start_minimap);
// 	printf("side: %d\n", game->side);
// 	printf("ray_step: %f\n", game->ray_step);
// 	printf("perp_wall_dist: %f\n", game->perp_wall_dist);
// 	printf("true_ray_dist: %f\n", game->true_ray_dist);
// 	printf("projected_slice_height: %d\n", game->projected_slice_height);
// 	printf("map_rows: %d\n", game->map_rows);
// 	printf("map_cols: %d\n", game->map_cols);
// 	printf("map_width: %d\n", game->map_width);
// 	printf("map_height: %d\n", game->map_height);
// 	printf("pos_x: %f\n", game->pos_x);
// 	printf("pos_y: %f\n", game->pos_y);
// 	printf("dir_angle: %f\n", game->dir_angle);
// 	printf("dir_x: %f\n", game->dir_x);
// 	printf("dir_y: %f\n", game->dir_y);
// 	printf("temp_x_move: %f\n", game->temp_x_move);
// 	printf("temp_y_move: %f\n", game->temp_y_move);
// 	printf("key_w: %d\n", game->key_w);
// 	printf("key_a: %d\n", game->key_a);
// 	printf("key_s: %d\n", game->key_s);
// 	printf("key_d: %d\n", game->key_d);
// 	printf("key_left: %d\n", game->key_left);
// 	printf("key_right: %d\n", game->key_right);

// 	printf("map:\n");
// 	if (game->map)
// 	{
// 		for (i = 0; game->map[i]; i++)
// 			printf("%s\n", game->map[i]);
// 	}
// 	else
// 	{
// 		printf("(null)\n");
// 	}
// }