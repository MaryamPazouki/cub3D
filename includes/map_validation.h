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
//int		extract_map_info(char *map_file, t_game *game);
int     validate_map(t_game *game, char **original_map);

//handle texture and validate
int 	handle_texture_directive(t_game *game, const char *key, const char *path);

// handle_color_directive.c
int 	handle_color_directive(t_game *game, const char *key, const char *value);

//read_map.c
int		append_map_line(t_game *game, char *line);
int		is_map_line(const char *line);

// map_validation
int 	parse_map_file(const char *filepath, t_game *game);

#endif