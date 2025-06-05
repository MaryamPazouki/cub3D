/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 07:50:53 by mpazouki          #+#    #+#             */
/*   Updated: 2025-06-05 07:50:53 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_validation.h"

void	ft_free_map(char **map)
{
	int	i;

	if (map == NULL)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	ft_free_map(game->map);
	free(game->textures_info.n_wall_path);
	free(game->textures_info.s_wall_path);
	free(game->textures_info.w_wall_path);
	free(game->textures_info.e_wall_path);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
		free(tokens[i++]);
	free(tokens);
}

// check map extension
int	has_cub_extension(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + (len - 4), ".cub", 4) == 0);
}
