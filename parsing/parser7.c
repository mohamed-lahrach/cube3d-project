
#include "../inc/parsing.h"

bool	free_2d_nd_return_bool(char **splitted, bool boolean)
{
	ft_free(splitted);
	return (boolean);
}

bool	parse_colors_string(t_type info_type, char *temp, t_components *comps)
{
	char	*colors_str;
	char	**splitted;
	int		starting_index;
	int		last_appearance;

	starting_index = where_to_start(info_type, temp);
	last_appearance = where_to_finish(starting_index, temp);
	colors_str = ft_substr(temp, starting_index, last_appearance
			- starting_index);
	splitted = ft_split(colors_str, ',');
	if (count_commas(colors_str) != 2)
	{
		free_and_set_to_null(&colors_str);
		return (free_2d_nd_return_bool(splitted, false));
	}
	free_and_set_to_null(&colors_str);
	if (get_length(splitted) != 3)
		return (free_2d_nd_return_bool(splitted, false));
	if (!deal_with_colors(info_type, comps, splitted))
		return (free_2d_nd_return_bool(splitted, false));
	return (free_2d_nd_return_bool(splitted, true));
}

bool	parse_colors(t_type info_type, char *temp, t_components *comps)
{
	if (info_type == FLOOR && comps->floor_color)
		return (false);
	else if (info_type == CEILING && comps->ceiling_color)
		return (false);
	if (parse_colors_string(info_type, temp, comps))
		return (true);
	else
		return (false);
}

bool	fill_container(t_type info_type, char *temp, t_components *comps)
{
	if (info_type == NORTH || info_type == SOUTH || info_type == EAST
		|| info_type == WEST)
		return (parse_textures(info_type, temp, comps));
	else if (info_type == FLOOR || info_type == CEILING)
		return (parse_colors(info_type, temp, comps));
	return (false);
}

bool	return_bool_nd_free(bool boolean, char **temp)
{
	free(*temp);
	*temp = NULL;
	return (boolean);
}
