/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:24:11 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/05/20 15:31:41 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

void	draw_direction_line(t_game *game, int distance,
		double dir_x, double dir_y)
{
	int	i;
	int	ex;
	int	yi;
	int	x;
	int	y;

	i = 0;
	x = (int)(game->pos_x * GRID_SIZE) + game->x_start_minimap;
	y = (int)(game->pos_y * GRID_SIZE) + game->y_start_minimap;
	while (i < distance)
	{
		ex = dir_x * i;
		yi = dir_y * i;
		put_pixel(game, x + ex, y + yi, 0x0000FF00);
		i++;
	}
}

void	cast_fov_rays(t_game *game)
{
	int		i;
	double	angle_init;
	double	one_degree;
	double	distance_to_wall;
	double	ray_angle;

	i = 0;
	angle_init = game->dir_angle - (M_PI / 6);
	one_degree = M_PI / 180;
	distance_to_wall = 0;
	while (i < 60)
	{
		ray_angle = angle_init + (i * one_degree);
		cast_rays(game, ray_angle, &distance_to_wall);
		distance_to_wall = distance_to_wall * cos(ray_angle - game->dir_angle);
		draw_direction_line(game, distance_to_wall * GRID_SIZE,
			cos(ray_angle), sin(ray_angle));
		i++;
	}
}

void	put_grid_boundary_2(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < GRID_SIZE)
	{
		j = 0;
		while (j < GRID_SIZE)
		{
			if (i == 0 || i == GRID_SIZE - 1 || j == 0 || j == GRID_SIZE - 1)
				put_pixel(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	put_map_background_2(t_game *game, int x_offset, int y_offset)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				put_grid_boundary_2(game, x * GRID_SIZE + x_offset,
					y * GRID_SIZE + y_offset, 0x008000FF);
			x++;
		}
		y++;
	}
}

void	put_player_position(t_game *game)
{
	int	square_size;
	int	x;
	int	y;
	int	i;
	int	j;

	square_size = GRID_SIZE >> 2;
	x = game->pos_x * GRID_SIZE - square_size / 2 + game->x_start_minimap;
	y = game->pos_y * GRID_SIZE - square_size / 2 + game->y_start_minimap;
	while (square_size > 0)
	{
		i = 0;
		while (i < square_size)
		{
			j = 0;
			while (j < square_size)
			{
				put_pixel(game, x + j, y + i, 0x00FF0000);
				j++;
			}
			i++;
		}
		square_size--;
	}
}
