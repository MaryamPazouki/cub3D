#ifndef MAP_VALIDATION_H
#define MAP_VALIDATION_H

#include "libft.h"
#include "get_next_line.h"
#include "map_creation.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// free_utils.c
void	ft_free_map(char **map);
void	free_game(t_game *game);
void	free_tokens(char **tokens);



//  int parse_map_file(const char *filepath, t_game *game);

// map_validation_utils.c
int		has_cub_extension(const char *filename);
int		encode_rgb(int r, int g, int b);
char	**ft_split_tokens(const char *str, const char *charset);

// map_parser.c
int		extract_map_info(char *map_file, t_game *game);
int     validate_map(t_game *game, char **original_map);

// valid texture path
//int	validate_texture_paths(t_game *game);


// map_validation


#endif