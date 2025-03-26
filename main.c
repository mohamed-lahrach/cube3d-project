/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:39:10 by mlahrach          #+#    #+#             */
/*   Updated: 2025/03/26 05:29:17 by mlahrach         ###   ########.fr       */
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
void    load_textures(t_game *game)
{
    char *texture_files[4] = {
        "textures/30x.xpm",
        "textures/64x.xpm",
        "textures/west_1.xpm",
        "textures/east_1.xpm"
    };
    int i;

    for (i = 0; i < 4; i++)
    {
        game->textures[i] = mlx_xpm_file_to_image(game->mlx, texture_files[i], &game->tex_width[i], &game->tex_height[i]);
        if (!game->textures[i])
        {
            printf("Error: Could not load texture %s\n", texture_files[i]);
            exit(1);
        }
        game->tex_data[i] = (int *)mlx_get_data_addr(game->textures[i], &game->bpp, &game->size_line, &game->endian);
    }
}

void	init_game(t_game *game, t_pos pos)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Raycaster");
	load_textures(game);
	normalize_map(&game->map);
	game->rows = get_num_rows(game->map.grid);
	game->columns = get_num_columns(game->map.grid);
	game->player = (t_player){.radius = 3, .move_speed = 1.6,
		.rotation_angle = M_PI / 2, .turn_direction = 0, .walk_direction = 0,
		.strafe_direction = 0, .rotation_speed = 0.4 * (M_PI / 180), .x = pos.x,
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
	render_game_in_3d(game);
	//render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
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

	if (!(parse_the_file(av[1], &components)))
		return (-1);
	game.components = &components;
	game.floor_color = get_color(components.floor_color);
	game.ceiling_color = get_color(components.ceiling_color);
	game.map.grid = list_to_array(components.map,
			get_max_string_length(components.map));
	print_components(&components);
	determine_player_pos(&pos, game.map.grid);
	init_game(&game, pos);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, NULL);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free_comps(&components);
	return (0);
}
