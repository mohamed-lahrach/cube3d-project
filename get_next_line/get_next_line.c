/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:47:38 by samsaafi          #+#    #+#             */
/*   Updated: 2025/04/10 01:18:36 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join_and_free(char *stash, char *buffer)
{
	char	*ptr;

	ptr = ft_strjoin(stash, buffer);
	free(stash);
	return (ptr);
}

char	*read_file(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = ft_calloc((size_t)BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(stash), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = ft_join_and_free(stash, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	if (bytes_read <= 0 && (!stash || ft_strlen(stash) == 0))
		return (free(stash), NULL);
	if (bytes_read == -1)
		return (free(stash), NULL);
	return (stash);
}

char	*ft_get_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_reset_stash(char *stash)
{
	char	*new_stash;
	int		i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(stash + i + 1);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd == 500)
	{
		free(stash);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_calloc(1, sizeof(char));
	if (!stash)
		return (NULL);
	if (!ft_strchr(stash, '\n'))
		stash = read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	stash = ft_reset_stash(stash);
	return (line);
}

// int	main(void)
// {
// 	char	*result;
// 	int		fd;

// 	fd = open("lines.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Failed to open the file.\n");
// 		return (1);
// 	}
// 	while ((result = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", result);
// 		free(result);
// 	}
// 	close(fd);
// 	return (0);
// }
