/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 23:36:48 by mpazouki          #+#    #+#             */
/*   Updated: 2025/05/28 08:19:57 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

//------------------parse and validate directive ---------------------

// check the valide keywords for directive
static int is_directive(char *line)
{	
	while (*line && ft_isspace(*line))
		line++;
	return(ft_strncmp(line, "NO", 2) == 0
		|| ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
}

// Check if all required directives (NO, SO, EA, WE, F, C) are present.
/* static int	validate_directives(t_game *game)
{
	if (!game->textures_info.n_wall_path || !game->textures_info.s_wall_path ||
		!game->textures_info.e_wall_path || !game->textures_info.w_wall_path)
		return (fprintf(stderr, "Error: Missing texture paths\n"), 0);
	if (game->textures_info.floor_color < 0 || game->textures_info.ceiling_color < 0)
		return (fprintf(stderr, "Error: Missing or invalid colors\n"), 0);
	return (1);
} */


// ---------------------validate color -------------------------------
static int	is_valid_color_range(int n)
{
	return (n >= 0 && n <= 255);
}

static int ft_validate_color(char **raw_color)
{
	int i;
	int value;

	i = 0;
	while(raw_color[i])
	{
		value = ft_atoi(raw_color[i]);
		if (!is_valid_color_range(value))
		{
			ft_free_map(raw_color);
			return(0);
		}
		i++;
	}
	return(1);
}
 
static void parse_color(const char *value, double *color_field, int *flag, const char *label)
{
	char **raw_color;

	if (!value)
	{
		fprintf(stderr, "Error: Missing value for %s color\n", label);
		return;
	}
	if ((*flag)++)
	{
		fprintf(stderr, "Error: Duplicate %s directive\n", label);
		return;
	}

	// Split color values by commas and whitespace
	raw_color = ft_split_tokens(value, ", \t");
	if (!raw_color || !raw_color[0] || !raw_color[1] || !raw_color[2] || raw_color[3])
	{
		fprintf(stderr, "Error: Invalid %s color format. Expected: R,G,B\n", label);
		ft_free_map(raw_color);
		return;
	}
	if (!ft_validate_color(raw_color))
	{
		fprintf(stderr, "Error: %s color values must be in range [0–255]\n", label);
		ft_free_map(raw_color);
		return;
	}

	// Encode RGB into single int stored as double
	*color_field = (ft_atoi(raw_color[0]) << 16)
				 | (ft_atoi(raw_color[1]) << 8)
				 | ft_atoi(raw_color[2]);
	ft_free_map(raw_color);
}


// valide texture and pathfile
static int	is_valid_texture_path(const char *path)
{
	int		fd;

	if (!path)
		return (0);

	// Check file extension (.xpm required by MiniLibX)
	int len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		fprintf(stderr, "Error: Invalid texture extension for '%s'. Must be .xpm\n", path);
		return (0);
	}

	// Try to open the file to check existence and readability
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror(path);
		return (0);
	}
	close(fd);
	return (1);
}

static int set_texture_path(char **dest, int *flag, const char *path, const char *label)
{
	if((*flag)++)
	{
		fprintf(stderr, "Error: Duplicate %s directive\n", label);
		return (0);
	}
	if (!is_valid_texture_path(path))
	{
		fprintf(stderr, "Error: Invalid texture path for %s: %s\n", label , path);
		return (0);
	}
	*dest = ft_strdup(path);
	if (!*dest)
	{
		fprintf(stderr, "Error: Failed to allocate memory for %s path\n", label);
		return (0);
	}
	return (1);
}


//handel texture and validate
static int handel_texture_directive(t_game *game, const char *key, const char *path)
{
	
	if (!ft_strcmp(key, "NO"))
		return set_texture_path(&game->textures_info.n_wall_path, &game->textures_info.has_no, path, "NO");
	else if (!ft_strcmp(key, "SO"))
		return set_texture_path(&game->textures_info.s_wall_path, &game->textures_info.has_so, path, "SO");
	else if (!ft_strcmp(key, "WE"))
		return set_texture_path(&game->textures_info.w_wall_path, &game->textures_info.has_we, path, "WE");
	else if (!ft_strcmp(key, "EA"))
		return set_texture_path(&game->textures_info.e_wall_path, &game->textures_info.has_ea, path, "EA");
	fprintf(stderr, "Error: Unknown texture key: %s\n", key);
	return (0);
}

static int handel_color_directive(t_game *game, const char *key, const char *value)
{
	if (!ft_strcmp(key, "F"))
	{
		parse_color(value, &game->textures_info.floor_color, &game->textures_info.has_f, "F");
		return 1;
	}
	if (!ft_strcmp(key, "C"))
	{
		parse_color(value, &game->textures_info.ceiling_color, &game->textures_info.has_c, "C");
		return 1;
	}
	fprintf(stderr, "Error: Unknown color key: %s\n", key);
	return 0;
}


