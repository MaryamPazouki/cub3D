/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:29:53 by mpazouki          #+#    #+#             */
/*   Updated: 2025/06/03 21:19:30 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

static void	sanitize_map(t_game *game, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((y == 0 || y == game->map_height - 1) && (map[y][x] == ' '
				|| map[y][x] == '\t'))
			{
				map[y][x] = '6';
			}
			x++;
		}
		y++;
	}
}

static int	is_player_tile(t_game *game, char c, int x, int y, double *pos_x,
		double *pos_y)
{
	if (c == 'N')
		game->dir_angle = 3 * M_PI / 2;
	else if (c == 'S')
		game->dir_angle = M_PI / 2;
	else if (c == 'E')
		game->dir_angle = 0;
	else if (c == 'W')
		game->dir_angle = M_PI;
	else
		return (0);
	*pos_x = x + 0.5;
	*pos_y = y + 0.5;
	game->dir_x = cos(game->dir_angle);
	game->dir_y = sin(game->dir_angle);
	return (1);
}

static int	find_player_position(t_game *game, char **map, double *pos_x,
		double *pos_y)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player_tile(game, map[y][x], x, y, pos_x, pos_y))
			{
				count++;
				if (count > 1)
					return (0);
				map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (count == 1);
}

static int	check_map_size_and_player(t_game *game, char **original_map)
{
	game->map_height = map_height(original_map);
	game->map_width = map_max_width(original_map);
	if (game->map_height > 50 || game->map_width > 55)
	{
		ft_putstr_fd("\033[31mError: Map size is out of bound\033[0m\n",
			STDERR_FILENO);
		return (0);
	}
	if (!find_player_position(game, original_map, &game->pos_x, &game->pos_y))
	{
		ft_putstr_fd("\033[31mError: Invalid player position!\033[0m\n",
			STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game, char **original_map)
{
	char	**normalized;

	if (!check_map_size_and_player(game, original_map))
		return (0);
	sanitize_map(game, original_map);
	normalized = normalized_map(original_map, game->map_height,
			game->map_width);
	if (!normalized)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		return (0);
	}
	if (!validate_map_enclosure_and_reachability(normalized, game->pos_x + 1,
			game->pos_y + 1))
	{
		ft_free_map(normalized);
		return (0);
	}
	ft_free_map(normalized);
	return (1);
}

// static int find_player_position(t_game *game, char **map, double *pos_x,
//	double *pos_y)
// {
// 	int y = 0;
// 	int x;
// 	int count = 0;

// 	while (map[y])
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			if (map[y][x] == 'N' || map[y][x] == 'S' ||
// 				map[y][x] == 'E' || map[y][x] == 'W')
// 			{
// 				count++;
// 				if (count > 1)
// 					return (0);
// 				if (map[y][x] == 'N')
// 					game->dir_angle = 3 * M_PI / 2;
// 				else if (map[y][x] == 'S')
// 					game->dir_angle = M_PI / 2;
// 				else if (map[y][x] == 'E')
// 					game->dir_angle = 0;
// 				else if (map[y][x] == 'W')
// 					game->dir_angle = M_PI;
// 				*pos_x = x + 0.5;
// 				*pos_y = y + 0.5;
// 				map[y][x] = '0';
// 				game->dir_x = cos(game->dir_angle);
// 				game->dir_y = sin(game->dir_angle);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (count == 1);
// }

// int validate_map(t_game *game, char **original_map)
// {
// 	char **normalized;

// 	game->map_height = map_height(original_map);
// 	game->map_width = map_max_width(original_map);
// 	if (game->map_height > 50 || game->map_width > 55)
// 	{
// 		ft_putstr_fd("\033[31mError: Map size is out of bound\033[0m\n",
//			STDERR_FILENO);
// 		return(0);
// 	}
// 	if (!find_player_position(game ,original_map, &game->pos_x, &game->pos_y))
// 	{
// 		ft_putstr_fd("\033[31mError: Invalid player position!\033[0m\n",
//			STDERR_FILENO);
// 		return(0);
// 	}
// 	sanitize_map(game, original_map);
// 	normalized = normalized_map(original_map, game->map_height,
//			game->map_width);
// 	if (!normalized)
// 	{
// 		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
// 		return(0);
// 	}
// 	if (!validate_map_enclosure_and_reachability(normalized, game->pos_x + 1,
//			game->pos_y + 1))
// 	{
// 			ft_free_map(normalized);
// 		return(0);
// 	}
// 	ft_free_map(normalized);
// 	return (1);
// }
