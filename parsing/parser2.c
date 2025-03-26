
#include "../inc/parsing.h"

bool	check_validity_of_file(int fd)
{
	if (fd < 0)
	{
		perror("invalid file");
		return (false);
	}
	return (true);
}

bool	valid_map_line(char *str)
{
	if (str != NULL)
	{
		if (ft_strlen(str) == 0)
			return (false);
		while (*str)
		{
			if (*str != '0' && *str != '1' && *str != 'N' && *str != 'S'
				&& *str != 'E' && *str != 'W' && *str != 32)
				return (false);
			str++;
		}
		return (true);
	}
	return (false);
}

void	ft_free(char **splitted)
{
	int	c;

	c = 0;
	while (splitted[c])
	{
		free(splitted[c]);
		splitted[c] = NULL;
		c++;
	}
	free(splitted);
	return ;
}

t_type	return_nd_free(t_type this, char **arr)
{
	ft_free(arr);
	return (this);
}

int	get_color(t_colors *color)
{
    int alpha = 255; // Fully opaque
    return ((alpha << 24) | (color->red << 16) | (color->green << 8) | color->blue);
}
