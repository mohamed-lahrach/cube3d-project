/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_2Dmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 01:10:53 by mlahrach          #+#    #+#             */
/*   Updated: 2025/03/23 00:28:08 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_rays(t_game *game, float factor)
{
	for (int i = 0; i < NUM_RAYS; i++)
	{
		draw_line(game->img_data, factor * game->player.x, factor
			* game->player.y, factor * game->rays[i].wall_hit_x, factor
			* game->rays[i].wall_hit_y, RED_COLOR, game->size_line, game->bpp,
			0.3);
	}
}
void	draw_square(char *img_data, int x, int y, int mini_map_tile_with, int mini_map_tile_height, int color,
		int size_line, int bpp)
{
	int	pixel;

	int i = 0;
	while(i < mini_map_tile_height)
	{
		int j = 0;
		while(j < mini_map_tile_with)
		{
			pixel = (y + i) * size_line + (x + j) * (bpp / 8);
			img_data[pixel] = color & 0xFF;             // Blue
			img_data[pixel + 1] = (color >> 8) & 0xFF;  // Green
			img_data[pixel + 2] = (color >> 16) & 0xFF; // Red
			j++;
		}
		i++;
	}
}

void	draw_line(char *img_data, int x0, int y0, int x1, int y1, int color,
		int size_line, int bpp, float alpha)
{
	double			deltaX;
	double			deltaY;
	int				steps;
	double			xIncrement;
	double			yIncrement;
	double			x;
	double			y;
	int				pixel;
	unsigned char	bg_b;
	unsigned char	bg_g;
	unsigned char	bg_r;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	new_r;
	unsigned char	new_g;
	unsigned char	new_b;

	deltaX = x1 - x0;
	deltaY = y1 - y0;
	steps = fabs(deltaX) > fabs(deltaY) ? fabs(deltaX) : fabs(deltaY);
	xIncrement = deltaX / steps;
	yIncrement = deltaY / steps;
	x = x0;
	y = y0;
	for (int i = 0; i <= steps; i++)
	{
		pixel = (int)y * size_line + (int)x * (bpp / 8);
		bg_b = img_data[pixel];
		bg_g = img_data[pixel + 1];
		bg_r = img_data[pixel + 2];
		r = (color >> 16) & 0xFF;
		g = (color >> 8) & 0xFF;
		b = color & 0xFF;
		new_r = (unsigned char)((r * alpha) + (bg_r * (1 - alpha)));
		new_g = (unsigned char)((g * alpha) + (bg_g * (1 - alpha)));
		new_b = (unsigned char)((b * alpha) + (bg_b * (1 - alpha)));
		img_data[pixel] = new_b;
		img_data[pixel + 1] = new_g;
		img_data[pixel + 2] = new_r;
		x += xIncrement;
		y += yIncrement;
	}
}

void	draw_circle(char *img_data, int x0, int y0, int radius, int color,
		int size_line, int bpp)
{
	int	pixel;

	for (int y = -radius; y <= radius; y++)
	{
		for (int x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
			{
				pixel = (y0 + y) * size_line + (x0 + x) * (bpp / 8);
				img_data[pixel] = color & 0xFF;
				img_data[pixel + 1] = (color >> 8) & 0xFF;
				img_data[pixel + 2] = (color >> 16) & 0xFF;
			}
		}
	}
}

void	render_player(t_game *game)
{
	draw_circle(game->img_data, game->player.x, game->player.y,
		game->player.radius, RED_COLOR, game->size_line, game->bpp);
}

void	render_minimap(t_game *game)
{
	int minimap_width = (int)(game->tile_size.width * game->rows
			* MINIMAP_SCALE_FACTOR);
	int minimap_height = (int)(game->tile_size.height * game->columns
			* MINIMAP_SCALE_FACTOR);
	int minimap_tile_size_with = (int)(game->tile_size.width * MINIMAP_SCALE_FACTOR);
	int minimap_tile_size_height = (int)(game->tile_size.height * MINIMAP_SCALE_FACTOR);
	for (int i = 0; i < game->columns; i++)
	{
		for (int j = 0; j < game->rows; j++)
		{
			int minimap_x = j * minimap_tile_size_with;
			int minimap_y = i * minimap_tile_size_height;
			int color = (game->map.grid[i][j] == '1') ? GRAY_COLOR : BLACK_COLOR;
			draw_square(game->img_data, minimap_x, minimap_y, minimap_tile_size_with,minimap_tile_size_height,
				color, game->size_line, game->bpp);
		}
	}
	int player_minimap_x = (int)(game->player.x * MINIMAP_SCALE_FACTOR);
	int player_minimap_y = (int)(game->player.y * MINIMAP_SCALE_FACTOR);
	draw_circle(game->img_data, player_minimap_x, player_minimap_y,
		game->player.radius, RED_COLOR, game->size_line, game->bpp);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		if (i == NUM_RAYS / 2)
		{
			int ray_start_x = player_minimap_x;
			int ray_start_y = player_minimap_y;
			int ray_end_x = (int)(game->rays[i].wall_hit_x
					* MINIMAP_SCALE_FACTOR);
			int ray_end_y = (int)(game->rays[i].wall_hit_y
					* MINIMAP_SCALE_FACTOR);
			draw_line(game->img_data, ray_start_x, ray_start_y, ray_end_x,
				ray_end_y, RED_COLOR, game->size_line, game->bpp, 1);
		}
	}
}
