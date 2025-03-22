/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3D_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:10:53 by mlahrach          #+#    #+#             */
/*   Updated: 2025/03/22 20:10:54 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_ceiling(t_game *game, int start_y, int end_y, int ray_index,
		int color)
{
	int	wall_strip_width;
	int	pixel;

	wall_strip_width = SCREEN_WIDTH / (NUM_RAYS);
	for (int y = start_y; y < end_y; y++)
	{
		pixel = (y * game->size_line) + (ray_index * wall_strip_width
				* (game->bpp / 8));
		game->img_data[pixel] = color & 0xFF;
		game->img_data[pixel + 1] = (color >> 8) & 0xFF;
		game->img_data[pixel + 2] = (color >> 16) & 0xFF;
	}
}

void	draw_wall_strip(t_game *game, int wall_top, int wall_bottom,
		int ray_index)
{
	int		wall_strip_width;
	t_ray	ray;
	int		color;
	int		pixel;
	int		y;

	wall_strip_width = SCREEN_WIDTH / (NUM_RAYS);
	ray = game->rays[ray_index];
	if (ray.was_hit_vertical)
		color = 0xFF0000;
	else
		color = 0x00FF00;
	y = wall_top;
	while (y < wall_bottom)
	{
		pixel = (y * game->size_line) + (ray_index * wall_strip_width
				* (game->bpp / 8));
		game->img_data[pixel] = color & 0xFF;
		game->img_data[pixel + 1] = (color >> 8) & 0xFF;
		game->img_data[pixel + 2] = (color >> 16) & 0xFF;
		y++;
	}
}

void	draw_floor(t_game *game, int start_y, int end_y, int ray_index,
		int color)
{
	int	wall_strip_width;
	int	pixel;
	int	y;

	wall_strip_width = SCREEN_WIDTH / (NUM_RAYS);
	y = start_y;
	while (y < end_y)
	{
		pixel = (y * game->size_line) + (ray_index * wall_strip_width
				* (game->bpp / 8));
		game->img_data[pixel] = color & 0xFF;
		game->img_data[pixel + 1] = (color >> 8) & 0xFF;
		game->img_data[pixel + 2] = (color >> 16) & 0xFF;
		y++;
	}
}

void	render_game_in_3D(t_game *game)
{
	t_ray	ray;
	float	perp_distance;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		i;

	i = -1;
	while (++i < NUM_RAYS)
	{
		ray = game->rays[i];
		perp_distance = ray.distance * cos(ray.ray_angle
				- game->player.rotation_angle);
		wall_strip_height = (int)((MIN(game->tile_size.height,
						game->tile_size.width) / perp_distance)
				* DIST_PROJ_PLANE);
		wall_top_pixel = (SCREEN_HEIGHT / 2) - (wall_strip_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		wall_bottom_pixel = (SCREEN_HEIGHT / 2) + (wall_strip_height / 2);
		if (wall_bottom_pixel > SCREEN_HEIGHT)
			wall_bottom_pixel = SCREEN_HEIGHT;
		draw_ceiling(game, 0, wall_top_pixel, i, game->ceiling_color);
		draw_wall_strip(game, wall_top_pixel, wall_bottom_pixel, i);
		draw_floor(game, wall_bottom_pixel, SCREEN_HEIGHT, i,
			game->floor_color);
	}
}
