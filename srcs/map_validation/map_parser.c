/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 23:36:48 by mpazouki          #+#    #+#             */
/*   Updated: 2025/05/24 00:06:35 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

//------------------parse and validate directive ---------------------

// check the valide keywords for directive
static is_directive(char *line)
{
	return(ft_strncmp(line, "NO", 2) == 0
		|| ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
}

// Check if all required directives (NO, SO, EA, WE, F, C) are present.
static int	validate_directives(t_game *game)
{
	if (!game->textures_info.n_wall_path || !game->textures_info.s_wall_path ||
		!game->textures_info.e_wall_path || !game->textures_info.w_wall_path)
		return (fprintf(stderr, "Error: Missing texture paths\n"), 0);
	if (game->textures_info.floor_color < 0 || game->textures_info.ceiling_color < 0)
		return (fprintf(stderr, "Error: Missing or invalid colors\n"), 0);
	return (1);
}

static int	is_valid_color_range(int n)
{
	return (n >= 0 && n <= 255);
}

static int ft_is_validate_color(char **raw_color)
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
 
static void parse_color(char *value, double *color_field)
{
	int r;
	int g;
	int b;
	char **raw_color;
	if (!value)
	{
		fprintf(stderr, "Error: Missing color value.\n");
		return;
	}
    // ft_split_charset handel all \t and spaces 
	raw_color = ft_split_charset(value, ", \t");
	if (!raw_color || !raw_color[0] || !raw_color[1] || !raw_color[2] || raw_color[3])
	{
		ft_free_map(raw_color);
        fprintf(stderr, "Error: Invalid color format. Expected format: R,G,B\n");
		return ;
	}
	if (!ft_is_validate_color(raw_color))
	{
		ft_free_map(raw_color);
        fprintf(stderr, "Error: Color components must be in range [0–255].\n");
		return;
	}
	*color_field = (ft_atoi(raw_color[0]) << 16) | (ft_atoi(raw_color[1]) << 8) | ft_atoi(raw_color[2]);
	ft_free_map(raw_color);
}

// clean the line from spaces and config the keywords and value
static void parse_directive(t_game *game, char *line)
{
	char **tokens;
	tokens = ft_split_charset(line, '\t');
	if (!tokens || !tokens[0] || !tokens[1] )
	{
		ft_free_map(tokens);
		return;
	}
	if (!ft_strcmp(tokens[0], "NO"))
		game->textures_info.n_wall_path = ft_strdup(tokens[1]);
	else if (!ft_strcmp(tokens[0], "SO"))
		game->textures_info.s_wall_path = ft_strdup(tokens[1]);
	else if (!ft_strcmp(tokens[0], "WE"))
		game->textures_info.w_wall_path = ft_strdup(tokens[1]);
	else if (!ft_strcmp(tokens[0], "EA"))
		game->textures_info.e_wall_path = ft_strdup(tokens[1]);
	else if (!ft_strcmp(tokens[0], "F"))
		parse_color(tokens[1], &game->textures_info.floor_color);
	else if (!ft_strcmp(tokens[0], "C"))
		parse_color(tokens[1], &game->textures_info.ceiling_color);
	ft_free_map(tokens);
}

//------------------------Extracting Map-------------------------

static int is_map_line(const char *line)
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










// main function to parse the map
int parse_map_file(const char *filepath, t_game *game)
{
	int fd;
	char *line;
	int map_start;

	map_start = 0;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return(perror("Failed to open map") , -1);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		if (!map_start && is_directive(line))
			parse_directive(game, line);
		else if (is_map_line(line))
		{
			map_start = 1;
			append_map_line(game, line);
		}
        else if (!map_start)
        {
	        fprintf(stderr, "Error: Invalid directive or garbage line: %s\n", line);
	        free(line);
	        close(fd);
	        return (-1);
        }
		free(line);
	}
	close(fd);
	return(0);
}
