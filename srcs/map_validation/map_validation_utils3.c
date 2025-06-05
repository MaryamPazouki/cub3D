/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 20:31:04 by mpazouki          #+#    #+#             */
/*   Updated: 2025-06-05 20:31:04 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

int	map_height(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
		i++;
	return (i);
}

static int	flood_fill_safe(char **map, int x, int y, int *visited_count)
{
	if (map[y][x] == '6' || map[y][x] == '\0')
		return (-1);
	if (map[y][x] == '1' || map[y][x] == 'x')
		return (0);
	if (map[y][x] == '0')
		(*visited_count)++;
	map[y][x] = 'x';
	if (flood_fill_safe(map, x + 1, y, visited_count) == -1)
		return (-1);
	if (flood_fill_safe(map, x - 1, y, visited_count) == -1)
		return (-1);
	if (flood_fill_safe(map, x, y + 1, visited_count) == -1)
		return (-1);
	if (flood_fill_safe(map, x, y - 1, visited_count) == -1)
		return (-1);
	return (0);
}

int	validate_map_enclosure_and_reachability(char **normalized_map, int start_x,
		int start_y)
{
	int	total_zeroes;
	int	visited_zeroes;

	total_zeroes = count_total_zeroes(normalized_map);
	visited_zeroes = 0;
	if (flood_fill_safe(normalized_map, start_x, start_y, &visited_zeroes) == -1)
	{
		printf("\033[31mError: Map is not enclosed!\033[0m\n");
		return (0);
	}
	if (visited_zeroes < total_zeroes)
	{
		printf("\033[31mError: Not all walkable areas are reachable!\033[0m\n");
		return (0);
	}
	return (1);
}
