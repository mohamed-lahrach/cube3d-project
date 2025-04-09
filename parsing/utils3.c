/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:55:07 by mlahrach          #+#    #+#             */
/*   Updated: 2025/04/09 17:56:25 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	skip_whitespace(const char *str, t_AtoiIndices *indices)
{
	while (ft_isspace(str[indices->i]))
		indices->i++;
}

bool	check_length(const char *str, t_AtoiIndices *indices)
{
	return (ft_strlen(&str[indices->i]) <= 3);
}

void	handle_sign(const char *str, t_AtoiIndices *indices)
{
	if (str[indices->i] == '-' || str[indices->i] == '+')
	{
		if (str[indices->i] == '-')
			indices->sign = -1;
		indices->i++;
	}
}

int	get_y(t_mapp *head)
{
	int	height;

	height = 0;
	while (head)
	{
		height++;
		head = head->next;
	}
	return (height);
}
