/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validartion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 08:55:30 by mpazouki          #+#    #+#             */
/*   Updated: 2025-06-05 08:55:30 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

static int	is_duplicate_color(int *flag, const char *label)
{
	if ((*flag)++)
	{
		printf("\033[31mError: Duplicate %s directive\033[0m\n", label);
		return (1);
	}
	return (0);
}

static int	validate_and_parse_rgb(char **raw_color, double *color_field,
		const char *label)
{
	if (!raw_color || !raw_color[0] || !raw_color[1] || !raw_color[2]
		|| raw_color[3])
	{
		printf("\033[31mInvalid %s color format. Expected: R,G,B\033[0m\n", label);
		return (0);
	}
	if (!ft_validate_color(raw_color))
	{
		printf("\033[31m %s color values must be in range [0–255]\033[0m\n", label);
		return (0);
	}
	*color_field = encode_rgb(ft_atoi(raw_color[0]), ft_atoi(raw_color[1]),
			ft_atoi(raw_color[2]));
	return (1);
}

// parse_color() return 1 (success) or 0 (error):
static int	parse_color(const char *value, double *color_field, int *flag,
		const char *label)
{
	char	**raw_color;

	if (is_missing_color_value(value, label))
		return (0);
	if (is_duplicate_color(flag, label))
		return (0);
	raw_color = ft_split_tokens(value, ", \t");
	if (!validate_and_parse_rgb(raw_color, color_field, label))
	{
		ft_free_map(raw_color);
		return (0);
	}
	ft_free_map(raw_color);
	return (1);
}

int	handle_color_directive(t_game *game, const char *key, const char *value)
{
	if (!ft_strcmp(key, "F"))
	{
		if (!parse_color(value, &game->textures_info.floor_color,
				&game->textures_info.has_f, "F"))
		{
			return (0);
		}
	}
	else if (!ft_strcmp(key, "C"))
	{
		if (!parse_color(value, &game->textures_info.ceiling_color,
				&game->textures_info.has_c, "C"))
		{
			return (0);
		}
	}
	else
	{
		printf("\033[31mError: Unknown color key: %s\033[0m\n", key);
		return (0);
	}
	return (1);
}
