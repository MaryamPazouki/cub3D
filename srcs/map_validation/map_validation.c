#include "main_header.h"

int count_lines(const char *filename)
{
	int fd;
	int count;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return 0;
	count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	return count;
}

char **read_map(const char *filename)
{
	int line_count;
	int fd;
	char **map;
	char *line;
	int i;

	line_count = count_lines(filename);
	if (line_count == 0)
		return NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return NULL;
	map = malloc((line_count + 1) * sizeof(char *));
	if (!map)
	{
		close(fd);
		return NULL;
	}
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map[i++] = line;
	}
	map[i] = NULL;
	close(fd);
	return map;
}

// char	**validate_map(char *map_file)
// {
// 	char **map;

// 	if (!map_file)
// 		return NULL; // print error
// 	map = read_map(map_file);
// 	// check if map is valid before returning
// 	return (map);
// 	// check extension
// 	// 
// }

// // int get_textures_info_and_colors(char **file_lines, t_game *game)
// // {
	
// // }
// // int	extract_map_info(char *map_file, t_game *game)
// // {
// // 	char	**file_lines;

// // 	if (!map_file)
// // 		return (-1); // print error
// // 	file_lines = read_map(map_file);
// // 	if (!file_lines)
// // 		return (-1);
// // 	// Extract relevant information from file_lines and populate game struct
// // 	get_textures_info_and_colors(file_lines, game);
// // 	return (0);
// // }
















































#include "main_header.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper to check if a line is a map line (contains only valid map characters)
static int is_map_line(const char *line) {
    if (!line || !*line)
        return 0;
    for (int i = 0; line[i]; i++) {
        if (!strchr("01NSEW \t", line[i]))
            return 0;
    }
    return 1;
}

// Helper to trim whitespace from start and end of a string
static char *trim_whitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str))
        str++;
    if (!*str)
        return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    *(end + 1) = '\0';
    return str;
}

// Helper to parse RGB color (e.g., "220,100,0") to a double (packed RGB)
static double parse_color(const char *color_str, int *error) {
    int r, g, b;
    char *trimmed = trim_whitespace(strdup(color_str));
    if (sscanf(trimmed, "%d,%d,%d", &r, &g, &b) != 3 ||
        r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        *error = 1;
        free(trimmed);
        return 0;
    }
    free(trimmed);
    // Pack RGB into a double (e.g., as an integer 0xRRGGBB)
    return (double)((r << 16) | (g << 8) | b);
}

// Helper to check if a line starts with a specific identifier
static int starts_with(const char *line, const char *prefix) {
    char *trimmed = trim_whitespace(strdup(line));
    int result = strncmp(trimmed, prefix, strlen(prefix)) == 0;
    free(trimmed);
    return result;
}

// Parse texture paths and colors, return index of first map line
static int get_textures_info_and_colors(char **file_lines, t_game *game) {
    int i = 0;
    int textures_found = 0;
    int floor_found = 0, ceiling_found = 0;
    int error = 0;

    while (file_lines[i] && !is_map_line(file_lines[i])) {
        char *line = trim_whitespace(file_lines[i]);
        if (!*line) {
            i++;
            continue;
        }

        if (starts_with(line, "NO ") && !game->textures_info.n_wall_path) {
            game->textures_info.n_wall_path = strdup(line + 3);
            textures_found++;
        } else if (starts_with(line, "SO ") && !game->textures_info.s_wall_path) {
            game->textures_info.s_wall_path = strdup(line + 3);
            textures_found++;
        } else if (starts_with(line, "WE ") && !game->textures_info.w_wall_path) {
            game->textures_info.w_wall_path = strdup(line + 3);
            textures_found++;
        } else if (starts_with(line, "EA ") && !game->textures_info.e_wall_path) {
            game->textures_info.e_wall_path = strdup(line + 3);
            textures_found++;
        } else if (starts_with(line, "F ") && !floor_found) {
            game->textures_info.floor_color = parse_color(line + 2, &error);
            if (error)
                return (ft_putstr_fd("Error: Invalid floor color\n", STDERR_FILENO), -1);
            floor_found = 1;
        } else if (starts_with(line, "C ") && !ceiling_found) {
            game->textures_info.ceiling_color = parse_color(line + 2, &error);
            if (error)
                return (ft_putstr_fd("Error: Invalid ceiling color\n", STDERR_FILENO), -1);
            ceiling_found = 1;
        } else {
            return (ft_putstr_fd("Error: Invalid or duplicate identifier\n", STDERR_FILENO), -1);
        }
        i++;
    }

    if (textures_found != 4 || !floor_found || !ceiling_found)
        return (ft_putstr_fd("Error: Missing required identifiers\n", STDERR_FILENO), -1);
    return i; // Index of first map line
}

