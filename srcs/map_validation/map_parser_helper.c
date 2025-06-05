/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 19:45:55 by mpazouki          #+#    #+#             */
/*   Updated: 2025-06-05 19:45:55 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main_header.h"

int	check_all_directives_present(t_textures_info *t)
{
	if (!t->has_no || !t->has_so || !t->has_we || !t->has_ea || !t->has_f
		|| !t->has_c)
		return (0);
	return (1);
}

int	parse_texture_directive(t_game *game, char **tokens)
{
	if (!handle_texture_directive(game, tokens[0], tokens[1]))
	{
		free_tokens(tokens);
		return (0);
	}
	free_tokens(tokens);
	return (1);
}

int	parse_color_directive(t_game *game, char **tokens)
{
	if (!handle_color_directive(game, tokens[0], tokens[1]))
	{
		free_tokens(tokens);
		return (0);
	}
	free_tokens(tokens);
	return (1);
}

int	parse_directive(t_game *game, char *line)
{
	char	**tokens;

	tokens = ft_split_tokens(line, " \t");
	if (!tokens || !tokens[0] || !tokens[1])
	{
		free_tokens(tokens);
		return (0);
	}
	if (!ft_strcmp(tokens[0], "NO") || !ft_strcmp(tokens[0], "SO")
		|| !ft_strcmp(tokens[0], "WE") || !ft_strcmp(tokens[0], "EA"))
		return (parse_texture_directive(game, tokens));
	if (!ft_strcmp(tokens[0], "F") || !ft_strcmp(tokens[0], "C"))
		return (parse_color_directive(game, tokens));
	fprintf(stderr, "Error: Unknown directive: %s\n", tokens[0]);
	free_tokens(tokens);
	return (0);
}

int	handle_directive_line(t_game *game, char *line)
{
	if (!is_directive(line) && !is_map_line(line))
	{
		fprintf(stderr,
			"\033[31mError: Invalid directive or garbage line:\033[0m %s\n",
			line);
		return (0);
	}
	if (parse_directive(game, line) == 0)
		return (0);
	return (1);
}
