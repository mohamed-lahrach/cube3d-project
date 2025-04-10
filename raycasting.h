/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:38:59 by mlahrach          #+#    #+#             */
/*   Updated: 2025/04/10 16:56:13 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "./inc/cub3d.h"
# include "./inc/parsing.h"
# include "/usr/local/include/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define LARGE_FLOAT 1e30
# define TILE_SIZE 64
# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 800
# define GRAY_COLOR 0xCCCCCC
# define BLACK_COLOR 0x000000
# define RED_COLOR 0xFF0000
# define YELLOW_COLOR 0xFFFF00
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define M_PI 3.14159265358979323846
# define WALL_STRIP_WIDTH 1
# define FOV_ANGLE 1.0471975512  /* 60 degrees in radians (pre-calculated) */
/* Pre-calculated: SCREEN_WIDTH / WALL_STRIP_WIDTH */
# define NUM_RAYS 1200
/* Pre-calculated: (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2) */
# define DIST_PROJ_PLANE 1040
# define MINIMAP_SCALE_FACTOR 0.3
# define HORIZONTAL 0
# define VERTICAL 1

typedef struct s_player
{
	float				x;
	float				y;
	float				radius;
	int					turn_direction;
	int					walk_direction;
	int					strafe_direction;
	float				rotation_angle;
	float				move_speed;
	float				rotation_speed;
}						t_player;

typedef struct s_ray
{
	float				ray_angle;
	float				wall_hit_x;
	float				wall_hit_y;
	float				distance;
	int					was_hit_vertical;
	int					is_facing_down;
	int					is_facing_up;
	int					is_facing_right;
	int					is_facing_left;
}						t_ray;
typedef struct s_intercept_data
{
	int					found_wall;
	float				hit_x;
	float				hit_y;
	float				yintercept;
	float				xintercept;
	float				ystep;
	float				xstep;
	float				next_touch_x;
	float				next_touch_y;
	int					subtract_one;
}						t_intercept_data;
typedef struct s_tile_size
{
	int					width;
	int					height;
}						t_tile_size;

// texture data
typedef struct s_draw_info
{
	int					tex_x;
	int					tex_y;
	float				tex_step;
	float				tex_pos;
	t_ray				*ray;
	int					tex_index;
	int					*texture;
	int					tex_width;
	int					tex_height;
	int					wall_strip_width;
	int					true_wall_height;
	int					color;
	int					pixel;
}						t_draw_info;

typedef struct s_draw_params
{
	int					start_y;
	int					end_y;
	int					ray_index;
	int					color;
}						t_draw_params;
typedef struct s_game
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*img_data;
	int					bpp;
	int					size_line;
	int					endian;
	t_intercept_data	vert_intercept_data;
	t_intercept_data	horz_intercept_data;
	t_tile_size			tile_size;
	int					columns;
	int					rows;
	t_map				map;
	t_player			player;
	t_pos				pos;
	t_ray				rays[NUM_RAYS];
	t_components		*components;
	int					ceiling_color;
	int					floor_color;

	void				*textures[4];
	int					*tex_data[4];
	int					tex_width[4];
	int					tex_height[4];
}						t_game;

int						close_window(void *param);
void					render_player(t_game *game);
int						key_press(int keycode, t_game *game);
int						key_release(int keycode, t_game *game);
int						has_wall_at(float x, float y, t_game *game);
float					normalize_angle(float angle);
void					update_player(t_game *game);
int						can_move_to(float newX, float newY, t_game *game);
t_ray					cast_ray(t_game *game, float ray_angle);
void					cast_all_rays(t_game *game);
void					draw_rays(t_game *game, float factor);
void					render_game_in_3d(t_game *game);
int						game_loop(t_game *game);
void					init_game(t_game *game, t_pos pos);
void					render_minimap(t_game *game);
void					show_data_of_rays(t_game *game);
void					initialize_player_position(t_game *game, t_map *map);
void					calculate_check_coordinates(int direction,
							t_intercept_data *data, float *check_x,
							float *check_y);
void					set_ray_directions(t_ray *ray);
void					select_closest_hit(t_ray *ray, t_game *game,
							double vert_distance, double horz_distance);
float					get_distance(t_intercept_data intercept_data,
							t_game *game);
void					normalize_map(t_map *map);
int						get_num_rows(char **grid);
int						get_num_columns(char **grid);
int						get_wall_color(t_ray ray);
int						get_texture_index(t_ray *ray);
int						get_texture_x_coord(t_ray *ray, int tex_width);
float					get_texture_start_position(int wall_top,
							int true_wall_height, float tex_step);
t_draw_params			init_draw_params(int start_y, int end_y, int ray_index,
							int color);
void					free_loaded_textures(t_game *game);
void					free_map_grid(char **grid);
#endif