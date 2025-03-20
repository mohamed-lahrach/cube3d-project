
#include "../inc/cub3d.h"

bool	valid_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (false);
	if (!(ft_strcmp(&path[len - 4], ".cub")))
		return (true);
	return (false);
}

int	open_file_and_return_fd(char *path)
{
	int	fd;

	if (!valid_path(path))
		return (-1);
	fd = open(path, O_RDONLY);
	return (fd);
}

void	copy_list_to_array(t_mapp *head, char **array, int max_length)
{
	int		i;
	int		len;
	t_mapp	*current;

	i = 0;
	current = head;
	while (current != NULL)
	{
		array[i] = (char *)malloc(max_length + 1);
		ft_strncpy(array[i], current->line, max_length);
		len = strlen(current->line);
		if (len < max_length)
		{
			ft_memset(array[i] + len, '\0', max_length - len);
		}
		array[i][max_length] = '\0';
		current = current->next;
		i++;
	}
	array[i] = NULL;
}

bool	handle_map_type(int fd, t_components *comps, char *line, char *temp)
{
	if (!retrieve_map(fd, comps, line))
	{
		free_and_set_to_null(&line);
		return (return_bool_nd_free(false, &temp));
	}
	if (all_good(comps))
	{
		free_and_set_to_null(&line);
		return (return_bool_nd_free(true, &temp));
	}
	free_and_set_to_null(&line);
	return (return_bool_nd_free(false, &temp));
}

bool	fill_it(int fd, t_components *comps)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!process_line(fd, comps, line))
			return (false);
	}
	return (true);
}
