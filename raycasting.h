/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:38:59 by mlahrach          #+#    #+#             */
/*   Updated: 2025/04/06 20:52:09 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "inc/cub3d.h"
# include "inc/parsing.h"
# include "minilibx-linux/mlx.h"
# include <float.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

#define TILE_SIZE 64
# define MIN(a, b) ((a) < (b) ? (a) : (b))
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
# define FOV_ANGLE (60 * (M_PI / 180))
# define WALL_STRIP_WIDTH 1
# define NUM_RAYS (SCREEN_WIDTH / WALL_STRIP_WIDTH)
# define DIST_PROJ_PLANE ((SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2))
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

	void    *textures[4]; // 0: North, 1: South, 2: West, 3: East
    int     *tex_data[4]; // Pixel data for each texture
    int     tex_width[4];
    int     tex_height[4];
}						t_game;

int						close_window(void *param);
void					draw_square(char *img_data, int x, int y,
							int mini_map_tile_with, int mini_map_tile_height,
							int color, int size_line, int bpp);
void					draw_line(char *img_data, int x0, int y0, int x1,
							int y1, int color, int size_line, int bpp,
							float alpha);
void					draw_circle(char *img_data, int x0, int y0, int radius,
							int color, int size_line, int bpp);
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
#endif