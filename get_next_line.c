/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqiouami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 09:04:55 by aqiouami          #+#    #+#             */
/*   Updated: 2022/10/23 10:08:35 by aqiouami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*readf(char *str, int fd)
{
	int		i;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	i = 1;
	if (!str)
		str = ft_calloc(1, 1);
	while (!ft_strchr(str, '\n') && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1 || (str[0] == 0 && i == 0))
		{
			free (str);
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free (buffer);
	return (str);
}

int	chars_before_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*create(char *str)
{
	int		i;
	char	*line;

	i = chars_before_newline(str);
	if (str[i] == '\n')
		i++;
	line = ft_substr(str, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*the_remainder(char *str)
{
	int		i;
	int		len;
	char	*rema;

	i = chars_before_newline(str);
	i++;
	len = ft_strlen(str) - i;
	rema = ft_substr(str, i, len);
	free (str);
	return (rema);
}

char	*get_next_line(int fd)
{
	static char		*stash;
	char			*line;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	stash = readf(stash, fd);
	if (!stash)
		return (NULL);
	line = create(stash);
	stash = the_remainder(stash);
	return (line);
}
// #include <fcntl.h>
// int	main(void)
// {
// 	int		fd;
//
// 	fd = open("text.txt", O_RDONLY);
// 	char *line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// }
