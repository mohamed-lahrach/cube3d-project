#include "raycasting.h"

void	draw_ceiling(t_game *game, int start_y, int end_y, int ray_index,
		int color)
{
	int	wall_strip_width;
	int	pixel;

	wall_strip_width = game->window_width / (game->window_width / 1);
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

	wall_strip_width = game->window_width / (game->window_width / 1);
	ray = game->rays[ray_index];
	if (ray.was_hit_vertical)
		color = 0xFF0000;
	else
		color = 0x00FF00;
	for (int y = wall_top; y < wall_bottom; y++)
	{
		pixel = (y * game->size_line) + (ray_index * wall_strip_width
				* (game->bpp / 8));
		game->img_data[pixel] = color & 0xFF;
		game->img_data[pixel + 1] = (color >> 8) & 0xFF;
		game->img_data[pixel + 2] = (color >> 16) & 0xFF;
	}
}

void	draw_floor(t_game *game, int start_y, int end_y, int ray_index,
		int color)
{
	int	wall_strip_width;
	int	pixel;

	wall_strip_width = game->window_width / (game->window_width / 1);
	for (int y = start_y; y < end_y; y++)
	{
		pixel = (y * game->size_line) + (ray_index * wall_strip_width
				* (game->bpp / 8));
		game->img_data[pixel] = color & 0xFF;
		game->img_data[pixel + 1] = (color >> 8) & 0xFF;
		game->img_data[pixel + 2] = (color >> 16) & 0xFF;
	}
}

void	render_game_in_3D(t_game *game)
{
	t_ray	ray;
	float	perp_distance;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		ceiling_color;
	int		floor_color;
	int		i;

	i = 0;
	ceiling_color = 0x87CEEB;
	floor_color = 0x8B4513;
	while (i < game->window_width / 1)
	{
		ray = game->rays[i];
		perp_distance = ray.distance * cos(ray.ray_angle
				- game->player.rotation_angle);
		wall_strip_height = (int)((TILE_SIZE / perp_distance)
				* DIST_PROJ_PLANE);
		wall_top_pixel = (game->window_height / 2) - (wall_strip_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		wall_bottom_pixel = (game->window_height / 2) + (wall_strip_height / 2);
		if (wall_bottom_pixel > game->window_height)
			wall_bottom_pixel = game->window_height;
		draw_ceiling(game, 0, wall_top_pixel, i, ceiling_color);
		draw_wall_strip(game, wall_top_pixel, wall_bottom_pixel, i);
		draw_floor(game, wall_bottom_pixel, game->window_height, i, floor_color);
		i++;
	}
}
