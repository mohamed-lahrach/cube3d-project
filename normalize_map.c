/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:09:47 by mlahrach          #+#    #+#             */
/*   Updated: 2025/03/26 05:21:00 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	replace_spaces_with_walls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == ' ')
				map->grid[i][j] = '1';
			j++;
		}
		i++;
	}
}

static void	pad_single_row(char **row_ptr, int target_length)
{
	char	*old_row;
	char	*new_row;
	int		j;

	old_row = *row_ptr;
	new_row = malloc(sizeof(char) * (target_length + 1));
	j = 0;
	if (!new_row)
		return ;
	while (old_row[j])
	{
		new_row[j] = old_row[j];
		j++;
	}
	while (j < target_length)
		new_row[j++] = '1';
	new_row[j] = '\0';
	free(old_row);
	*row_ptr = new_row;
}

void	pad_rows_to_equal_length(t_map *map)
{
	int	i;
	int	longest_len;

	i = 0;
	longest_len = get_num_rows(map->grid);
	while (map->grid[i])
	{
		pad_single_row(&map->grid[i], longest_len);
		i++;
	}
}

void	normalize_map(t_map *map)
{
	replace_spaces_with_walls(map);
	pad_rows_to_equal_length(map);
}
