/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:29:53 by mpazouki          #+#    #+#             */
/*   Updated: 2025/06/03 11:00:21 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

static int ft_strlen_with_space(const char *map)
{
    int i = 0;
    while (map[i])
        i++;
    return i;
}

static int map_height(char **map)
{
	int i = 0;
	if (!map)
		return 0;
	while (map[i])
		i++;
	return i;
}

static int map_max_width(char **map)
{
	int max = 0;
	int i = 0;
	if (!map)
		return 0;
	while (map[i])
	{
		int len = ft_strlen_with_space(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return max;
}
//--------------------pad the map with spaces----------------------------
static char *create_padding_row(int width)
{
	char *padding_row = malloc(sizeof(char) * (width + 3));
	if (!padding_row)
		return NULL;
	for (int i = 0; i < width + 2; i++)
		padding_row[i] = '6';
	padding_row[width + 2] = '\0';
	return padding_row;
}

char *pad_line_with_walls(const char *line, int target_width)
{
	int len = ft_strlen(line);
	char *padded = malloc(sizeof(char) * (target_width + 3)); // +2 for borders, +1 for '\0'
	if (!padded)
		return NULL;

	padded[0] = '6';

	// Copy characters from line
	int i = 0;
	while (i < target_width)
	{
		if (i < len)
			padded[i + 1] = line[i];
		else
			padded[i + 1] = '6'; // pad with '6' if line is shorter
		i++;
	}

	padded[target_width + 1] = '6';
	padded[target_width + 2] = '\0';

	//printf("Padded: %s\n", padded); // Debug output
	return padded;
}



static char **normalized_map(char **map, int height, int width)
{
	char **normalized;
	int	i;
	
	i = 0;
	normalized = malloc(sizeof(char *) * (height + 3));
	if (!normalized)
		return NULL;

	normalized[0] = create_padding_row(width);
	while(i < height)
	{	
		normalized[i + 1] = pad_line_with_walls(map[i], width);
		i++;
	}
	normalized[height + 1] = create_padding_row(width);
	normalized[height + 2] = NULL;
	return normalized;
}


// -----------------------zero reachable---------------
static int count_total_zeroes(char **map)
{
	int y = 0, x, count = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
				count++;
			x++;
		}
		y++;
	}
	return count;
}

static int flood_fill_safe(char **map, int x, int y, int *visited_count)
{
	if (map[y][x] == '6' || map[y][x] == '\0')
		return -1;
	if (map[y][x] == '1' || map[y][x] == 'x')
		return 0;
	if (map[y][x] == '0')
		(*visited_count)++;

	map[y][x] = 'x';
	if (flood_fill_safe(map, x + 1, y, visited_count) == -1) return -1;
	if (flood_fill_safe(map, x - 1, y, visited_count) == -1) return -1;
	if (flood_fill_safe(map, x, y + 1, visited_count) == -1) return -1;
	if (flood_fill_safe(map, x, y - 1, visited_count) == -1) return -1;

	return 0;
}

static int validate_map_enclosure_and_reachability(char **normalized_map, int start_x, int start_y)
{
	int total_zeroes = count_total_zeroes(normalized_map);
	int visited_zeroes = 0;
	if (flood_fill_safe(normalized_map, start_x, start_y, &visited_zeroes) == -1)
	{
		ft_putstr_fd("Error: Map is not enclosed\n", STDERR_FILENO);
		return (0);
	}
	if (visited_zeroes < total_zeroes)
	{
		ft_putstr_fd("Error: Not all walkable areas are reachable\n", STDERR_FILENO);
		return (0);
        //exit(1);
	}
	return (1);
}

static int find_player_position(char **map, int *pos_x, int *pos_y)
{
	int y = 0;
	int x, count = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' ||
				map[y][x] == 'E' || map[y][x] == 'W')
			{
				count++;
				if (count > 1)
					return 0;
				*pos_x = x;
				*pos_y = y;
			}
			x++;
		}
		y++;
	}
	return (count == 1);
}

static void sanitize_map(t_game *game, char **map)
{
	int y = 0;
	while (map[y])
	{
		int x = 0;
		while (map[y][x])
		{
			if ((y == 0 || y == game->map_height - 1) &&
				(map[y][x] == ' ' || map[y][x] == '\t'))
			{
				map[y][x] = '6'; // For top or bottom rows, treat space/tab as padding
			}
			x++;
		}
		y++;
	}
}

int validate_map(t_game *game, char **original_map)
{
	printf("Validating map...\n");
	char **normalized;
    game->map_height = map_height(original_map);
	game->map_width = map_max_width(original_map);
    if (game->map_height > 15 || game->map_width > 35)
    {
        ft_putstr_fd("Error: Map is so big\n", STDERR_FILENO);
        ft_free_map(original_map);
		exit(1);
    }
    if (!find_player_position(original_map, &game->pos_x, &game->pos_y))
	{
		ft_putstr_fd("Error: Invalid or multiple player positions\n", STDERR_FILENO);
		ft_free_map(original_map);
		exit(1);
	}
	sanitize_map(game, original_map);
	normalized = normalized_map(original_map, game->map_height, game->map_width);
	// for (int i = 0; original_map[i]; i++)
    // 	printf("%s\n", original_map[i]); 
	if (!normalized)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		ft_free_map(original_map);
		exit(1);
	}

     // Adjusted due to padding
	if (!validate_map_enclosure_and_reachability(normalized, game->pos_x + 1, game->pos_y + 1))
    {
        ft_free_map(normalized);
        ft_free_map(original_map);
        exit(1);
    }
	printf("Validating map structure...\n");
	ft_free_map(normalized);
	return 1;
}
