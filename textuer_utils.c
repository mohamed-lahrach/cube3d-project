/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textuer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:20:28 by mlahrach          #+#    #+#             */
/*   Updated: 2025/04/10 01:33:38 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

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

int	get_texture_index(t_ray *ray)
{
	if (ray->was_hit_vertical)
	{
		if (ray->is_facing_left)
			return (2);
		else
			return (3);
	}
	else
	{
		if (ray->is_facing_up)
			return (0);
		else
			return (1);
	}
}

int	get_texture_x_coord(t_ray *ray, int tex_width)
{
	int	tex_x;

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
	return (tex_x);
}

float	get_texture_start_position(int wall_top, int true_wall_height,
		float tex_step)
{
	float	tex_pos;
	int		screen_center;
	int		half_wall_height;
	int		offset;

	tex_pos = 0;
	if (wall_top <= 0)
	{
		screen_center = SCREEN_HEIGHT / 2;
		half_wall_height = true_wall_height / 2;
		offset = screen_center - half_wall_height;
		if (offset < 0)
			tex_pos = abs(offset) * tex_step;
	}
	return (tex_pos);
}

t_draw_params	init_draw_params(int start_y, int end_y, int ray_index,
		int color)
{
	t_draw_params	params;

	params.start_y = start_y;
	params.end_y = end_y;
	params.ray_index = ray_index;
	params.color = color;
	return (params);
}
