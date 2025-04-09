/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:54:20 by mlahrach          #+#    #+#             */
/*   Updated: 2025/04/09 17:57:09 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	(void)comps;
	return (true);
}
