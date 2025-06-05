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

// ---------------------validate color -------------------------------
static int	is_valid_color_range(int n)
{
	return (n >= 0 && n <= 255);
}

static int is_numeric_str(const char *str)
{
	int i = 0;

	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}


static int ft_validate_color(char **raw_color)
{
	int i;
	int value;

	i = 0;
	while (raw_color[i])
	{
		if (!is_numeric_str(raw_color[i]))
		{
			// fprintf(stderr, "\033[31mError: Non-numeric color component: '%s'\033[0m\n", raw_color[i]);
			return (0);
		}
		value = ft_atoi(raw_color[i]);
		if (!is_valid_color_range(value))
			return (0);
		i++;
	}
	return (1);
}


static int is_missing_color_value(const char *value, const char *label)
{
	if (!value)
	{
		fprintf(stderr, "\033[31mError: Missing value for %s color\033[0m\n", label);
		return (1);
	}
	return (0);
}
static int is_duplicate_color(int *flag, const char *label)
{
	if ((*flag)++)
	{
		fprintf(stderr, "\033[31mError: Duplicate %s directive\033[0m\n", label);
		//ft_free_map(NULL);
		return (1);
	}
	return (0);
}

static int validate_and_parse_rgb(char **raw_color, double *color_field, const char *label)
{
	if (!raw_color || !raw_color[0] || !raw_color[1] || !raw_color[2] || raw_color[3])
	{
		fprintf(stderr, "\033[31mError: Invalid %s color format. Expected: R,G,B\033[0m\n", label);
		return (0);
	}
	if (!ft_validate_color(raw_color))
	{
		fprintf(stderr, "\033[31mError: %s color values must be in range [0–255]\033[0m\n", label);
		return (0);
	}
	*color_field = encode_rgb(
		ft_atoi(raw_color[0]),
		ft_atoi(raw_color[1]),
		ft_atoi(raw_color[2]));
	return (1);
}
// parse_color() return 1 (success) or 0 (error):
static int parse_color(const char *value, double *color_field, int *flag, const char *label)
{
	char **raw_color;

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
int handle_color_directive(t_game *game, const char *key, const char *value)
{
    if (!ft_strcmp(key, "F"))
    {
        if (!parse_color(value, &game->textures_info.floor_color, &game->textures_info.has_f, "F"))
        {
			return(0);
		}
    }
    else if (!ft_strcmp(key, "C"))
    {
        if (!parse_color(value, &game->textures_info.ceiling_color, &game->textures_info.has_c, "C"))
        {
			return(0);
		}
    }
	else {
		fprintf(stderr, "\033[31mError: Unknown color key: %s\033[0m\n", key);
		return (0); // Return error for unknown key
	}
	// Free any allocated resources if necessary
	return (1);
}
