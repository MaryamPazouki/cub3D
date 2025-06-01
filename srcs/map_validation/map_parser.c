/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 23:36:48 by mpazouki          #+#    #+#             */
/*   Updated: 2025/06/01 22:43:34 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"
//------------------parse and validate directive ---------------------

// check the valide keywords for directive
static int is_directive(char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (!line[0] || !line[1] || !line[2])
		return (0);
	return((ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2]))
		|| (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2]))
		|| (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2]))
		|| (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2]))
		|| (line[0] == 'F' && ft_isspace(line[1]))
		|| (line[0] == 'C' && ft_isspace(line[1]))
	);
}

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

// parse_color() return 1 (success) or 0 (error):
static int parse_color(const char *value, double *color_field, int *flag, const char *label)
{
	char **raw_color;

	if (!value)
	{
		fprintf(stderr, "Error: Missing value for %s color\n", label);
		return (0);
	}
	if ((*flag)++)
	{
		fprintf(stderr, "Error: Duplicate %s directive\n", label);
		return (0);
	}
	raw_color = ft_split_tokens(value, ", \t");
	if (!raw_color || !raw_color[0] || !raw_color[1] || !raw_color[2] || raw_color[3])
	{
		fprintf(stderr, "Error: Invalid %s color format. Expected: R,G,B\n", label);
		ft_free_map(raw_color);
		return (0);
	}
	if (!ft_validate_color(raw_color))
	{
		fprintf(stderr, "Error: %s color values must be in range [0–255]\n", label);
		return (0);
	}
	*color_field = encode_rgb(
					ft_atoi(raw_color[0]),
					ft_atoi(raw_color[1]),
					ft_atoi(raw_color[2]));
	ft_free_map(raw_color);
	return (1);
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
		fprintf(stderr, "\033[31mError: Invalid texture extension for '%s'. Must be .xpm\033[0m\n", path);
		return (0);
	}

	// Try to open the file to check existence and readability
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "\033[31mError: Invalid texture path for '%s'\033[0m\n", path);
		return(0);
	}
	close(fd);
	return (1);
}

static int set_texture_path(char **dest, int *flag, const char *path, const char *label)
{
	if((*flag)++)
	{
		fprintf(stderr, "\033[31mError: Duplicate %s directive\033[0m\n", label);
		return (1);
	}
	if (!is_valid_texture_path(path))
		return (1);
	if (*dest)
		free(*dest);
	*dest = ft_strdup(path);
	if (!*dest)
	{
		fprintf(stderr, "\033[31mError: Failed to allocate memory for %s path\033[0m\n", label);
		exit (1);
	}
	return (0);
}

static int check_all_directives_present(t_textures_info *t)
{
	if (!t->has_no || !t->has_so || !t->has_we || !t->has_ea ||
		!t->has_f || !t->has_c)
	{
		if (!t->has_no) fprintf(stderr, "Missing NO directive\n");
		if (!t->has_so) fprintf(stderr, "Missing SO directive\n");
		if (!t->has_we) fprintf(stderr, "Missing WE directive\n");
		if (!t->has_ea) fprintf(stderr, "Missing EA directive\n");
		if (!t->has_f) fprintf(stderr, "Missing F directive\n");
		if (!t->has_c) fprintf(stderr, "Missing C directive\n");
		return (0);
	}
	return (1);
}

//handle texture and validate
static int handle_texture_directive(t_game *game, const char *key, const char *path)
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
	return (1);
}

static int handle_color_directive(t_game *game, const char *key, const char *value)
{
	if (!ft_strcmp(key, "F"))
	{
		return parse_color(value,
				&game->textures_info.floor_color, &game->textures_info.has_f, "F");
	}
	if (!ft_strcmp(key, "C"))
	{
		return parse_color(value,
				&game->textures_info.ceiling_color, &game->textures_info.has_c, "C");
	}
	fprintf(stderr, "Error: Unknown color key: %s\n", key);
	return (0);
}


//parse texture and colors
int parse_directive(t_game *game, char *line)
{
	char **tokens;

	tokens = ft_split_tokens(line, " \t");
	if (!tokens || !tokens[0] || !tokens[1])
	{
		fprintf(stderr, "Error: Invalid directive format\n");
		ft_free_map(tokens);
		return (0);
	}
	if (!ft_strcmp(tokens[0], "NO") || !ft_strcmp(tokens[0], "SO") ||
		!ft_strcmp(tokens[0], "WE") || !ft_strcmp(tokens[0], "EA"))
	{
		if (handle_texture_directive(game, tokens[0], tokens[1]))
		{
			ft_free_map(tokens);
			return (0);
		}
	}
	else if (!ft_strcmp(tokens[0], "F") || !ft_strcmp(tokens[0], "C"))
	{
		if (handle_color_directive(game, tokens[0], tokens[1]))
		{
			ft_free_map(tokens);
			return (0);
		}
	}
	else
	{
		fprintf(stderr, "Error: Unknown directive: %s\n", tokens[0]);
		ft_free_map(tokens);
		return (0);
	}
	ft_free_map(tokens);
	return (1);
}


//------------------------Extracting Map-------------------------

// check map extension
static int has_cub_extension(const char *filename)
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
		{
			game->player_count++;
			/* if (game->player_count > 1)
			{
				fprintf(stderr, "\033[31mError: Multiple player positions found\033[0m\n");
				exit(1);
			} */
		}
		line++;
	}
}


