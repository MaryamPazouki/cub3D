/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:53:38 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/05/20 14:27:02 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

static void	init_v_line_vars(t_v_line_vars *vars, int wall_height,
		t_game *game, double ray_angle)
{
	vars->y_start = (WIN_HEIGHT / 2) + (wall_height / 2);
	vars->y_end = (WIN_HEIGHT / 2) - (wall_height / 2);
	if (vars->y_start > WIN_HEIGHT)
		vars->y_start = WIN_HEIGHT;
	if (vars->y_end < 0)
		vars->y_end = 0;
	vars->texture_data = return_texture_type(game, ray_angle);
	vars->wall_x = calculate_wall_x(game, ray_angle);
	vars->tex_x = (int)(vars->wall_x * game->textures_info.width);
}

void	put_vertical_line(int wall_height, int column,
			t_game *game, double ray_angle)
{
	t_v_line_vars	vars;

	init_v_line_vars(&vars, wall_height, game, ray_angle);
	vars.i = vars.y_end;
	while (vars.i < vars.y_start)
	{
		vars.tex_pos = (vars.i - WIN_HEIGHT / 2 + wall_height / 2)
			* (double)game->textures_info.height / wall_height;
		vars.tex_y = (int)vars.tex_pos % game->textures_info.height;
		if (vars.tex_y < 0)
			vars.tex_y = 0;
		if (vars.tex_y >= game->textures_info.height)
			vars.tex_y = game->textures_info.height - 1;
		vars.tex_index = (vars.tex_y * game->texture_size_line)
			+ (vars.tex_x * (game->texture_bpp / 8));
		vars.color = *(uint32_t *)(vars.texture_data + vars.tex_index);
		put_pixel(game, column, vars.i, vars.color);
		vars.i++;
	}
}

void	cast_and_creat_pseudo_3d_env(t_game *game)
{
	double	angle_init;
	int		height;
	double	ray_angle;
	int		i;

	angle_init = game->dir_angle - (M_PI / 6);
	height = 0;
	i = 0;
	while (i < WIN_WIDTH)
	{
		ray_angle = angle_init + (i * game->ray_step);
		if (cast_rays(game, ray_angle, &game->true_ray_dist) == -1)
		{
			ft_putstr_fd("Error: Ray out of map bounds\n", STDERR_FILENO);
			free_game_struct(game);
			exit (1);
		}
		game->perp_wall_dist = game->true_ray_dist
			* cos(ray_angle - game->dir_angle);
		height = (game->projected_slice_height
				/ (game->perp_wall_dist * game->textures_info.width)) * 4;
		put_vertical_line(height, i, game, ray_angle);
		i++;
	}
}

void	draw_screen(t_game *game)
{
	clear_screen(game);
	print_ceiling_floor(game);
	cast_and_creat_pseudo_3d_env(game);
	cast_fov_rays(game);
	put_map_background_2(game, game->x_start_minimap, game->y_start_minimap);
	put_player_position(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
