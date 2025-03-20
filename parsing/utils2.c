
#include "../inc/parsing.h"

bool	is_valid_digit(const char *str, t_AtoiIndices *indices)
{
	return (ft_isdigit(str[indices->i]));
}

void	convert_to_number(const char *str, t_AtoiIndices *indices)
{
	while (ft_isdigit(str[indices->i]))
	{
		indices->num = indices->num * 10 + (str[indices->i] - '0');
		indices->i++;
	}
}

bool	check_end_of_string(const char *str, t_AtoiIndices *indices)
{
	return (str[indices->i] == '\0');
}

int	ft_super_atoi(const char *str)
{
	t_AtoiIndices	indices;

	initialize_indices(&indices);
	skip_whitespace(str, &indices);
	if (!check_length(str, &indices))
		return (-1);
	handle_sign(str, &indices);
	if (!is_valid_digit(str, &indices))
		return (-1);
	convert_to_number(str, &indices);
	if (!check_end_of_string(str, &indices))
		return (-1);
	indices.num *= indices.sign;
	return (indices.num);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
