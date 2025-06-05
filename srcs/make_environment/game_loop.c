/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:14:28 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/05/20 13:23:02 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"
	// if (new_x < 0 || new_x >= game->map_cols
	// 	|| new_y < 0 || new_y >= game->map_rows)
int	is_valid_position(t_game *game, double new_x, double new_y)
{
	int	tile_x;
	int	tile_y;

	tile_x = (int)new_x;
	tile_y = (int)new_y;
	if (new_x < 0 || new_x >= game->map_width
		|| new_y < 0 || new_y >= game->map_height)
		return (0);
	if (game->map[tile_y][tile_x] != '0')
		return (0);
	return (1);
}

void	update_move(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->pos_x + move_x;
	new_y = game->pos_y + move_y;
	if (move_x != 0 || move_y != 0)
	{
		if (is_valid_position(game, new_x, new_y))
		{
			game->pos_x = new_x;
			game->pos_y = new_y;
		}
		else
		{
			new_x = game->pos_x + move_x;
			new_y = game->pos_y;
			if (is_valid_position(game, new_x, new_y))
				game->pos_x = new_x;
			new_x = game->pos_x;
			new_y = game->pos_y + move_y;
			if (is_valid_position(game, new_x, new_y))
				game->pos_y = new_y;
		}
	}
}

long long	get_current_time_ms(void)
{
	struct timeval	tv;
	long long		cur_time;

	gettimeofday(&tv, NULL);
	cur_time = (long long)(tv.tv_sec) *1000 + (long long)(tv.tv_usec) / 1000;
	return (cur_time);
}

double	get_delta_time(void)
{
	static long long	last_time = 0;
	long long			current_time;
	double				delta_time;

	current_time = get_current_time_ms();
	if (last_time == 0)
		last_time = current_time;
	delta_time = (current_time - last_time) / 1000.0;
	last_time = current_time;
	return (delta_time);
}
