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
void free_textures_info(t_textures_info *t);
int encode_rgb(int r, int g, int b);



/* int parse_map_file(const char *filepath, t_game *game);


int has_cub_extension(const char *filename); */

char	**ft_split_tokens(const char *str, const char *charset);
int extract_map_info(char *map_file, t_game *game);


// valid texture path
//int	validate_texture_paths(t_game *game);


// map_validation
int     validate_map(t_game *game, char **original_map);

#endif