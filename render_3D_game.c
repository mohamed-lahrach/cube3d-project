/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3D_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:10:53 by mlahrach          #+#    #+#             */
/*   Updated: 2025/04/09 14:39:25 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_ceiling(t_game *game, t_draw_params params)
{
	int	wall_strip_width;
	int	pixel;
	int	y;

	wall_strip_width = SCREEN_WIDTH / (NUM_RAYS);
	y = params.start_y;
	while (y < params.end_y)
	{
		pixel = (y * game->size_line) + (params.ray_index * wall_strip_width
				* (game->bpp / 8));
		game->img_data[pixel] = params.color & 0xFF;
		game->img_data[pixel + 1] = (params.color >> 8) & 0xFF;
		game->img_data[pixel + 2] = (params.color >> 16) & 0xFF;
		y++;
	}
}

void	initialize_draw_info(t_draw_info *info, t_game *game, int wall_top,
		int ray_index)
{
	info->ray = &game->rays[ray_index];
	info->tex_index = get_texture_index(info->ray);
	info->texture = game->tex_data[info->tex_index];
	info->tex_width = game->tex_width[info->tex_index];
	info->tex_height = game->tex_height[info->tex_index];
	info->wall_strip_width = WALL_STRIP_WIDTH;
	info->tex_x = get_texture_x_coord(info->ray, info->tex_width);
	info->true_wall_height = (int)((TILE_SIZE / (info->ray->distance
					* cos(info->ray->ray_angle - game->player.rotation_angle)))
			* DIST_PROJ_PLANE);
	info->tex_step = (float)info->tex_height / (float)info->true_wall_height;
	info->tex_pos = get_texture_start_position(wall_top, info->true_wall_height,
			info->tex_step);
}

void	draw_wall_strip(t_game *game, int wall_top, int wall_bottom,
		int ray_index)
{
	int			y;
	t_draw_info	info;

	initialize_draw_info(&info, game, wall_top, ray_index);
	y = wall_top;
	while (y < wall_bottom)
	{
		info.tex_y = (int)info.tex_pos & (info.tex_height - 1);
		info.tex_pos += info.tex_step;
		info.color = info.texture[info.tex_y * info.tex_width + info.tex_x];
		info.pixel = (y * game->size_line) + (ray_index * info.wall_strip_width
				* (game->bpp / 8));
		game->img_data[info.pixel] = info.color & 0xFF;
		game->img_data[info.pixel + 1] = (info.color >> 8) & 0xFF;
		game->img_data[info.pixel + 2] = (info.color >> 16) & 0xFF;
		y++;
	}
}

void	draw_floor(t_game *game, t_draw_params params)
{
	int	wall_strip_width;
	int	pixel;
	int	y;

	wall_strip_width = WALL_STRIP_WIDTH;
	y = params.start_y;
	while (y < params.end_y)
	{
		pixel = (y * game->size_line) + (params.ray_index * wall_strip_width
				* (game->bpp / 8));
		game->img_data[pixel] = params.color & 0xFF;
		game->img_data[pixel + 1] = (params.color >> 8) & 0xFF;
		game->img_data[pixel + 2] = (params.color >> 16) & 0xFF;
		y++;
	}
}

void	render_game_in_3d(t_game *game)
{
	t_ray			ray;
	float			correct_distance;

	int (wall_strip_height), (wall_top_pixel), (wall_bottom_pixel), (i);
	i = -1;
	while (++i < NUM_RAYS)
	{
		ray = game->rays[i];
		correct_distance = ray.distance * cos(ray.ray_angle
				- game->player.rotation_angle);
		wall_strip_height = (int)((TILE_SIZE / correct_distance)
				* DIST_PROJ_PLANE);
		wall_top_pixel = (SCREEN_HEIGHT / 2) - (wall_strip_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		wall_bottom_pixel = (SCREEN_HEIGHT / 2) + (wall_strip_height / 2);
		if (wall_bottom_pixel > SCREEN_HEIGHT)
			wall_bottom_pixel = SCREEN_HEIGHT;
		draw_ceiling(game, init_draw_params(0, wall_top_pixel, i,
				game->ceiling_color));
		draw_wall_strip(game, wall_top_pixel, wall_bottom_pixel, i);
		draw_floor(game, init_draw_params(wall_bottom_pixel, SCREEN_HEIGHT, i,
				game->floor_color));
	}
}
