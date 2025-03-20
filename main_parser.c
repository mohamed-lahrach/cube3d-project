
#include "inc/cub3d.h"
#include "inc/parsing.h"

void	init_map(t_map *map, int x, int y)
{
	map->size.x = x;
	map->size.y = y;
}



int	main(int ac, char **av)
{
	t_game_parser			game;
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
	free_comps(&components);
}
