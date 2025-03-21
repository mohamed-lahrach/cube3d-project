/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:20:10 by mlahrach          #+#    #+#             */
/*   Updated: 2025/03/21 19:36:54 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void initialize_player_position(t_game *game, t_map *map)
{
    int i = 0;
    
    while (map->grid[i])
    {
        int j = 0;
        while (map->grid[i][j])
        {
            if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S' ||
                map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
            {
                // Set player position
                game->player.x = j * TILE_SIZE + TILE_SIZE / 2;
                game->player.y = i * TILE_SIZE + TILE_SIZE / 2;
                
                // Set player direction based on character
                if (map->grid[i][j] == 'N')
                    game->player.rotation_angle = 270; // North (in degrees)
                else if (map->grid[i][j] == 'S')
                    game->player.rotation_angle = 90;  // South
                else if (map->grid[i][j] == 'E')
                    game->player.rotation_angle = 0;   // East
                else if (map->grid[i][j] == 'W')
                    game->player.rotation_angle = 180; // West
                
                // Replace player character with empty space
                map->grid[i][j] = '0';
                return;
            }
            j++;
        }
        i++;
    }
}

void	initialize_map_grid(t_game *game,
		char initial_map[MAP_HEIGHT][MAP_WIDTH])
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			game->map.grid[i][j] = initial_map[i][j];
			j++;
		}
		i++;
	}
}

int	has_wall_at(float x, float y, t_map *map)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
		return (1);
	return (map->grid[map_y ][map_x] == '1');
}

int	can_move_to(float newX, float newY, t_game *game)
{
	if (has_wall_at(newX + game->player.radius, newY + game->player.radius,
			&game->map))
		return (0);
	if (has_wall_at(newX - game->player.radius, newY + game->player.radius,
			&game->map))
		return (0);
	if (has_wall_at(newX + game->player.radius, newY - game->player.radius,
			&game->map))
		return (0);
	if (has_wall_at(newX - game->player.radius, newY - game->player.radius,
			&game->map))
		return (0);
	return (1);
}
