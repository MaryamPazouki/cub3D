/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 23:36:48 by mpazouki          #+#    #+#             */
/*   Updated: 2025/06/04 09:21:10 by mpazouki         ###   ########.fr       */
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



static int check_all_directives_present(t_textures_info *t)
{
	if (!t->has_no || !t->has_so || !t->has_we || !t->has_ea ||
		!t->has_f || !t->has_c)
	{
		// if (!t->has_no) fprintf(stderr, "Missing NO directive\n");
		// if (!t->has_so) fprintf(stderr, "Missing SO directive\n");
		// if (!t->has_we) fprintf(stderr, "Missing WE directive\n");
		// if (!t->has_ea) fprintf(stderr, "Missing EA directive\n");
		// if (!t->has_f) fprintf(stderr, "Missing F directive\n");
		// if (!t->has_c) fprintf(stderr, "Missing C directive\n");
		return (0);
	}
	return (1);
}

int parse_texture_directive(t_game *game, char **tokens)
{
	if (!handle_texture_directive(game, tokens[0], tokens[1]))
	{
		free_tokens(tokens);
		return (0);
	}
	free_tokens(tokens);
	return (1);
}

int parse_color_directive(t_game *game, char **tokens)
{
	if (!handle_color_directive(game, tokens[0], tokens[1]))
	{
		free_tokens(tokens);
		return (0);
	}
	free_tokens(tokens);
	return (1);
}

int parse_directive(t_game *game, char *line)
{
	char **tokens;

	tokens = ft_split_tokens(line, " \t");
	if (!tokens || !tokens[0] || !tokens[1])
	{
		free_tokens(tokens);
		return (0);
	}

	if (!ft_strcmp(tokens[0], "NO") || !ft_strcmp(tokens[0], "SO") ||
 		!ft_strcmp(tokens[0], "WE") || !ft_strcmp(tokens[0], "EA"))
		return parse_texture_directive(game, tokens);

	if (!ft_strcmp(tokens[0], "F") || !ft_strcmp(tokens[0], "C"))
		return parse_color_directive(game, tokens);

	fprintf(stderr, "Error: Unknown directive: %s\n", tokens[0]);
	free_tokens(tokens);
	return (0);
}

static int	handle_directive_line(t_game *game, char *line)
 {
	if (!is_directive(line) && !is_map_line(line))
	{
		fprintf(stderr, "\033[31mError: Invalid directive or garbage line:\033[0m %s\n", line);
		return (0);
	}
	if (parse_directive(game, line) == 0)
		return (0);
	return (1);
}


static int	handle_map_line(t_game *game, char *line)
{
	if (!is_map_line(line))
		return (0);
	append_map_line(game, line);
	return (1);
}


static int is_blank_line(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

static size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t i = 0;
	while (s[i])
	{
		for (size_t j = 0; reject[j]; j++)
		{
			if (s[i] == reject[j])
				return (i);
		}
		i++;
	}
	return (i);
}

// --- Helper: check for garbage after map ---
static int check_garbage_after_map(char *line)
{
	fprintf(stderr, "\033[31mError: Garbage after map end:\033[0m %s\n", line);
	free(line);
	return (0);
}

// --- Helper: trim a line or return error ---
static char *safe_trim_line(char *line)
{
	char *trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
	{
		free(line);
		fprintf(stderr, "Memory allocation error\n");
		return (NULL);
	}
	return (trimmed);
}

int	process_directive_stage(t_game *game, char *line, char *trimmed, int *map_started)
{
	if (handle_directive_line(game, trimmed))
	{
		free(trimmed);
		free(line);
		return (1);
	}
	line[ft_strcspn(line, "\n")] = '\0';
	if (is_map_line(line))
	{
		if (!check_all_directives_present(&game->textures_info))
		{
			fprintf(stderr, "\033[31mError: Map started before all directives were defined\033[0m\n");
			free(trimmed);
			free(line);
			return (0);
		}
		*map_started = 1;
		handle_map_line(game, line);
		free(trimmed);
		free(line);
		return (1);
	}
	free(trimmed);
	free(line);
	return (0);
}

