/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:29:07 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/05/20 13:36:34 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

void	initialize_game_vars(t_game *game)
{
	game->key_w = 0;
	game->key_a = 0;
	game->key_s = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
	game->ray_step = (M_PI / 3) / WIN_WIDTH;
}

// txld = texture load
// txinfo = texture info
int	load_textures(t_game *game, t_loaded_textures *txld,
	t_textures_info *txinfo)
{
	txld->n_wall = mlx_xpm_file_to_image(game->mlx, txinfo->n_wall_path,
			&txinfo->width, &txinfo->height);
	if (!txld->n_wall)
		return (ft_putstr_fd("Error: North wall\n", STDERR_FILENO), -1);
	txld->n_wall_data = mlx_get_data_addr(txld->n_wall, &game->texture_bpp,
			&game->texture_size_line, &game->texture_endian);
	txld->w_wall = mlx_xpm_file_to_image(game->mlx, txinfo->w_wall_path,
			&txinfo->width, &txinfo->height);
	if (!txld->w_wall)
		return (ft_putstr_fd("Error: West wall\n", STDERR_FILENO), -1);
	txld->w_wall_data = mlx_get_data_addr(txld->w_wall, &game->texture_bpp,
			&game->texture_size_line, &game->texture_endian);
	txld->s_wall = mlx_xpm_file_to_image(game->mlx, txinfo->s_wall_path,
			&txinfo->width, &txinfo->height);
	if (!txld->s_wall)
		return (ft_putstr_fd("Error: South wall\n", STDERR_FILENO), -1);
	txld->s_wall_data = mlx_get_data_addr(txld->s_wall, &game->texture_bpp,
			&game->texture_size_line, &game->texture_endian);
	txld->e_wall = mlx_xpm_file_to_image(game->mlx, txinfo->e_wall_path,
			&txinfo->width, &txinfo->height);
	if (!txld->e_wall)
		return (ft_putstr_fd("Error: East wall\n", STDERR_FILENO), -1);
	txld->e_wall_data = mlx_get_data_addr(txld->e_wall, &game->texture_bpp,
			&game->texture_size_line, &game->texture_endian);
	return (0);
}

void	set_minimap_dimensions(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[i])
		i++;
	game->map_height = i * GRID_SIZE;
	game->map_rows = i;
	while (game->map[0][j])
		j++;
	game->map_width = game->map_width * GRID_SIZE;
	game->map_cols = j;
	game->x_start_minimap = (WIN_WIDTH - game->map_width) - 10;
	game->y_start_minimap = (WIN_HEIGHT - game->map_height) - 10;
}

int	initialize_game_struct(t_game *game)
{
	set_minimap_dimensions(game);
	game->mlx = mlx_init();
	game->projected_slice_height = TEXTURE_SIZE * 255;
	if (!game->mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MiniLibX\n", STDERR_FILENO);
		return (-1);
	}
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!game->win)
	{
		ft_putstr_fd("Error: Failed to create window\n", STDERR_FILENO);
		return (-1);
	}
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (load_textures(game, &game->loaded_textures, &game->textures_info) == -1)
	{
		ft_putstr_fd("Error: Failed to load textures\n", STDERR_FILENO);
		return (-1);
	}
	initialize_game_vars(game);
	return (0);
}
