/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:39:26 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/05/27 09:39:34 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

void	free_game_struct(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_window(game->mlx, game->win);
	ft_free_map(game->map);
	mlx_destroy_image(game->mlx, game->loaded_textures.n_wall);
	mlx_destroy_image(game->mlx, game->loaded_textures.w_wall);
	mlx_destroy_image(game->mlx, game->loaded_textures.s_wall);
	mlx_destroy_image(game->mlx, game->loaded_textures.e_wall);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == XK_w)
		game->key_w = 1;
	else if (keysym == XK_a)
		game->key_a = 1;
	else if (keysym == XK_s)
		game->key_s = 1;
	else if (keysym == XK_d)
		game->key_d = 1;
	else if (keysym == XK_Left)
		game->key_left = 1;
	else if (keysym == XK_Right)
		game->key_right = 1;
	else if (keysym == XK_Escape)
	{
		free_game_struct(game);
		exit(0);
	}
	return (0);
}

int	handle_keyrelease(int keysym, t_game *game)
{
	if (keysym == XK_w)
		game->key_w = 0;
	else if (keysym == XK_a)
		game->key_a = 0;
	else if (keysym == XK_s)
		game->key_s = 0;
	else if (keysym == XK_d)
		game->key_d = 0;
	else if (keysym == XK_Left)
		game->key_left = 0;
	else if (keysym == XK_Right)
		game->key_right = 0;
	return (0);
}

int	handle_close(t_game *game)
{
	free_game_struct(game);
	exit(0);
}
