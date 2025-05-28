/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:29:53 by mpazouki          #+#    #+#             */
/*   Updated: 2025/05/28 12:14:06 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

// find_max_row
int find_max_row_len(char **map)
{
	int max;
	int len;
	int i;

	i = 0;
	max = 0;
	while(map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	int emptyCounter = 0;
	return(max);
	
}

// create padding rows
char *create_padding_row(int width)
{
	char *padding_row;
	int i;

	padding_row = (char *)malloc(sizeof(char) * (width + 1));
	if (!padding_row)
		return NULL;

	i = 0;
	while (i < width)
	{
		padding_row[i] = ' ';
		i++;
	}
	padding_row[width] = '\0';
	return padding_row;
}

// pad_line -Pad each line to same length with spaces

char *pad_line(char *line, int width)
{
	int len;
	char *padded;
	int i;

	len = ft_strlen(line);
	padded = malloc(sizeof (char *) * (width + 3));
	if (!padded)
		return(NULL);
	
	i = 0;
	while(i < width)
	{
		if (i < len)
			padded[i + 1] = line[i];
		else
			padded [i] = ' ';
		i++;
	}
	
	padded[0] = ' '; // left wall
	padded[i + 1] = ' '; // right wall
	padded[i + 2] = '\0';
	return (padded);
}






int flood_fill_safe(char **map, int x, int y, int *count)
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
