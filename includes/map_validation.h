#ifndef MAP_VALIDATION_H
#define MAP_VALIDATION_H

#include "libft.h"
#include "get_next_line.h"
#include "map_creation.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// map_validation_utils.c
void	ft_free_map(char **map);

// map_validation.c
//char	**validate_map(char *map);


int parse_map_file(const char *filepath, t_game *game);

#endif