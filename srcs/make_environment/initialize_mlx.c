/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:10:50 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/05/20 13:12:40 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

void	handle_wasd_movement(t_game *game, double *move_x,
		double *move_y, double delta_time)
{
	double	move_speed;

	move_speed = 0.5;
	if (game->key_w)
	{
		*move_x += game->dir_x * move_speed * delta_time;
		*move_y += game->dir_y * move_speed * delta_time;
	}
	if (game->key_s)
	{
		*move_x -= game->dir_x * move_speed * delta_time;
		*move_y -= game->dir_y * move_speed * delta_time;
	}
	if (game->key_a)
	{
		*move_x += game->dir_y * move_speed * delta_time;
		*move_y -= game->dir_x * move_speed * delta_time;
	}
	if (game->key_d)
	{
		*move_x -= game->dir_y * move_speed * delta_time;
		*move_y += game->dir_x * move_speed * delta_time;
	}
}

void	handle_rotation(t_game *game, double delta_time)
{
	if (game->key_left)
	{
		game->dir_angle -= 1.5 * delta_time;
		game->dir_y = sin(game->dir_angle);
		game->dir_x = cos(game->dir_angle);
	}
	if (game->key_right)
	{
		game->dir_angle += 1.5 * delta_time;
		game->dir_y = sin(game->dir_angle);
		game->dir_x = cos(game->dir_angle);
	}
	if (game->dir_angle > 2 * M_PI)
		game->dir_angle -= 2 * M_PI;
	if (game->dir_angle < 0)
		game->dir_angle += 2 * M_PI;
}

int	handle_movement_and_rotation(t_game *game, double *move_x, double *move_y)
{
	double	delta_time;
	double	length;
	double	move_speed;

	move_speed = 5.0;
	length = 0;
	delta_time = get_delta_time();
	handle_wasd_movement(game, move_x, move_y, delta_time);
	handle_rotation(game, delta_time);
	if ((*move_x != 0 || game->dir_y == 0)
		&& (*move_y != 0 || game->dir_x == 1))
	{
		length = sqrt((*move_x) * (*move_x) + (*move_y) * (*move_y));
		if (length > 0)
		{
			*move_x = *move_x / length * move_speed * delta_time;
			*move_y = *move_y / length * move_speed * delta_time;
		}
	}
	return (0);
}

int	game_loop(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = 0;
	move_y = 0;
	handle_movement_and_rotation(game, &move_x, &move_y);
	update_move(game, move_x, move_y);
	draw_screen(game);
	return (0);
}

int	initialize_mlx_and_launch_game(t_game *game)
{
	if (initialize_game_struct(game) == -1)
		return (-1);
	mlx_hook(game->win, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask,
		&handle_close, game);
	mlx_loop(game->mlx);
	return (0);
}
