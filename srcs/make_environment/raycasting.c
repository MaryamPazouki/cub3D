/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:28:55 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/05/20 14:58:22 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

void	init_ray_deltas(t_ray_params *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

void	init_ray_params(t_game *game, double dir_angle, t_ray_params *ray)
{
	ray->dir_x = cos(dir_angle);
	ray->dir_y = sin(dir_angle);
	init_ray_deltas(ray);
	if (ray->dir_x > 0)
		ray->step_x = 1;
	else
		ray->step_x = -1;
	if (ray->dir_y > 0)
		ray->step_y = 1;
	else
		ray->step_y = -1;
	if (ray->dir_x >= 0)
		ray->next_x = ceil(game->pos_x);
	else
		ray->next_x = floor(game->pos_x);
	if (ray->dir_y >= 0)
		ray->next_y = ceil(game->pos_y);
	else
		ray->next_y = floor(game->pos_y);
}

void	init_ray_side_distances(t_game *game, t_ray_params *ray)
{
	ray->dist_to_x_wall = 0;
	ray->dist_to_y_wall = 0;
	if (ray->dir_x > 0)
		ray->dist_to_x_wall = (ray->next_x - game->pos_x) * ray->delta_dist_x;
	else if (ray->dir_x < 0)
		ray->dist_to_x_wall = (game->pos_x - ray->next_x) * ray->delta_dist_x;
	else
		ray->dist_to_x_wall = 1e30;
	if (ray->dir_y > 0)
		ray->dist_to_y_wall = (ray->next_y - game->pos_y) * ray->delta_dist_y;
	else if (ray->dir_y < 0)
		ray->dist_to_y_wall = (game->pos_y - ray->next_y) * ray->delta_dist_y;
	else
		ray->dist_to_y_wall = 1e30;
}

int	perform_dda_loop(t_game *game, t_ray_params *ray)
{
	while (1)
	{
		if (ray->dist_to_x_wall < ray->dist_to_y_wall)
		{
			ray->map_x += ray->step_x;
			game->side = 0;
			if (game->map[ray->map_y][ray->map_x] != '1')
				ray->dist_to_x_wall += ray->delta_dist_x;
		}
		else
		{
			ray->map_y += ray->step_y;
			game->side = 1;
			if (game->map[ray->map_y][ray->map_x] != '1')
				ray->dist_to_y_wall += ray->delta_dist_y;
		}
		if (ray->map_y >= 0 && ray->map_y < game->map_rows && ray->map_x >= 0
			&& ray->map_x < game->map_cols)
		{
			if (game->map[ray->map_y][ray->map_x] == '1')
				return (0);
		}
		else
			return (ft_putstr_fd("Error: Ray", STDERR_FILENO), -1);
	}
}

int	cast_rays(t_game *game, double dir_angle, double *distance_to_wall)
{
	t_ray_params	ray;

	init_ray_params(game, dir_angle, &ray);
	init_ray_side_distances(game, &ray);
	ray.map_x = (int)game->pos_x;
	ray.map_y = (int)game->pos_y;
	if (perform_dda_loop(game, &ray) < 0)
		return (-1);
	*distance_to_wall = fmin(ray.dist_to_x_wall, ray.dist_to_y_wall);
	return (0);
}
