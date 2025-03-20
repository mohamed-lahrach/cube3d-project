
#include "../inc/parsing.h"

int	get_max_string_length(t_mapp *head)
{
	int	max_length;
	int	current_length;

	max_length = 0;
	while (head != NULL)
	{
		current_length = ft_strlen(head->line);
		if (current_length > max_length)
			max_length = current_length;
		head = head->next;
	}
	return (max_length);
}

bool	valid_map(t_mapp *map)
{
	int		max_length;
	bool	*out;
	char	**map_arr;
	t_pos	player_pos;

	out = malloc(sizeof(bool *));
	*out = false;
	max_length = get_max_string_length(map);
	map_arr = list_to_array(map, max_length);
	determine_player_pos(&player_pos, map_arr);
	check_borders(map_arr, player_pos.x, player_pos.y, out);
	if (*out)
	{
		free(out);
		return (free_2d_nd_return_bool(map_arr, false));
	}
	free(out);
	return (free_2d_nd_return_bool(map_arr, true));
}

bool	check_validity_of_map(t_mapp *map)
{
	t_mapp	*current;

	current = map->next;
	if (!treat_first_and_last(map->line))
		return (false);
	while (current->next)
	{
		if (!treat_middle_line(current->line))
			return (false);
		current = current->next;
	}
	if (!treat_first_and_last(current->line))
		return (false);
	if (!check_player_position(map) || !valid_map(map))
		return (false);
	return (true);
}

bool	check_validity_of_textures(t_components *comps)
{
	// comps->west_texture = mlx_load_png(comps->path_to_west_texture);
	// comps->east_texture = mlx_load_png(comps->path_to_east_texture);
	// comps->north_texture = mlx_load_png(comps->path_to_north_texture);
	// comps->south_texture = mlx_load_png(comps->path_to_south_texture);
	// if (!comps->west_texture | !comps->east_texture
	// 	| !comps->north_texture | !comps->south_texture)
	// 	return (false);
	return (true);
}
