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

char	**ft_split_tokens(const char *str, const char *charset);
int has_cub_extension(const char *filename);


// valid texture path
int	validate_texture_paths(t_game *game);

// validate the map
int is_map_closed(char **map);

#endif