int	process_map_stage(t_game *game, char *line, char *trimmed)
{
	line[ft_strcspn(line, "\n")] = '\0';
	if (!handle_map_line(game, line))
	{
		fprintf(stderr, "\033[31mError: Invalid map line:\033[0m %s\n", line);
		free(trimmed);
		free(line);
		return (0);
	}
	free(trimmed);
	free(line);
	return (1);
}

int	process_line(t_game *game, char *line, int *map_started, int *blank_after_map)
{
	char *trimmed;

	if (is_blank_line(line))
	{
		if (*map_started)
			*blank_after_map = 1;
		free(line);
		return (1);
	}
	if (*blank_after_map)
		return (check_garbage_after_map(line));
	
	trimmed = safe_trim_line(line);
	if (!trimmed)
		return (0);

	if (!*map_started)
		return (process_directive_stage(game, line, trimmed, map_started));
	else
		return (process_map_stage(game, line, trimmed));
}


int	read_map_file(t_game *game, int fd)
{
	char	*line;
	int		result;
	int		map_started = 0;
	int		blank_after_map = 0;

	while ((line = get_next_line(fd)))
	{
		result = process_line(game, line, &map_started, &blank_after_map);
		if (!result)
			return (0);
	}
	free(line); 
	if (!map_started)
	{
		fprintf(stderr, "\033[31mError: No map found in file\033[0m\n");
		return (0);
	}
	return (1);
}


// ---------------------PARSE MAP-------------------------------------
// main function to parse the map
int parse_map_file(const char *filepath, t_game *game)
{
	int fd;
	if (!has_cub_extension(filepath))
	{
		fprintf(stderr, "\033[31mError: Map file must have a .cub extension\033[0m\n");
		return (0);
	}
	fd = open(filepath, O_RDONLY);
	if (fd < 0) {
		perror("Failed to open map");
		return 0;
	}
	if (read_map_file(game, fd) == 0)
	{
		close(fd);
		return 0;
	}
	close(fd);
	if (!game->map || !game->map[0])
	{
		fprintf(stderr, "\033[31mError: Empty map\033[0m\n");
		return 0;
	}
	return 1;
}

// //parse texture and colors
// int parse_directive(t_game *game, char *line)
// {
// 	char **tokens;

// 	tokens = ft_split_tokens(line, " \t");
// 	if (!tokens || !tokens[0] || !tokens[1])
// 	{
// 		//fprintf(stderr, "Error: Invalid directive format\n");
// 		free_tokens(tokens);
// 		return (0);
// 	}
// 	if (!ft_strcmp(tokens[0], "NO") || !ft_strcmp(tokens[0], "SO") ||
// 		!ft_strcmp(tokens[0], "WE") || !ft_strcmp(tokens[0], "EA"))
// 	{
// 		if (!handle_texture_directive(game, tokens[0], tokens[1]))
// 		{
// 			free_tokens(tokens);
// 			return (0);
// 		}
// 	}
// 	else if (!ft_strcmp(tokens[0], "F") || !ft_strcmp(tokens[0], "C"))
// 	{
// 		if (!handle_color_directive(game, tokens[0], tokens[1]))
// 		{
// 			free_tokens(tokens);
// 			return (0);
// 		}
// 	}
// 	else if (!is_directive(tokens[0]))
// 	{
//  		fprintf(stderr, "Error: Unknown directive: %s\n", tokens[0]);
// 		free_tokens(tokens);
// 		return (0);
// 	}
// 	free_tokens(tokens);
// 	return (1);
// }
// int read_map_file(t_game *game, int fd)
// {
// 	char	*line;
// 	char	*trimmed;
// 	int		map_started = 0;
// 	int		blank_after_map = 0;

// 	while ((line = get_next_line(fd)))
// 	{
// 		if (is_blank_line(line))
// 		{
// 			if (map_started)
// 				blank_after_map = 1;
// 			free(line);
// 			continue;
// 		}

