/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:39:10 by mlahrach          #+#    #+#             */
/*   Updated: 2025/03/22 23:59:48 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	update_player(t_game *game)
{
	float	move_step;
	float	strafe_step;
	float	new_player_x;
	float	new_player_y;

	move_step = game->player.walk_direction * game->player.move_speed;
	strafe_step = game->player.strafe_direction * game->player.move_speed;
	new_player_x = game->player.x + cos(game->player.rotation_angle) * move_step
		- sin(game->player.rotation_angle) * strafe_step;
	new_player_y = game->player.y + sin(game->player.rotation_angle) * move_step
		+ cos(game->player.rotation_angle) * strafe_step;
	if (can_move_to(new_player_x, new_player_y, game))
	{
		game->player.x = new_player_x;
		game->player.y = new_player_y;
	}
	game->player.rotation_angle += game->player.turn_direction
		* game->player.rotation_speed;
	game->player.rotation_angle = fmod(game->player.rotation_angle, 2 * M_PI);
}

void	init_game(t_game *game, t_pos pos)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Raycaster");
	game->player = (t_player){.radius = 3, .move_speed = .5,
		.rotation_angle = M_PI / 2, .turn_direction = 0, .walk_direction = 0,
		.strafe_direction = 0, .rotation_speed = 0.2 * (M_PI / 180), .x = pos.x,
		.y = pos.y};
	initialize_player_position(game, &game->map);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
}

int	game_loop(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	update_player(game);
	cast_all_rays(game);
	render_game_in_3D(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
// Function to count the number of rows in the grid
int	get_num_columns(char **grid)
{
	int	num_rows;

	num_rows = 0;
	while (grid[num_rows] != NULL)
		num_rows++;
	return (num_rows);
}

int	get_num_rows(char **grid)
{
	int	max_len;
	int	i;
	int	len;

	max_len = 0;
	i = 0;
	while (grid[i])
	{
		len = ft_strlen(grid[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}
void	normalize_map(t_map *map)
{
	int		i;
	int		longest_len;
	int		j;
	char	*new_line;

	i = 0;
	longest_len = get_num_rows(map->grid);
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == ' ')
				map->grid[i][j] = '1';
			j++;
		}
		new_line = malloc(sizeof(char) * (longest_len + 1));
		if (!new_line)
			return ;
		j = 0;
		while (map->grid[i][j])
		{
			new_line[j] = map->grid[i][j];
			j++;
		}
		while (j < longest_len)
		{
			new_line[j] = '1';
			j++;
		}
		new_line[j] = '\0';
		free(map->grid[i]);
		map->grid[i] = new_line;
		i++;
	}
}

void	print_grid(char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j] != '\0')
		{
			printf("%c", grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int ac, char **av)
{
	t_game			game;
	t_pos			pos;
	t_components	components;

	/*
		parsing stuff
	*/
	if (!(parse_the_file(av[1], &components)))
		return (-1);
	game.components = &components;
	game.floor_color = get_color(components.floor_color);
	game.ceiling_color = get_color(components.ceiling_color);
	printf("floor color: %d\n", game.floor_color);
	printf("ceiling color: %d\n", game.ceiling_color);
	game.map.grid = list_to_array(components.map,
			get_max_string_length(components.map));
	print_components(&components);
	/*
		ray casting stuff
	*/
	determine_player_pos(&pos, game.map.grid);
	print_grid(game.map.grid);
	printf("\n");
	normalize_map(&game.map);
	print_grid(game.map.grid);
	game.rows = get_num_rows(game.map.grid);
	game.columns = get_num_columns(game.map.grid);
	game.tile_size.width = SCREEN_WIDTH / game.rows;
	game.tile_size.height = SCREEN_HEIGHT / game.columns;
	printf("pos x: %f, pos y: %f\n", pos.x, pos.y);
	printf("window width: %d * %d = %d\n", game.tile_size.width, game.rows,
		game.tile_size.width * game.rows);
	printf("window height: %d * %d = %d\n", game.tile_size.height, game.columns,
		game.tile_size.height * game.columns);
	printf("++++++++++++++++++++++++++++++\n");
	printf("number of rows: %d\n", game.rows);
	printf("number of colums: %d\n", game.columns);
	printf("++++++++++++++++++++++++++++++\n");
	printf("tile width: %d\n", game.tile_size.width);
	printf("tile height: %d\n", game.tile_size.height);
	init_game(&game, pos);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, NULL);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free_comps(&components);
	return (0);
}
