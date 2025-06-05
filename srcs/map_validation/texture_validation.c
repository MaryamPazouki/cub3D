/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 09:00:39 by mpazouki          #+#    #+#             */
/*   Updated: 2025-06-05 09:00:39 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main_header.h"

// valide texture and pathfile
static int	is_valid_texture_path(t_game *game, const char *path)
{
	int		fd;

	if (!path)
		return (0);

	// Check file extension (.xpm required by MiniLibX)
	int len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		fprintf(stderr, "\033[31mError: Invalid texture extension for '%s'. Must be .xpm\033[0m\n", path);
		free_game(game); // Free any previously allocated memory
		return(0);
	}
	// Try to open the file to check existence and readability
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "\033[31mError: Invalid texture path for '%s'\033[0m\n", path);
		free_game(game); // Free any previously allocated memory
		return(0);
	}
	close(fd);
	return (1);
}

static int set_texture_path(t_game *game, char **dest, int *flag, const char *path, const char *label)
{
	if(++(*flag)>1)
	{
		fprintf(stderr, "\033[31mError: Duplicate %s directive\033[0m\n", label);
		return(0);
	}
	if (!is_valid_texture_path(game, path))
	{
		return(0);
	}
	if (!dest)
	{
		fprintf(stderr, "\033[31mError: Null pointer for %s path\033[0m\n", label);
		return(0);
	}
	*dest = ft_strdup(path);
	if (!*dest)
	{
		fprintf(stderr, "\033[31mError: Failed to allocate memory for %s path\033[0m\n", label);
		return(0);
	}
	return (1);
}

//handle texture and validate
int handle_texture_directive(t_game *game, const char *key, const char *path)
{
	
	if (!ft_strcmp(key, "NO"))
		return set_texture_path(game, &game->textures_info.n_wall_path, &game->textures_info.has_no, path, "NO");
	else if (!ft_strcmp(key, "SO"))
		return set_texture_path(game,&game->textures_info.s_wall_path, &game->textures_info.has_so, path, "SO");
	else if (!ft_strcmp(key, "WE"))
		return set_texture_path(game,&game->textures_info.w_wall_path, &game->textures_info.has_we, path, "WE");
	else if (!ft_strcmp(key, "EA"))
		return set_texture_path(game, &game->textures_info.e_wall_path, &game->textures_info.has_ea, path, "EA");
	fprintf(stderr, "Error: Unknown texture key: %s\n", key);
	return (0);
}