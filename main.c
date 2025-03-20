/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:39:10 by mlahrach          #+#    #+#             */
/*   Updated: 2025/03/20 01:00:48 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

char initial_map[MAP_HEIGHT][MAP_WIDTH] = {{'1', '1', '1', '1', '1', '1',
											'1', '1', '1', '1', '1', '1', '1', '1', '1'},
										   {'1', '0', '0', '0', '0',
											'0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
										   {'1', '0', '0', '1',
											'0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
										   {'1', '1', '1',
											'0', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1'},
										   {'1', '0',
											'0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '1', '0', '1'},
										   {'1',
											'0', '1', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '0', '1'},
										   {'1', '0', '0', 'P', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
											'1'},
										   {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
											'0', '1'},
										   {'1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1',
											'1', '0', '1'},
										   {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
											'0', '0', '0', '1'},
										   {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
											'1', '1', '1', '1', '1'}};

void update_player(t_game *game)
{
	float move_step;
	float strafe_step;
	float new_player_x;
	float new_player_y;

	move_step = game->player.walk_direction * game->player.move_speed;
	strafe_step = game->player.strafe_direction * game->player.move_speed;
	new_player_x = game->player.x + cos(game->player.rotation_angle) * move_step - sin(game->player.rotation_angle) * strafe_step;
	new_player_y = game->player.y + sin(game->player.rotation_angle) * move_step + cos(game->player.rotation_angle) * strafe_step;
	if (can_move_to(new_player_x, new_player_y, game))
	{
		game->player.x = new_player_x;
		game->player.y = new_player_y;
	}
	game->player.rotation_angle += game->player.turn_direction * game->player.rotation_speed;
	game->player.rotation_angle = fmod(game->player.rotation_angle, 2 * M_PI);
}

void init_game(t_game *game, t_pos *pos)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
							   "Raycaster");
	game->player = (t_player){.radius = 3
		, .move_speed = 1,
		 .rotation_angle = M_PI / 2,
		 .turn_direction = 0,
		 .walk_direction = 0,
		 .strafe_direction = 0, 
		 .rotation_speed = 0.4 * (M_PI / 180),
		 .x = pos->x,
		 .y = pos->y
		};
	//initialize_player_position(game, game->map.grid);
	//initialize_map_grid(game, game->map.grid);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
									   &game->endian);
}

int game_loop(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	update_player(game);
	cast_all_rays(game);
	//show_data_of_rays(game);
	render_game_in_3D(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int main(int ac, char **av)
{
	t_game game;
	t_pos *pos;
	//t_game			game;
	t_components	components;

	// if (ac != 3)
	// {
	// 	ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
	// 	return (-1);
	// }
	if (!(parse_the_file(av[1], &components)))
		return (-1);
	game.components = &components;
	game.floor_color = get_color(components.floor_color);
	game.ceiling_color = get_color(components.ceiling_color);
	game.map.grid = list_to_array(components.map,
			get_max_string_length(components.map));
	print_components(&components);
	determine_player_pos(pos, game.map.grid);
	printf("x: %f, y: %f\n", pos->x, pos->y);
	// init_game(&game, pos);
	// mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	// mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	// mlx_hook(game.win, 17, 0, close_window, NULL);
	// mlx_loop_hook(game.mlx, game_loop, &game);
	// mlx_loop(game.mlx);
	free_comps(&components);
	return (0);
}