// -------------------------append lines in MAP-----------------------
static void	append_map_line(t_game *game, char *line)
{
	char	**new_map;
	int		i;

	count_player_in_line(game, line);
	i = 0;
	if (game->map)
		while (game->map[i])
			i++;
	new_map = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!new_map)
	{
		perror("Failed to allocate map");
		ft_free_map(game->map);
		exit(EXIT_FAILURE);
	}
	for (int j = 0; j < i; j++)
		new_map[j] = game->map[j];
	new_map[i] = ft_strdup(line);
	if (!new_map[i])
	{
		perror("Failed to duplicate map line");
		ft_free_map(new_map);
		exit(EXIT_FAILURE);
	}
	free(game->map);
	game->map = new_map;
}

static int is_map_line(const char *line)
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


static int	handle_directive_line(t_game *game, char *line, int *directive_count)
 {
	if (!is_directive(line))
		return (0);
	parse_directive(game, line);
	(*directive_count)++;
	return (1);
}

static int	handle_map_line(t_game *game, char *line)
{
	if (!is_map_line(line))
		return (0);
	append_map_line(game, line);
	return (1);
}


static int	read_map_file(t_game *game, int fd)
{
	char	*line;
	char	*trimmed;
	int		directive_count = 0;
	int		map_started = 0;
	int		blank_after_map = 0;

	while ((line = get_next_line(fd)))
	{
		trimmed = ft_strtrim(line, " \t\n");
		free(line);
		if (!trimmed)
			return (fprintf(stderr, "Memory allocation error\n"), -1);

		if (*trimmed == '\0')  // Empty line
		{
			if (map_started)
				blank_after_map = 1;
			free(trimmed);
			continue;
		}

		if (!map_started)
		{
			if (handle_directive_line(game, trimmed, &directive_count))
			{
				free(trimmed);
				continue;
			}
			if (handle_map_line(game, trimmed))
			{
				if (!check_all_directives_present(&game->textures_info))
				{
					fprintf(stderr, "\033[31mError: Map started before all directives were defined\033[0m\n");
					free(trimmed);
					return (-1);
				}
				map_started = 1;
				//append_map_line(game, trimmed);
				free(trimmed);
				continue;
			}
			fprintf(stderr, "\033[31mError: Invalid directive or garbage line:\033[0m %s\n", trimmed);
			free(trimmed);
			return (-1);
		}
		else
		{
			// Already inside map
			if (blank_after_map)
			{
				fprintf(stderr, "\033[31mError: Garbage after map end:\033[0m %s\n", trimmed);
				free(trimmed);
				return (-1);
			}
			if (!handle_map_line(game, trimmed))
			{
				fprintf(stderr, "\033[31mError: Invalid map line:\033[0m %s\n", trimmed);
				free(trimmed);
				return (-1);
			}
			//append_map_line(game, trimmed);
			free(trimmed);
		}
	}
	if (!map_started)
	{
		fprintf(stderr, "\033[31mError: No map found in file\033[0m\n");
		return (-1);
	}
	if (!check_all_directives_present(&game->textures_info))
	{
		fprintf(stderr, "\033[31mError: Missing one or more required directives\033[0m\n");
		return (-1);
	}
	return (0);
}





// ---------------------PARSE MAP-------------------------------------
// main function to parse the map
static int parse_map_file(const char *filepath, t_game *game)
{
	int fd;
	
	if (!has_cub_extension(filepath))
	{
		fprintf(stderr, "Error: Map file must have a .cub extension\n");
		return (1);
	}
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return(perror("Failed to open map") , -1);
	if (read_map_file(game, fd) < 0)
	{
		close(fd);
		return 1;
	}
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
	if (!parse_map_file(map_file, game))
		return(0); 
	validate_map(game, game -> map);
	return 1;
}