// Validate map: check rectangular, walls, valid chars, one player
static int validate_map_content(char **map, int start_idx, t_game *game) {
    int rows = 0, max_cols = 0, player_count = 0;
    int i, j;

    // Count rows and max columns
    for (i = start_idx; map[i]; i++) {
        int len = strlen(trim_whitespace(map[i]));
        if (len > max_cols)
            max_cols = len;
        rows++;
    }
    if (rows == 0)
        return -1;

    // Create cleaned map array
    char **clean_map = malloc((rows + 1) * sizeof(char *));
    if (!clean_map)
        return -1;

    for (i = 0; i < rows; i++) {
        clean_map[i] = malloc(max_cols + 1);
        if (!clean_map[i])
            return -1;
        memset(clean_map[i], ' ', max_cols);
        clean_map[i][max_cols] = '\0';
        char *line = trim_whitespace(map[start_idx + i]);
        for (j = 0; j < (int)strlen(line) && j < max_cols; j++) {
            clean_map[i][j] = line[j];
        }
    }
    clean_map[rows] = NULL;

    // Validate map content
    for (i = 0; i < rows; i++) {
        for (j = 0; j < max_cols; j++) {
            char c = clean_map[i][j];
            if (!strchr("01NSEW ", c))
                return -1;
            if (strchr("NSEW", c)) {
                player_count++;
                game->pos_x = j + 0.5;
                game->pos_y = i + 0.5;
                if (c == 'N')
                    game->dir_angle = 3 * M_PI / 2;
                else if (c == 'S')
                    game->dir_angle = M_PI / 2;
                else if (c == 'E')
                    game->dir_angle = 0;
                else if (c == 'W')
                    game->dir_angle = M_PI;
                clean_map[i][j] = '0'; // Replace player with floor
                game->dir_x = cos(game->dir_angle);
                game->dir_y = sin(game->dir_angle);
            }
            // Check borders
            if ((i == 0 || i == rows - 1 || j == 0 || j == max_cols - 1) &&
                c != '1' && c != ' ')
                return (ft_putstr_fd("Error: Map is not surrounded by walls\n", STDERR_FILENO), -1);
            // Check if open spaces are enclosed
            if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W') {
                if ((i > 0 && clean_map[i-1][j] == ' ') ||
                    (i < rows-1 && clean_map[i+1][j] == ' ') ||
                    (j > 0 && clean_map[i][j-1] == ' ') ||
                    (j < max_cols-1 && clean_map[i][j+1] == ' ')) {
						printf("clean_map[%d]: %s\n", i, clean_map[i]);
						printf("clean_map[%d]: %s\n", i + 1, clean_map[i + 1]);
                    	return (printf("clean_map[%d]: %s\n", i, clean_map[i - 1]), -1);
					}
            }
        }
    }

    if (player_count != 1)
        return -1;

    game->map = clean_map;
    game->map_rows = rows; // don't know what for
    game->map_cols = max_cols; // don't know what for
    return 0;
}

char **validate_map(char *map_file) {
    char **map = read_map(map_file);
    if (!map)
        return NULL;

    // Check file extension
    if (!strstr(map_file, ".cub")) {
        // Free map and return NULL
        for (int i = 0; map[i]; i++)
            free(map[i]);
        free(map);
        return NULL;
    }

    return map; // Will be processed further in extract_map_info
}

int extract_map_info(char *map_file, t_game *game) {
    char **file_lines = validate_map(map_file);
    if (!file_lines)
        return -1;

    // Initialize textures_info
    game->textures_info.n_wall_path = NULL;
    game->textures_info.s_wall_path = NULL;
    game->textures_info.w_wall_path = NULL;
    game->textures_info.e_wall_path = NULL;
    game->textures_info.floor_color = 0;
    game->textures_info.ceiling_color = 0;
    game->textures_info.width = 0; // Set later if needed
    game->textures_info.height = 0; // Set later if needed

    // Get textures and colors
    int map_start_idx = get_textures_info_and_colors(file_lines, game);
    if (map_start_idx < 0) {
        // Free resources and return error
        free(game->textures_info.n_wall_path);
        free(game->textures_info.s_wall_path);
        free(game->textures_info.w_wall_path);
        free(game->textures_info.e_wall_path);
        for (int i = 0; file_lines[i]; i++)
            free(file_lines[i]);
        free(file_lines);
        return -1;
    }

    // Validate map content and populate game->map
    if (validate_map_content(file_lines, map_start_idx, game) < 0) {
        // Free resources and return error
        free(game->textures_info.n_wall_path);
        free(game->textures_info.s_wall_path);
        free(game->textures_info.w_wall_path);
        free(game->textures_info.e_wall_path);
        for (int i = 0; file_lines[i]; i++)
            free(file_lines[i]);
        free(file_lines);
        if (game->map) {
            for (int i = 0; game->map[i]; i++)
                free(game->map[i]);
            free(game->map);
        }
        return -1;
    }

    // Free original file_lines
    for (int i = 0; file_lines[i]; i++)
        free(file_lines[i]);
    free(file_lines);

    // // Initialize direction and plane (assuming dir_angle set)
    // game->dir_x = cos(game->dir_angle);
    // game->dir_y = sin(game->dir_angle);
    // game->plane_x = -game->dir_y * 0.66; // FOV ~66 degrees
    // game->plane_y = game->dir_x * 0.66;

    return 0;
}
