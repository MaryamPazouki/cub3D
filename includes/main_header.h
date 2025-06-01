/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:46:38 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/05/29 11:13:06 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HEADER_H
# define MAIN_HEADER_H
# include "libft.h"
# include "get_next_line.h"
# include "map_validation.h"
# include "map_creation.h"
# include <stdbool.h>

// print_debugging_fts.c
void	print_map(char **map);
int		cast_rays(t_game *game, double dir_angle, double *first_cross_dist);

int		extract_map_info(char *map_file, t_game *game);



#endif
