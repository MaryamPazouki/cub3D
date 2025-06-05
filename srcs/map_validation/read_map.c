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

// static int count_player_in_line(t_game *game, const char *line)
// {
// 	while (*line)
// 	{
// 		if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
// 		{
// 			game->player_count++;
// 			if (game->player_count > 1)
// 			{
// 				fprintf(stderr, "\033[31mError: Multiple player positions found\033[0m\n");
// 				return(0);
// 			}
// 		}
// 		line++;
// 	}
// 	return(1);
// }

static char *pad_line_with_spaces(char *line)
{
	int len;
	int i;
	char *new_line;

	i = 0;
	len = ft_strlen(line);
	new_line = malloc(sizeof (char) *(len + 1));
	if (!new_line)
		return (NULL);
	while(line[i])
	{	
		if (line[i]== ' ' || line[i] == '\t')
			new_line[i] = '1';
		else
			new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	return(new_line);
}

void	update_game_map(t_game *game, char **new_map)
{
	free(game->map);
	game->map = new_map;
}


int	copy_and_append_line(t_game *game, char **new_map, char *padded_line)
{
	int	i = 0;

	if (game->map)
		while (game->map[i])
		{
			new_map[i] = game->map[i];
			i++;
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
	int		i = 0;
	char	**new_map;

	if (game->map)
		while (game->map[i])
			i++;

	new_map = (char **)ft_calloc(i + 2, sizeof(char *));
	return (new_map);
}


int	append_map_line(t_game *game, char *line)
{
	char	*padded_line;
	char	**new_map;

	// if (!count_player_in_line(game, line))
	// 	return(0);
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

int is_map_line(const char *line)
{
	int i;

	if (!line)
		return 0;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' ||
			line[i] == 'N' || line[i] == 'S' ||
			line[i] == 'E' || line[i] == 'W' ||
			line[i] == ' ' || line[i] == '\t')
		{
			i++;
			continue;
		}
		return 0;
	}
	return 1;
}


// // -------------------------append lines in MAP-----------------------
// int	append_map_line(t_game *game, char *line)
// {
// 	char	**new_map;
// 	int		i;
// 	char *padded_line;

// 	count_player_in_line(game, line);
// 	i = 0;
// 	if (game->map)
// 		while (game->map[i])
// 			i++;

// 	padded_line = pad_line_with_spaces(line);
// 	if (!padded_line)
// 	{
// 		perror("Failed to pad line");
// 		return(0);
// 	}
// 	new_map = (char **)ft_calloc(i + 2, sizeof(char *));
// 	if (!new_map)
// 	{
// 		perror("Failed to allocate map");
// 		return(0);;
// 	}
// 	for (int j = 0; j < i; j++)
// 		new_map[j] = game->map[j];
// 	new_map[i] = ft_strdup(padded_line);
// 	if (!new_map[i])
// 	{
// 		perror("Failed to duplicate map line");
// 		return(0);
// 	}
// 	new_map[i + 1] = NULL;
// 	free(padded_line);
// 	free(game->map);
// 	game->map = new_map;
// 	return (1);
// }