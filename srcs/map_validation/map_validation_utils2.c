/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 20:29:02 by mpazouki          #+#    #+#             */
/*   Updated: 2025-06-05 20:29:02 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main_header.h"

int	map_max_width(char **map)
{
	int	max;
	int	i;
	int	len;

	max = 0;
	i = 0;
	if (!map)
		return (0);
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

//--------------------pad the map with spaces----------------------------
char	*create_padding_row(int width)
{
	char	*padding_row;
	int		i;

	i = 0;
	padding_row = malloc(sizeof(char) * (width + 3));
	if (!padding_row)
		return (NULL);
	while (i < width + 2)
	{
		padding_row[i] = '6';
		i++;
	}
	padding_row[width + 2] = '\0';
	return (padding_row);
}

char	*pad_line_with_walls(const char *line, int target_width)
{
	int		len;
	char	*padded;
	int		i;

	len = ft_strlen(line);
	padded = malloc(sizeof(char) * (target_width + 3));
	if (!padded)
		return (NULL);
	padded[0] = '6';
	i = 0;
	while (i < target_width)
	{
		if (i < len)
			padded[i + 1] = line[i];
		else
			padded[i + 1] = '6';
		i++;
	}
	padded[target_width + 1] = '6';
	padded[target_width + 2] = '\0';
	return (padded);
}

char	**normalized_map(char **map, int height, int width)
{
	char	**normalized;
	int		i;

	i = 0;
	normalized = malloc(sizeof(char *) * (height + 3));
	if (!normalized)
		return (NULL);
	normalized[0] = create_padding_row(width);
	while (i < height)
	{
		normalized[i + 1] = pad_line_with_walls(map[i], width);
		i++;
	}
	normalized[height + 1] = create_padding_row(width);
	normalized[height + 2] = NULL;
	return (normalized);
}

// -----------------------zero reachable---------------
int	count_total_zeroes(char **map)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
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
	return (count);
}
