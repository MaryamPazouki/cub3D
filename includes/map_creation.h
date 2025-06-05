/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:33:51 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/06/01 23:22:16 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_CREATION_H
# define MAP_CREATION_H

# include "libft.h"
# include "get_next_line.h"
# include "map_validation.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <sys/time.h>

# define GRID_SIZE 16
# define TEXTURE_SIZE 64
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "Cub3D - Raycaster"

# define BLUE 0x0000FF
# define GREEN 0x00FF00
# define RED 0xFF0000
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define PURPLE 0x800080
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF

typedef struct s_textures_info
{
	char	*n_wall_path; // string created in map validation
	char	*w_wall_path; // string created in map validation
	char	*s_wall_path; // string created in map validation
	char	*e_wall_path; // string created in map validation
	double	floor_color;  // double created in map validation
	double 	ceiling_color; // double created in map validation
	
	// NEW flags to detect duplicates
	int		has_no;
	int		has_so;
	int		has_we;
	int		has_ea;
	int		has_f;
	int		has_c;
	
	int		width;
	int		height;
}	t_textures_info;

typedef struct s_loaded_textures
{
	void	*n_wall;
	char	*n_wall_data;
	void	*w_wall;
	char	*w_wall_data;
	void	*s_wall;
	char	*s_wall_data;
	void	*e_wall;
	char	*e_wall_data;
}	t_loaded_textures;

typedef struct s_game
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*img_data;
	char				**map; 
	int 				player_count;
	int					bpp;
	int					size_line;
	int					endian;
	int					texture_bpp;
	int					texture_size_line;
	int					texture_endian;
	int					x_start_minimap;
	int					y_start_minimap;
	int					side;
	double				ray_step;
	double				perp_wall_dist;
	double				true_ray_dist;
	int					projected_slice_height;
	int					map_rows;
	int					map_cols;
	int					map_width; // int created in map validation
	int					map_height;// int created in map validation
	double				pos_x; // double created in map validation (optional)
	double				pos_y; // double created in map validation (optional)
	double				dir_angle;
	double				dir_x;
	double				dir_y;
	double				temp_x_move;
	double				temp_y_move;
	int					key_w;
	int					key_a;
	int					key_s;
	int					key_d;
	int					key_left;
	int					key_right;
	t_textures_info		textures_info;
	t_loaded_textures	loaded_textures;
}	t_game;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_v_line_vars
{
	int			y_start;
	int			y_end;
	char		*texture_data;
	double		wall_x;
	int			tex_x;
	int			i;
	double		tex_pos;
	int			tex_y;
	int			tex_index;
	uint32_t	color;
}	t_v_line_vars;

typedef struct s_ray_params
{
	double	dir_x;
	double	dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	next_x;
	double	next_y;
	double	dist_to_x_wall;
	double	dist_to_y_wall;
	int		map_x;
	int		map_y;
	int		exit_status;
}	t_ray_params;

int		handle_close(t_game *game);

// initialize_mlx.c
int		initialize_mlx_and_launch_game(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);

// handle_keys.c
int		handle_keypress(int keysym, t_game *game);
int		handle_keyrelease(int keysym, t_game *game);
int		handle_close(t_game *game);
void	free_game_struct(t_game *game);

// initialize_game_struct.c
int		initialize_game_struct(t_game *game);
void	initialize_game_vars(t_game *game);

// game_loop.c
int		game_loop(t_game *game);
int		is_valid_position(t_game *game, double new_x, double new_y);
double	get_delta_time(void);
void	update_move(t_game *game, double move_x, double move_y);

// put_map_utils.c
void	clear_screen(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
void	print_ceiling_floor(t_game *game);
double	calculate_wall_x(t_game *game, double ray_angle);
char	*return_texture_type(t_game *game, double ray_angle);

// put_map.c
void	draw_direction_line(t_game *game, int distance,
			double dir_x, double dir_y);
void	draw_screen(t_game *game);

// put_minimap.c
void	put_map_background_2(t_game *game, int x_offset, int y_offset);
void	put_player_position(t_game *game);
void	cast_fov_rays(t_game *game);

// Add to main_header.h
int		cast_rays(t_game *game, double dir_angle, double *first_cross_dist);

//int		extract_map_info(char *map_file, t_game *game);
#endif
