/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:57:03 by dnikifor          #+#    #+#             */
/*   Updated: 2023/11/10 16:23:11 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strcpy_newl(char *src)
{
	int		i;
	char	*ptr;
	char	*dest;

	i = 0;
	if (!src[i])
		return (NULL);
	while (src[i] != '\n' && src[i] != '\0')
		i++;
	dest = malloc((i + 2) * sizeof(char));
	if (!dest)
		return (NULL);
	ptr = dest;
	i = 0;
	while (src[i] != '\n' && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		dest[i] = '\n';
		i++;
	}
	dest[i] = '\0';
	return (ptr);
}

char	*ft_strcpy_nullt(char *src)
{
	int		i;
	int		j;
	char	*ptr;
	char	*dest;

	i = 0;
	j = 0;
	while (src[i] != '\n' && src[i] != '\0')
		i++;
	if (!src[i])
	{
		free(src);
		return (NULL);
	}
	dest = malloc((ft_strlen(src) - i + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i++;
	ptr = dest;
	while (src[i] != '\0')
		dest[j++] = src[i++];
	dest[j] = '\0';
	free(src);
	return (ptr);
}

char	*str_extractor(char *text_runner, int fd)
{
	int			bytes;
	char		*buffer;

	bytes = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(text_runner, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		text_runner = ft_strjoin(text_runner, buffer);
		if (!text_runner)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (text_runner);
}

char	*get_next_line(int fd)
{
	char		*current_line;
	static char	*text_runner;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	text_runner = str_extractor(text_runner, fd);
	if (!text_runner)
	{
		return (NULL);
	}
	current_line = ft_strcpy_newl(text_runner);
	text_runner = ft_strcpy_nullt(text_runner);
	if (!text_runner)
	{
		return (NULL);
	}
	return (current_line);
}


int	main()
{
	int file_descriptor;
	char *str;
	file_descriptor = open("test.txt", O_RDONLY);
	str = get_next_line(file_descriptor);
	printf("%s", str);
	str = get_next_line(file_descriptor);
	printf("%s", str);
	str = get_next_line(file_descriptor);
	printf("%s", str);
	str = get_next_line(file_descriptor);
	printf("%s", str);
}