// 		if (blank_after_map)
// 		{
// 			fprintf(stderr, "\033[31mError: Garbage after map end:\033[0m %s\n", line);
// 			free(line);
// 			return (0);
// 		}

// 		// Trim for directive check
// 		trimmed = ft_strtrim(line, " \t\n");
// 		if (!trimmed)
// 		{
//     		free(line);
// 			return (fprintf(stderr, "Memory allocation error\n"), 0);
// 		}

// 		if (!map_started)
// 		{
// 			if (handle_directive_line(game, trimmed))
// 			{
// 				free(trimmed);
// 				free(line);
// 				continue;
// 			}

// 			// Remove newline before map line check
// 			line[ft_strcspn(line, "\n")] = '\0';

// 			if (is_map_line(line))
// 			{
// 				if (!check_all_directives_present(&game->textures_info))
// 				{
// 					fprintf(stderr, "\033[31mError: Map started before all directives were defined\033[0m\n");
// 					free(trimmed);
// 					free(line);
// 					return (0);
// 				}
// 				map_started = 1;
// 				handle_map_line(game, line);
// 				free(trimmed);
// 				free(line);
// 				continue;
// 			}
// 			//fprintf(stderr, "\033[31mError: Invalid directive or garbage line:\033[0m %s\n", line);
// 			free(trimmed);
// 			free(line);
// 			return (0);
			
// 		}
// 		else
// 		{
// 			// Map already started
// 			line[ft_strcspn(line, "\n")] = '\0';
// 			if (!handle_map_line(game, line))
// 			{
// 				fprintf(stderr, "\033[31mError: Invalid map line:\033[0m %s\n", line);
// 				free(trimmed);
// 				free(line);
// 				return (0);
// 			}
// 		}
// 		free(trimmed);
// 		free(line);
// 	}

// 	if (!map_started)
// 	{
// 		fprintf(stderr, "\033[31mError: No map found in file\033[0m\n");
// 		return (0);
// 	}
// 	return (1);
// }





// static int is_texture_directive(const char *token)
// {
// 	return (!ft_strcmp(token, "NO") ||
// 			!ft_strcmp(token, "SO") ||
// 			!ft_strcmp(token, "WE") ||
// 			!ft_strcmp(token, "EA"));
// }

// static int is_color_directive(const char *token)
// {
// 	return (!ft_strcmp(token, "F") ||
// 			!ft_strcmp(token, "C"));
// }

// static int handle_directive_error(char **tokens, const char *message)
// {
// 	fprintf(stderr, "Error: %s\n", message);
// 	free_tokens(tokens);
// 	return (0);
// }

// static int process_texture_directive(t_game *game, char **tokens)
// {
// 	if (handle_texture_directive(game, tokens[0], tokens[1]))
// 	{
// 		free_tokens(tokens);
// 		return (0);
// 	}
// 	free_tokens(tokens);
// 	return (1);
// }

// static int process_color_directive(t_game *game, char **tokens)
// {
// 	if (handle_color_directive(game, tokens[0], tokens[1]))
// 	{
// 		free_tokens(tokens);
// 		return (1); // return 1 on success
// 	}
// 	free_tokens(tokens);
// 	return (0);
// }

// int parse_directive(t_game *game, char *line)
// {
// 	char **tokens = ft_split_tokens(line, " \t");

// 	if (!tokens || !tokens[0] || !tokens[1])
// 		return handle_directive_error(tokens, "Invalid directive format");

// 	if (is_texture_directive(tokens[0]))
// 		return process_texture_directive(game, tokens);
// 	else if (is_color_directive(tokens[0]))
// 		return process_color_directive(game, tokens);
// 	else
// 	{
// 		char msg[256];
// 		snprintf(msg, sizeof(msg), "Unknown directive: %s", tokens[0]);
// 		return handle_directive_error(tokens, msg);
// 	}
// }
