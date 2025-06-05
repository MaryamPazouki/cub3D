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

int	process_directive_stage(t_game *game, char *line, char *trimmed,
		int *map_started)
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
			printf("\033[31m Map started before all directives\033[0m\n");
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
		printf("\033[31mError: Invalid map line:\033[0m %s\n", line);
		free(trimmed);
		free(line);
		return (0);
	}
	free(trimmed);
	free(line);
	return (1);
}

int	process_line(t_game *game, char *line, int *map_started,
		int *blank_after_map)
{
	char	*trimmed;

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
	int		map_started;
	int		blank_after_map;

	map_started = 0;
	blank_after_map = 0;
	while ((line = get_next_line(fd)))
	{
		result = process_line(game, line, &map_started, &blank_after_map);
		if (!result)
			return (0);
	}
	free(line);
	if (!map_started)
	{
		printf("\033[31mError: No map found in file\033[0m\n");
		return (0);
	}
	get_next_line_cleanup();
	return (1);
}

// ---------------------PARSE MAP-------------------------------------
// main function to parse the map
int	parse_map_file(const char *filepath, t_game *game)
{
	int	fd;

	if (!has_cub_extension(filepath))
	{
		printf("\033[31mError: Map file must have a .cub extension\033[0m\n");
		return (0);
	}
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		printf("\033[31mFailed to open map\033[0m\n");
		return (0);
	}
	if (read_map_file(game, fd) == 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (!game->map || !game->map[0])
	{
		printf("\033[31mError: Empty map\033[0m\n");
		return (0);
	}
	return (1);
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
// 			continue ;
// 		}

// 		if (blank_after_map)
// 		{
// 			fprintf(stderr, "\033[31mError: Garbage after map end:\033[0m %s\n",
//				line);
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
// 				continue ;
// 			}

// 			// Remove newline before map line check
// 			line[ft_strcspn(line, "\n")] = '\0';

// 			if (is_map_line(line))
// 			{
// 				if (!check_all_directives_present(&game->textures_info))
// 				{
// 					fprintf(stderr,
//						"\033[31mError: Map started before
//  all directives were defined\033[0m\n");
// 					free(trimmed);
// 					free(line);
// 					return (0);
// 				}
// 				map_started = 1;
// 				handle_map_line(game, line);
// 				free(trimmed);
// 				free(line);
// 				continue ;
// 			}
// 			//fprintf(stderr,
//				"\033[31mError: Invalid directive or garbage line:\033[0m %s\n",
//				line);
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
// 				fprintf(stderr, "\033[31mError: Invalid map line:\033[0m %s\n",
//					line);
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
// 		return (handle_directive_error(tokens, "Invalid directive format"));

// 	if (is_texture_directive(tokens[0]))
// 		return (process_texture_directive(game, tokens));
// 	else if (is_color_directive(tokens[0]))
// 		return (process_color_directive(game, tokens));
// 	else
// 	{
// 		char msg[256];
// 		snprintf(msg, sizeof(msg), "Unknown directive: %s", tokens[0]);
// 		return (handle_directive_error(tokens, msg));
// 	}
// }