//parse texture and colors
void parse_directive(t_game *game, char *line)
{
	char **tokens;

	tokens = ft_split_tokens(line, " \t");
	if (!tokens || !tokens[0] || !tokens[1])
	{
		fprintf(stderr, "Error: Invalid directive format\n");
		ft_free_map(tokens);
		return;
	}
	if (!ft_strcmp(tokens[0], "NO") || !ft_strcmp(tokens[0], "SO") || 
		!ft_strcmp(tokens[0], "WE") || !ft_strcmp(tokens[0], "EA"))
	{
		if (handel_texture_directive(game, tokens[0], tokens[1]))
		{;}
	}
	else if (!ft_strcmp(tokens[0], "F") || !ft_strcmp(tokens[0], "C"))
	{	
		if (handel_color_directive(game, tokens[0], tokens[1]))
		{;}
	}
	/* else
		fprintf(stderr, "Error: Unknown directive: %s\n", tokens[0]); */
	ft_free_map(tokens);
}


//------------------------Extracting Map-------------------------

static int has_valid_characters(const char *line)
{
    int i;
    
    i = 0;
    while(line[i])
    {
        if (line[i] != ' ' && line[i] != '0' && line[i] != '1' &&
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
    }
    return (1);
}



// check map extension
int has_cub_extension(const char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (len < 4)
		return(0);
	return(ft_strncmp(filename + (len - 4 ), ".cub", 4) == 0);	
}

static void count_player_in_line(t_game *game, const char *line)
{
	while (*line)
	{
		if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			game->player_count++;
		line++;
	}
}


// -------------------------append lines in MAP-----------------------
void	append_map_line(t_game *game, char *line)
{
	char	**new_map;
	int		i;
	
	count_player_in_line(game, line);
	// Count existing map lines
	i = 0;
	if (game->map)
		while (game->map[i])
			i++;

	// Allocate new map with one extra slot
	new_map = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!new_map)
	{
		perror("Failed to allocate map");
		ft_free_map(game->map);
		exit(EXIT_FAILURE);
	}

	// Copy old map lines into new map
	for (int j = 0; j < i; j++)
		new_map[j] = game->map[j];

	// Duplicate the new line and assign it
	new_map[i] = ft_strdup(line);
	if (!new_map[i])
	{
		perror("Failed to duplicate map line");
		ft_free_map(new_map);
		exit(EXIT_FAILURE);
	}

	// Free old map array (but not the strings, since they are reused)
	free(game->map);

	// Assign the new map to game
	game->map = new_map;
}




static int read_map_file(t_game *game, int fd)
{
	char *line;
	int map_start;
	int count;

	map_start = 0;
	count = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		char *trimmed_line = ft_strtrim(line, " \t\n");
		if (!trimmed_line)
			return (-1);
		if (!map_start && is_directive(trimmed_line))
		{
			parse_directive(game, trimmed_line);
		    count++;
		}
		else if (count == 6 && is_map_line(line))
		{
			map_start = 1;
			if (game->player_count != 1)
			{
				fprintf(stderr, "Error: Map must contain exactly one player start position\n");
				return (-1);
			}
			append_map_line(game, line);
		}
        else if (!map_start)
        {
	        fprintf(stderr, "Error: Invalid directive or garbage line: %s\n", line);
	        free(trimmed_line);
	        close(fd);
	        return (-1);
        }
		free(trimmed_line);
		free(line);
	}
	return (0);
}




// ---------------------PARSE MAP-------------------------------------
// main function to parse the map
int parse_map_file(const char *filepath, t_game *game)
{
	int fd;
		
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return(perror("Failed to open map") , -1);
	if (!has_cub_extension(filepath))
	{
		fprintf(stderr, "Error: Map file must have a .cub extension\n");
		return (1);
	}
	read_map_file(game, fd);
	close(fd);
	if (!game->map || !game->map[0])
	{
		fprintf(stderr, "Error: Empty map\n");
		return (1);
	}
	return(0);
}

// extract the mapfile and check for validation---------------

int extract_map_info(char *map_file, t_game *game)
{
    parse_map_file(map_file, game);
    if (!game->map)
        return -1;
    /* if (!is_map_rectangular(game->map))
        return -1; */
    if (!has_valid_characters(game->map))
        return -1;
	if (!validate_map_closed(game, map_height))
	{
		ft_putstr_fd("Error: Map is not closed by walls\n", STDERR_FILENO);
		return (-1);
	}
	if (!validate_all_zeros_reachable(game, map_height))
	{
		ft_putstr_fd("Error: Not all 0s are reachable from player\n", STDERR_FILENO);
		return (-1);
	}	
    if (!set_player_position(game))
        return -1;
    set_map_dimensions(game);
    return 0;
}