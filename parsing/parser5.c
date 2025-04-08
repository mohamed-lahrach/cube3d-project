
#include "../inc/parsing.h"

void	set_all_to_null(t_components *comps)
{
	comps->ceiling_color = NULL;
	comps->floor_color = NULL;
	comps->path_to_east_texture = NULL;
	comps->path_to_west_texture = NULL;
	comps->path_to_north_texture = NULL;
	comps->path_to_south_texture = NULL;
	comps->map = NULL;
}

void	print_components(const t_components *components)
{
	if (components == NULL)
	{
		printf("Components is NULL\n");
		return ;
	}
	printf("Floor color: %d, %d, %d\n", components->floor_color->red,
		components->floor_color->green, components->floor_color->blue);
	printf("Ceiling color: %d, %d, %d\n", components->ceiling_color->red,
		components->ceiling_color->green, components->ceiling_color->blue);
	printf("West texture: %s\n", components->path_to_west_texture);
	printf("East texture: %s\n", components->path_to_east_texture);
	printf("North texture: %s\n", components->path_to_north_texture);
	printf("South texture: %s\n", components->path_to_south_texture);
}

bool	adjacent_space(char *line)
{
	if (*line == ' ')
	{
		if (*(line - 1) != ' ' && *(line - 1) != '1')
			return (false);
		if (*(line + 1) != ' ' && *(line + 1) != '1' && *(line + 1) != '\0')
			return (false);
	}
	return (true);
}

bool	treat_middle_line(char *line)
{
	while (*line && *line == ' ')
		line++;
	if (*line != '1')
		return (false);
	while (*line)
	{
		if (!adjacent_space(line))
			return (false);
		line++;
	}
	line--;
	while (*line && *line == ' ')
		line--;
	if (*line != '1')
		return (false);
	return (true);
}

bool	treat_first_and_last(char *line)
{
	if (!*line)
		return(false);
	while (*line && *line == ' ')
		line++;
	while (*line)
	{
		if (*line != ' ' && *line != '1')
			return (false);
		line++;
	}
	return (true);
}
