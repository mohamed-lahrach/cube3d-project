
#include "../inc/parsing.h"

t_type	detect_type(char *str)
{
	char	**arr;

	arr = ft_split(str, ' ');
	if (!str)
		return (return_nd_free(INVALID, arr));
	if (!arr[0])
		return (return_nd_free(INVALID, arr));
	else if (valid_map_line(str))
		return (return_nd_free(MAP, arr));
	else if ((!(ft_strcmp(arr[0], "NO"))) && arr[1])
		return (return_nd_free(NORTH, arr));
	else if ((!(ft_strcmp(arr[0], "SO"))) && arr[1])
		return (return_nd_free(SOUTH, arr));
	else if ((!(ft_strcmp(arr[0], "EA"))) && arr[1])
		return (return_nd_free(EAST, arr));
	else if ((!(ft_strcmp(arr[0], "WE"))) && arr[1])
		return (return_nd_free(WEST, arr));
	else if ((!(ft_strcmp(arr[0], "F"))) && arr[1])
		return (return_nd_free(FLOOR, arr));
	else if ((!(ft_strcmp(arr[0], "C"))) && arr[1])
		return (return_nd_free(CEILING, arr));
	else
		return (return_nd_free(INVALID, arr));
}

bool	parse_texture_string(t_type info_type, char *temp, t_components *comps)
{
	char	**splitted;

	splitted = ft_split(temp, ' ');
	if (get_length(splitted) > 2)
		return (false);
	if (info_type == NORTH)
		comps->path_to_north_texture = ft_strdup(splitted[1]);
	else if (info_type == SOUTH)
		comps->path_to_south_texture = ft_strdup(splitted[1]);
	else if (info_type == EAST)
		comps->path_to_east_texture = ft_strdup(splitted[1]);
	else if (info_type == WEST)
		comps->path_to_west_texture = ft_strdup(splitted[1]);
	ft_free(splitted);
	return (true);
}

bool	parse_textures(t_type info_type, char *temp, t_components *comps)
{
	if (info_type == NORTH && comps->path_to_north_texture)
		return (false);
	else if (info_type == SOUTH && comps->path_to_south_texture)
		return (false);
	else if (info_type == EAST && comps->path_to_east_texture)
		return (false);
	else if (info_type == WEST && comps->path_to_west_texture)
		return (false);
	return (parse_texture_string(info_type, temp, comps));
}

int	where_to_start(t_type info_type, char *temp)
{
	int	i;

	i = 0;
	if (info_type == CEILING)
		i++;
	else if (info_type == FLOOR)
		i = i + 2;
	while (temp[i] && (temp[i] == 32 || temp[i] == 9))
		i++;
	return (i);
}

int	where_to_finish(int starting_index, char *temp)
{
	int	i;

	i = starting_index;
	while (temp[i] && temp[i] != '\0' && temp[i] != '\n')
		i++;
	i--;
	while (i >= starting_index && (temp[i] == ' ' || temp[i] == '\t'))
		i--;
	return (i + 1);
}
