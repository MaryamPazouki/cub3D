/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:29:53 by mpazouki          #+#    #+#             */
/*   Updated: 2025/05/27 21:50:39 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

static int is_wall_row(const char *row)
{
	int i = 0;
	while (row[i])
	{
		if (row[i] != '1' && row[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}


static int is_valid_neighbor(char **map, int i, int j)
{
	// Map bounds
	if (!map[i] || !map[i][j])
		return (0);

	// Check 4 directions
	if (!map[i - 1] || !map[i + 1])
		return (0);
	if ((int)ft_strlen(map[i - 1]) <= j || (int)ft_strlen(map[i + 1]) <= j)
		return (0);

	char up = map[i - 1][j];
	char down = map[i + 1][j];
	char left = j > 0 ? map[i][j - 1] : ' ';
	char right = map[i][j + 1];

	return (up != ' ' && down != ' ' && left != ' ' && right != ' ');
}

static int ft_map_len(char **map)
{
	int len;
	
	len = 0;
	while (map[len])
		len++;
	return len;
}

int is_map_closed(char **map)
{
	int i; 
	int j;

	// Check top and bottom row
	if (!is_wall_row(map[0]) || !is_wall_row(map[ft_map_len(map) - 1]))
	{
		fprintf(stderr, "Error: Map not surrounded by walls (top/bottom).\n");
		return (0);
	}

	for (i = 1; map[i + 1]; i++) // skip first and last line
	{
		for (j = 0; map[i][j]; j++)
		{
			char c = map[i][j];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (!is_valid_neighbor(map, i, j))
				{
					fprintf(stderr, "Error: Map is not closed at (%d, %d).\n", i, j);
					return (0);
				}
			}
		}
	}
	return (1);
}
