
#include "../inc/parsing.h"

bool	all_good(t_components *comps)
{
	if (comps->ceiling_color && comps->path_to_east_texture
		&& comps->floor_color && comps->path_to_north_texture
		&& comps->path_to_south_texture && comps->path_to_west_texture)
		return (true);
	else
		return (false);
}

char	*remove_newline(char *line)
{
	int		len;
	char	*temp;

	len = ft_strlen(line);
	if (len == 0)
		return (NULL);
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, line, len + 1);
	if (len > 0 && temp[len - 1] == '\n')
		temp[len - 1] = '\0';
	return (temp);
}

void	add_to_list(t_mapp **head, char *new_line)
{
	t_mapp	*new_node;
	t_mapp	*current;

	new_node = malloc(sizeof(t_mapp));
	if (!new_node)
		return ;
	new_node->line = ft_strdup(new_line);
	if (!new_node->line)
	{
		free(new_node);
		return ;
	}
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

bool	retrieve_map(int fd, t_components *comps, char *line)
{
	char	*cleaned_line;
	char	*temp;

	cleaned_line = remove_newline(line);
	add_to_list(&comps->map, cleaned_line);
	free_and_set_to_null(&cleaned_line);
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = remove_newline(line);
		free_and_set_to_null(&line);
		if (detect_type(temp) != MAP)
			return (return_bool_nd_free(false, &temp));
		add_to_list(&comps->map, temp);
		free_and_set_to_null(&temp);
	}
	return (true);
}

bool	process_line(int fd, t_components *comps, char *line)
{
	char	*temp;
	t_type	info_type;

	temp = trim_white_spaces(line);
	if (ft_strlen(temp) == 0)
	{
		free_and_set_to_null(&line);
		free_and_set_to_null(&temp);
		return (true);
	}
	info_type = detect_type(temp);
	if (info_type == MAP)
		return (handle_map_type(fd, comps, line, temp));
	if (info_type == INVALID)
		return (free_and_set_to_null(&line), return_bool_nd_free(false, &temp));
	if (!fill_container(info_type, temp, comps))
	{
		free_and_set_to_null(&line);
		return (return_bool_nd_free(false, &temp));
	}
	free_and_set_to_null(&line);
	free_and_set_to_null(&temp);
	return (true);
}
