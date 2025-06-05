/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 20:14:39 by mpazouki          #+#    #+#             */
/*   Updated: 2025-06-05 20:14:39 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main_header.h"

// ---------------------validate color -------------------------------
static int	is_valid_color_range(int n)
{
	return (n >= 0 && n <= 255);
}

static int	is_numeric_str(const char *str)
{
	int	i;

	i = 0;
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

int	ft_validate_color(char **raw_color)
{
	int	i;
	int	value;

	i = 0;
	while (raw_color[i])
	{
		if (!is_numeric_str(raw_color[i]))
			return (0);
		value = ft_atoi(raw_color[i]);
		if (!is_valid_color_range(value))
			return (0);
		i++;
	}
	return (1);
}

int	is_missing_color_value(const char *value, const char *label)
{
	if (!value)
	{
		printf("\033[31mError: Missing value for %s color\033[0m\n", label);
		return (1);
	}
	return (0);
}
