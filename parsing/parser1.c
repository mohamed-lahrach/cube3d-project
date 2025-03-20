
#include "../inc/parsing.h"

void	free_t_colors(t_colors **colors)
{
	if (colors != NULL && *colors != NULL)
	{
		free(*colors);
		*colors = NULL;
	}
}

void	free_mapp(t_mapp **head)
{
	t_mapp	*current;
	t_mapp	*next_node;

	current = *head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->line);
		free(current);
		current = next_node;
	}
	*head = NULL;
}

// void	free_mlx_texture(mlx_texture_t **texture)
// {
// 	free((*texture)->pixels);
// 	free(*texture);
// 	*texture = NULL;
// }

void	free_comps(t_components *comps)
{
	if (comps->ceiling_color)
		free_t_colors(&comps->ceiling_color);
	if (comps->floor_color)
		free_t_colors(&comps->floor_color);
	if (comps->map)
		free_mapp(&comps->map);
	if (comps->path_to_north_texture)
		free_and_set_to_null(&comps->path_to_north_texture);
	if (comps->path_to_south_texture)
		free_and_set_to_null(&comps->path_to_south_texture);
	if (comps->path_to_east_texture)
		free_and_set_to_null(&comps->path_to_east_texture);
	if (comps->path_to_west_texture)
		free_and_set_to_null(&comps->path_to_west_texture);
}

bool	parse_the_file(char *path, t_components *comps)
{
	int	fd;

	set_all_to_null(comps);
	fd = open_file_and_return_fd(path);
	if (!check_validity_of_file(fd))
		return (false);
	if (!fill_it(fd, comps))
	{
		ft_putstr_fd("Error\nfailed filling components\n", 2);
		free_comps(comps);
		return (false);
	}
	if (!check_validity_of_textures(comps))
	{
		ft_putstr_fd("Error\ninvalid texture\n", 2);
		free_comps(comps);
		return (false);
	}
	if (!check_validity_of_map(comps->map))
	{
		ft_putstr_fd("Error\ninvalid map\n", 2);
		free_comps(comps);
		return (false);
	}
	return (true);
}
