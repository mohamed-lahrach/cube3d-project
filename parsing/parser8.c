
#include "../inc/parsing.h"

int	get_length(char *array[])
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		i++;
	}
	return (i);
}

bool	check_color_validity(char *str, int *color_value)
{
	*color_value = ft_super_atoi(str);
	if (*color_value < 0)
		return (false);
	else
		return (true);
}

bool	process_colors(char **array, t_colors *color)
{
	char	*trimmed;
	int		i;
	int		color_value;

	i = 0;
	while (i < 3)
	{
		trimmed = trim_white_spaces(array[i]);
		if (!check_color_validity(trimmed, &color_value))
		{
			free(trimmed);
			return (false);
		}
		if (i == 0)
			color->red = color_value;
		else if (i == 1)
			color->green = color_value;
		else if (i == 2)
			color->blue = color_value;
		free(trimmed);
		i++;
	}
	return (true);
}

bool	deal_with_colors(t_type info_type, t_components *comps, char **splitted)
{
	if (info_type == CEILING)
	{
		comps->ceiling_color = malloc(sizeof(t_colors));
		return (process_colors(splitted, comps->ceiling_color));
	}
	else if (info_type == FLOOR)
	{
		comps->floor_color = malloc(sizeof(t_colors));
		return (process_colors(splitted, comps->floor_color));
	}
	return (false);
}

int	count_commas(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == ',')
			count++;
		str++;
	}
	return (count);
}
