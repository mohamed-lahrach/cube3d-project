
#include "../inc/parsing.h"

bool	is_a_position_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

bool	check_player_position(t_mapp *map)
{
	t_mapp	*current;
	int		position_char_count;
	int		i;

	i = -1;
	current = map;
	position_char_count = 0;
	while (current)
	{
		i = -1;
		while (current->line[++i])
		{
			if (is_a_position_char(current->line[i]))
				position_char_count++;
		}
		current = current->next;
	}
	if (position_char_count != 1)
		return (false);
	return (true);
}

char	**list_to_array(t_mapp *head, int max_length)
{
	int		count;
	t_mapp	*current;
	char	**array;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	array = (char **)malloc(sizeof(char *) * (count + 1));
	current = head;
	copy_list_to_array(head, array, max_length);
	return (array);
}

void	determine_player_pos(t_pos *pos, char **arr)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (arr[y])
	{
		x = 0;
		while (arr[y][x])
		{
			if (is_a_position_char(arr[y][x]))
			{
				pos->y = y;
				pos->x = x;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	check_borders(char **map_arr, int x, int y, bool *out)
{
	if (!map_arr[y][x] || map_arr[y][x] == ' ')
	{
		*out = true;
		return ;
	}
	if (map_arr[y][x] == '1' || map_arr[y][x] == '2')
		return ;
	map_arr[y][x] = '2';
	if (map_arr[y + 1])
		check_borders(map_arr, x, y + 1, out);
	check_borders(map_arr, x + 1, y, out);
	check_borders(map_arr, x, y - 1, out);
	check_borders(map_arr, x - 1, y, out);
}
