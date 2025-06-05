#ifndef MAP_VALIDATION_H
# define MAP_VALIDATION_H

# include "get_next_line.h"
# include "libft.h"
# include "map_creation.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

// free_utils.c
void	ft_free_map(char **map);
void	free_game(t_game *game);
void	free_tokens(char **tokens);

//  int parse_map_file(const char *filepath, t_game *game);

// map_parse_utils.c
int		is_blank_line(const char *line);
size_t	ft_strcspn(const char *s, const char *reject);
char	*safe_trim_line(char *line);
int		check_garbage_after_map(char *line);
int		is_directive(char *line);

// map_parse_helper.c
int		check_all_directives_present(t_textures_info *t);
int		parse_texture_directive(t_game *game, char **tokens);
int		parse_color_directive(t_game *game, char **tokens);
int		parse_directive(t_game *game, char *line);
int		handle_directive_line(t_game *game, char *line);

// map_validation_utils.c
int		has_cub_extension(const char *filename);
int		encode_rgb(int r, int g, int b);
char	**ft_split_tokens(const char *str, const char *charset);
int	map_height(char **map);
//int	flood_fill_safe(char **map, int x, int y, int *visited_count);
int	validate_map_enclosure_and_reachability(char **normalized_map, int start_x, int start_y);
int	count_total_zeroes(char **map);
char	*pad_line_with_walls(const char *line, int target_width);
char	*create_padding_row(int width);
int	map_max_width(char **map);
char	**normalized_map(char **map, int height, int width);
int	count_total_zeroes(char **map);



// map_validation_helper.c
int		handle_map_line(t_game *game, char *line);

// map_parser.c
// int		extract_map_info(char *map_file, t_game *game);
int		validate_map(t_game *game, char **original_map);

// handle texture and validate
int		handle_texture_directive(t_game *game, const char *key,
			const char *path);

// handle_color_directive.c
int		handle_color_directive(t_game *game, const char *key,
			const char *value);
int		ft_validate_color(char **raw_color);
int		is_missing_color_value(const char *value, const char *label);

	// read_map.c
int		append_map_line(t_game *game, char *line);
int		is_map_line(const char *line);

// read_map_utils.c
char	*pad_line_with_spaces(char *line);	
void	update_game_map(t_game *game, char **new_map);
int		copy_and_append_line(t_game *game, char **new_map, char *padded_line);
char	**allocate_new_map(t_game *game);


// map_validation
int		parse_map_file(const char *filepath, t_game *game);

#endif