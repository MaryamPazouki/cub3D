/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 20:43:46 by mpazouki          #+#    #+#             */
/*   Updated: 2025-06-05 20:43:46 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

char	*pad_line_with_spaces(char *line)
{
	int		len;
	int		i;
	char	*new_line;

	i = 0;
	len = ft_strlen(line);
	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			new_line[i] = '1';
		else
			new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

void	update_game_map(t_game *game, char **new_map)
{
	free(game->map);
	game->map = new_map;
}

int	copy_and_append_line(t_game *game, char **new_map, char *padded_line)
{
	int	i;

	i = 0;
	if (game->map)
	{
		while (game->map[i])
		{
			new_map[i] = game->map[i];
			i++;
		}
	}
	new_map[i] = ft_strdup(padded_line);
	if (!new_map[i])
	{
		perror("Failed to duplicate map line");
		return (0);
	}
	new_map[i + 1] = NULL;
	return (1);
}

char	**allocate_new_map(t_game *game)
{
	int		i;
	char	**new_map;

	i = 0;
	if (game->map)
		while (game->map[i])
			i++;
	new_map = (char **)ft_calloc(i + 2, sizeof(char *));
	return (new_map);
}
