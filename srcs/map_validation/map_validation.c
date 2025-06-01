/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:29:53 by mpazouki          #+#    #+#             */
/*   Updated: 2025/06/01 23:39:52 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

static int map_height(char **map)
{
	int i;
	
	if (!map)
		return(0);
	i = 0;
	while (map[i])
		i++;
	return i;
}

static int map_max_width(char **map)
{
	int max;
	int i;
	
	if (!map)
		return(0);
	max = 0;
	i = 0;
	while (map[i])
	{
		int len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return max;
}

// create padding rows
static char *create_padding_row(int width)
{
	char *padding_row;
	int i;
	
	padding_row = malloc(sizeof(char) * (width + 3));
	if (!padding_row)
		return(NULL);
	i = 0;
	while(i < width + 2)
	{
		padding_row[i] = ' ';
		i++;
	}
	padding_row[width + 2] = '\0';
	return(padding_row);		
}

// pad the lines with spaces to readjust all lines into same size
static char *pad_line_with_walls(const char *line, int target_width)
{
	int len;
	char *padded_line;
	int i;

	len = ft_strlen(line);
	padded_line = malloc(sizeof(char) * (target_width + 3));
	if (!padded_line)
		return(NULL);
	padded_line[0] = ' ';
	i = 0;
	while(i < target_width)
	{
		if (i < len)
			padded_line[i + 1] = line[i];
		else 
			padded_line[i + 1] = ' ';
		i++;
	}
	padded_line[target_width + 1] = ' ';
	padded_line[target_width + 2] = '\0';
	return padded_line;
}

// finall version of normalized map
static char **normalized_map(char **map, int height, int width)
{
	char **normalized;
	int i;

	normalized = malloc(sizeof(char *) * (height + 3) );
	if (!normalized)
		return(NULL);
	normalized[0] = create_padding_row(width);
	i = 0;
	while(i < height)
	{
		normalized[i + 1] = pad_line_with_walls(map[i], width);
		i++;
	}
	normalized[height + 1] = create_padding_row(width);
	normalized[height + 2] = NULL;
	return normalized;
}


//  functio to check the map is surrounded with 1 and all area is reachebale
static int flood_fill_safe(char **map, int x, int y, int *count)
{
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return -1; // map is not enclosed

	if (map[y][x] == '1' || map[y][x] == 'x')
		return 0; // wall or already visited

	if (map[y][x] == '0')
		(*count)++;

	map[y][x] = 'x'; // mark visited
	if (flood_fill_safe(map, x + 1, y, count) == -1) return -1;
	if (flood_fill_safe(map, x - 1, y, count) == -1) return -1;
	if (flood_fill_safe(map, x, y + 1, count) == -1) return -1;
	if (flood_fill_safe(map, x, y - 1, count) == -1) return -1;

	return 0;
}

// check if the map is closed
/* static int is_map_closed(char **map, t_game *game)
{
	int count;
	
	count = 0;
	if (flood_fill_safe(map, game->pos_x, game->pos_y , &count) == -1)
		return(0);
	return(1);
} */
static int has_open_on_border(char **map)
{
    int i, len, height;

    height = map_height(map);
    if (height == 0)
        return 1;

    // Check first and last row
    for (i = 0; map[0][i]; i++)
        if (map[0][i] == '0' || map[0][i] == 'N' || map[0][i] == 'S' || map[0][i] == 'E' || map[0][i] == 'W')
            return 1;
    for (i = 0; map[height-1][i]; i++)
        if (map[height-1][i] == '0' || map[height-1][i] == 'N' || map[height-1][i] == 'S' || map[height-1][i] == 'E' || map[height-1][i] == 'W')
            return 1;

    // Check first and last column of each row
    for (i = 0; i < height; i++) {
        len = ft_strlen(map[i]);
        if (map[i][0] == '0' || map[i][0] == 'N' || map[i][0] == 'S' || map[i][0] == 'E' || map[i][0] == 'W')
            return 1;
        if (map[i][len-1] == '0' || map[i][len-1] == 'N' || map[i][len-1] == 'S' || map[i][len-1] == 'E' || map[i][len-1] == 'W')
            return 1;
    }
    return 0;
}

// find palayer position and check the number of player exist in map
static int find_player_position(char **map, int *pos_x, int *pos_y)
{
	int y = 0;
	int x;
	int count = 0;

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
					return (0); // more than one player found
				*pos_x = x;
				*pos_y = y;
			}
			x++;
		}
		y++;
	}
	return (count == 1); // must be exactly one player
}



// main function to validate the map

int validate_map(t_game *game, char **original_map)
{
	int height;
	int width;
	char **normalized;
	int start_x, start_y;

	height = map_height(original_map);
	width = map_max_width(original_map);
	if (!find_player_position(original_map, &game->pos_x, &game->pos_y))
	{
		ft_putstr_fd("Error: Invalid or multiple player positions\n", STDERR_FILENO);
		ft_free_map(original_map);
		return (0);
	}
	
	if (has_open_on_border(original_map)) {
    ft_putstr_fd("Error: Map has open space or player on border\n", STDERR_FILENO);
    ft_free_map(original_map);
    return 0;
}
	normalized = normalized_map(original_map, height, width);
	if (!normalized)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		ft_free_map(original_map);
		return (0);
	}

	start_x = game->pos_x + 1;
	start_y = game->pos_y + 1;
	if (flood_fill_safe(normalized, start_x, start_y, &(int){0}) == -1)
	{
		ft_putstr_fd("Error: Map is not surrounded by walls\n", STDERR_FILENO);
		ft_free_map(normalized);
		ft_free_map(original_map);
		return (0);
	}

	ft_free_map(normalized);
	return (1);
}


