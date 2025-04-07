/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3D_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:10:53 by mlahrach          #+#    #+#             */
/*   Updated: 2025/04/07 15:53:38 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_ceiling(t_game *game, int start_y, int end_y, int ray_index,
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

int	get_wall_color(t_ray ray)
{
	if (ray.was_hit_vertical)
	{
		if (ray.is_facing_left)
			return (0xFF0000);
		else
			return (0x8B4513);
	}
	else
	{
		if (ray.is_facing_up)
			return (0x00FF00);
		else
			return (0xFFFF00);
	}
}
int get_texture_index(t_ray *ray)
{
    if (ray->was_hit_vertical)
        return (ray->is_facing_left ? 2 : 3); // 2 = West, 3 = East
    else
        return (ray->is_facing_up ? 0 : 1);   // 0 = North, 1 = South
}

void    draw_wall_strip(t_game *game, int wall_top, int wall_bottom, int ray_index)
{
    int     y;
    int     tex_x, tex_y;
    float   tex_step;
    float   tex_pos;
    t_ray   *ray;
    int     tex_index;
    int     *texture;
    int     tex_width;
    int     tex_height;
    int     wall_strip_width;
    int     true_wall_height;
    int     color;
    int     pixel;
    
    ray = &game->rays[ray_index];
    tex_index = get_texture_index(ray);
    texture = game->tex_data[tex_index];
    tex_width = game->tex_width[tex_index];
    tex_height = game->tex_height[tex_index];
    wall_strip_width = WALL_STRIP_WIDTH;

    // Get correct texture X coordinate based on hit position
    if (ray->was_hit_vertical)
    {
        tex_x = (int)ray->wall_hit_y % TILE_SIZE;
        if (ray->is_facing_left)
            tex_x = tex_width - tex_x - 1;
    }
    else
    {
        tex_x = (int)ray->wall_hit_x % TILE_SIZE;
        if (ray->is_facing_up)
            tex_x = tex_width - tex_x - 1;
    }
    
    // Calculate the true height of the wall before any clipping
    true_wall_height = (int)((TILE_SIZE / (ray->distance * cos(ray->ray_angle - game->player.rotation_angle))) * DIST_PROJ_PLANE);
    
    // Calculate texture step based on true wall height
    tex_step = (float)tex_height / (float)true_wall_height;
    
    // Calculate the starting position in the texture
    // This accounts for walls that are partially off-screen at the top
    tex_pos = 0;
    if (wall_top <= 0)
    {
        // If wall extends above screen, calculate texture offset
        int screen_center = SCREEN_HEIGHT / 2;
        int half_wall_height = true_wall_height / 2;
        int offset = screen_center - half_wall_height;
        
        // If offset is negative, wall extends above screen
        if (offset < 0)
            tex_pos = abs(offset) * tex_step;
    }

    y = wall_top;
    while (y < wall_bottom)
    {
        tex_y = (int)tex_pos & (tex_height - 1); // Keep within texture bounds
        tex_pos += tex_step;

        color = texture[tex_y * tex_width + tex_x];
        pixel = (y * game->size_line) + (ray_index * wall_strip_width * (game->bpp / 8));

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

	wall_strip_width = WALL_STRIP_WIDTH;
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

void render_game_in_3d(t_game *game)
{
    t_ray ray;
    float correct_distance;
    int wall_strip_height;
    int wall_top_pixel;
    int wall_bottom_pixel;
    
    for (int i = 0; i < NUM_RAYS; i++)
    {
        ray = game->rays[i];
        correct_distance = ray.distance * cos(ray.ray_angle - game->player.rotation_angle);
        wall_strip_height = (int)((TILE_SIZE / correct_distance) * DIST_PROJ_PLANE);
        wall_top_pixel = (SCREEN_HEIGHT / 2) - (wall_strip_height / 2);
        if (wall_top_pixel < 0)
            wall_top_pixel = 0;
        wall_bottom_pixel = (SCREEN_HEIGHT / 2) + (wall_strip_height / 2);
        if (wall_bottom_pixel > SCREEN_HEIGHT)
            wall_bottom_pixel = SCREEN_HEIGHT;
        draw_ceiling(game, 0, wall_top_pixel, i, game->ceiling_color);
        draw_wall_strip(game, wall_top_pixel, wall_bottom_pixel, i);
        draw_floor(game, wall_bottom_pixel, SCREEN_HEIGHT, i, game->floor_color);
    }
}
