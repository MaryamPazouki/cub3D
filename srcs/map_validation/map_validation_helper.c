/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 19:52:44 by mpazouki          #+#    #+#             */
/*   Updated: 2025-06-05 19:52:44 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

int	handle_map_line(t_game *game, char *line)
{
	if (!is_map_line(line))
		return (0);
	append_map_line(game, line);
	return (1);
}
