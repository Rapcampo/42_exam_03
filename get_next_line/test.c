/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 01:11:52 by rapcampo          #+#    #+#             */
/*   Updated: 2024/09/27 01:26:04 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

char *ft_strdup(char *src)
{
	char *dest;
	int i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\n';
	return (dest);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	char line[70000];
	static int buffer_read;
	static int buffer_index;
	int i = 0;
	if (fd < 0 || BUFFER_SIZE  <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_index >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_index = 0;
			if (buffer_read <= 0)
				break ;
		}
		line[i++] = buffer[buffer_index++];
		if (line[i - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}
