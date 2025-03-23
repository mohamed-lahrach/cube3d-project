/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:27:11 by mlahrach          #+#    #+#             */
/*   Updated: 2025/03/23 02:32:57 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	get_num_columns(char **grid)
{
	int	num_rows;

	num_rows = 0;
	while (grid[num_rows] != NULL)
		num_rows++;
	return (num_rows);
}

int	get_num_rows(char **grid)
{
	int	max_len;
	int	i;
	int	len;

	max_len = 0;
	i = 0;
	while (grid[i])
	{
		len = ft_strlen(grid[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}
