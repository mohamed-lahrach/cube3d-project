
#include "../inc/parsing.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	free_and_set_to_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

char	*trim_white_spaces(char *str)
{
	char			*trimmed_str;
	t_TrimIndices	indices;

	if (str == NULL)
		return (NULL);
	indices.start = 0;
	while (str[indices.start] && (str[indices.start] == ' '
			|| str[indices.start] == '\t' || str[indices.start] == '\n'))
		indices.start++;
	indices.end = ft_strlen(str) - 1;
	while (indices.end > indices.start && (str[indices.end] == ' '
			|| str[indices.end] == '\t' || str[indices.end] == '\n'))
		indices.end--;
	trimmed_str = malloc(indices.end - indices.start + 2);
	if (trimmed_str == NULL)
		return (NULL);
	indices.i = indices.start;
	while (indices.i <= indices.end)
	{
		trimmed_str[indices.i - indices.start] = str[indices.i];
		indices.i++;
	}
	trimmed_str[indices.i - indices.start] = '\0';
	return (trimmed_str);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

void	initialize_indices(t_AtoiIndices *indices)
{
	indices->i = 0;
	indices->num = 0;
	indices->sign = 1;
}
