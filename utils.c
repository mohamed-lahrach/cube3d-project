/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:20:10 by mlahrach          #+#    #+#             */
/*   Updated: 2025/03/22 06:24:19 by mlahrach         ###   ########.fr       */
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
                game->player.x = j * game->tile_size.width + game->tile_size.width / 2;
                game->player.y = i * game->tile_size.height + game->tile_size.height / 2;
                
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

int	has_wall_at(float x, float y, t_game *game)
{
	int	map_x;
	int	map_y;
	char **grid = game->map.grid;

	map_x = (int)(x / game->tile_size.width);
	map_y = (int)(y / game->tile_size.height);
	if (map_x < 0 || map_x >= game->rows || map_y < 0 || map_y >= game->columns)
		return (1);
	return (grid[map_y ][map_x] == '1');
}

int	can_move_to(float newX, float newY, t_game *game)
{
	if (has_wall_at(newX + game->player.radius, newY + game->player.radius,
			game))
		return (0);
	if (has_wall_at(newX - game->player.radius, newY + game->player.radius,
			game))
		return (0);
	if (has_wall_at(newX + game->player.radius, newY - game->player.radius,
			game))
		return (0);
	if (has_wall_at(newX - game->player.radius, newY - game->player.radius,
			game))
		return (0);
	return (1);
}
