/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 09:02:37 by mpazouki          #+#    #+#             */
/*   Updated: 2025-06-05 09:02:37 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

//------------------------Extracting Map-------------------------

int	append_map_line(t_game *game, char *line)
{
	char	*padded_line;
	char	**new_map;

	padded_line = pad_line_with_spaces(line);
	if (!padded_line)
	{
		perror("Failed to pad line");
		return (0);
	}
	new_map = allocate_new_map(game);
	if (!new_map)
	{
		perror("Failed to allocate map");
		return (0);
	}
	if (!copy_and_append_line(game, new_map, padded_line))
		return (0);
	update_game_map(game, new_map);
	free(padded_line);
	return (1);
}

int	is_map_line(const char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W' || line[i] == ' '
			|| line[i] == '\t')
		{
			i++;
			continue ;
		}
		return (0);
	}
	return (1);
}
