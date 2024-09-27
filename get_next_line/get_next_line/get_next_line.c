#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

long long ft_strlen(char *str)
{
	long long i = -1;
	while (str[++i]);
	return (i);
}
char *ft_strchr(char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

void *ft_calloc(size_t nmemb, size_t size)
{
	void *ptr;
	size_t i;
	i = (size_t)-1;
	ptr = malloc(nmemb * size);
	if (ptr)
	{
		while (++i < nmemb * size)
			*((unsigned char *)ptr + i) = 0;
	}
	return (ptr);
}

void	fill_buffer(char *str)
{
	char *has_nl = ft_strchr(str, '\n');
	ssize_t i = 0;
	ssize_t len;
	if (has_nl)
	{
		len = ft_strlen(has_nl + 1);
		while (i < len)
		{
			str[i] = has_nl [i + 1];
			i++;
		}
		while (i < BUFFER_SIZE)
			str[i++] = '\0';
	}
	else
	{
		while (i < BUFFER_SIZE)
			str[i++] = 0;
	}
}

char *ft_strjoin(char *s1, char *s2)
{
	size_t i = (size_t)-1;
	size_t j = (size_t)-1;
	char *res;
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	res = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (s1[++i])
		res[i] = s1[i];
	while (s2[++j] && s2[j] != '\n')
		res[i++] = s2[j];
	res[i] = s2[j];
	if (s2[j] == '\n')
		res[++i] = '\0';
	fill_buffer(s2);
	free(s1);
	return (res);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE + 1];
	char *line;
	ssize_t len;
	line = NULL;
	len = 1;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buffer[0])
		len = read(fd, buffer, BUFFER_SIZE);
	while (len > 0)
	{
		line = ft_strjoin(line, buffer);
		if (ft_strchr(line, '\n'))
			break ;
		len = read(fd, buffer, BUFFER_SIZE);
	}
	if (len < 0)
	{
		if (line)
			free(line);
		return (NULL);
	}
	return (line);
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	auto int	 fd = open("example.txt", O_RDONLY);
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
		line = NULL;
	}
	free(line);

	close(fd);
	return (0);
}
