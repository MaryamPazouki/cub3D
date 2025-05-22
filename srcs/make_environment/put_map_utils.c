/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:25:35 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/05/20 13:59:16 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

void	clear_screen(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	pixel;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		pixel = (y * game->size_line) + (x * (game->bpp / 8));
		*(unsigned int *)(game->img_data + pixel) = color;
	}
}

void	print_ceiling_floor(t_game *game)
{
	int	i;
	int	j;
	int	half_height;

	i = 0;
	half_height = WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			if (i > half_height)
				put_pixel(game, j, i, game->textures_info.floor_color);
			else
				put_pixel(game, j, i, game->textures_info.ceiling_color);
			j++;
		}
		i++;
	}
}

double	calculate_wall_x(t_game *game, double ray_angle)
{
	double	wall_x;

	if (game->side == 0)
		wall_x = game->pos_y + game->true_ray_dist * sin(ray_angle);
	else
		wall_x = game->pos_x + game->true_ray_dist * cos(ray_angle);
	return (wall_x - floor(wall_x));
}

char	*return_texture_type(t_game *game, double ray_angle)
{
	if (ray_angle > 2 * M_PI)
		ray_angle -= 2 * M_PI;
	else if (ray_angle < 0)
		ray_angle += 2 * M_PI;
	if (game->side == 0)
	{
		if (ray_angle > M_PI / 2 && ray_angle < (3 * M_PI) / 2)
			return (game->loaded_textures.w_wall_data);
		else
			return (game->loaded_textures.e_wall_data);
	}
	else
	{
		if (ray_angle > 0 && ray_angle < M_PI)
			return (game->loaded_textures.s_wall_data);
		else
			return (game->loaded_textures.n_wall_data);
	}
}
