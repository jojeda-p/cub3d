/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:13:11 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/04 12:42:54 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static void	without_newline(char ***dest, char **src, char *buf, int i)
{
	int		j;

	while(src[i])
	{
    j = ft_strlen(src[i]);
    if (!src[i + 1])
        (*dest)[i] = malloc(j + 2);
    else
        (*dest)[i] = malloc(j + 1);
    j = 0;
    while(src[i][j])
    {
        (*dest)[i][j] = src[i][j];
        j++;
    }
    if (!src[i + 1])
    {
        (*dest)[i][j] = buf[0];
        (*dest)[i][j + 1] = '\0';
    }
    else
        (*dest)[i][j] = '\0';
    i++;
	}
	(*dest)[i] = NULL;
}

static void	with_newline(char ***dest, char **src, char *buf)
{
	int		j;
	int		i;

	i = 0;
	while(src[i])
	{
		j = ft_strlen(src[i]);
		(*dest)[i] = malloc(sizeof(char) * (j + 1));
		j = 0;
		while(src[i][j])
		{
			(*dest)[i][j] = src[i][j];
			j++;
		}
		(*dest)[i][j] = '\0';
		i++;
	}
	(*dest)[i] = malloc(sizeof(char) * 2);
	(*dest)[i][0] = buf[0];
	(*dest)[i][1] = '\0';
	(*dest)[i + 1] = NULL;
}

static char	**void_matrix(char *buf)
{
	char	**dest;

	dest = malloc(sizeof(char *) * 2);
	dest[0] = malloc(sizeof(char) * 2);
	dest[0][0] = buf[0];
	dest[0][1] = '\0';
	dest[1] = NULL;
	return (dest);
}

static char	**memmove_v2(char **src, char *buf)
{
	char	**dest;
	int		i;
	int		j;

	if (!src[0])
		return (void_matrix(buf));
	i = 0;
	while (src[i])
	{
		j = 0;
		while (src[i][j])
			j++;
		i++;
	}
	if (src[i - 1][j -1] == '\n')
	{
		dest = malloc(sizeof(char *) * (i + 2));
		with_newline(&dest, src, buf);
	}
	else
	{
		dest = malloc(sizeof(char *) * (i + 1));
		without_newline(&dest, src, buf, 0);
	}
	return (dest);
}

char	**parse_content(char *file)
{
	int		fd;
	char	**buffer;
	char	**temp;
	char	buf[2];

	buffer = malloc(sizeof(char *) * 1);
	if (!buffer)
		return (NULL);
	buffer[0] = NULL;
	buf[1] = '\0';
	fd = open(file, O_RDONLY);
	while (read(fd, buf, 1) > 0)
	{
		temp = buffer;
		buffer = memmove_v2(buffer, buf);
		free_matrix(temp);
	}
	close(fd);
	return (buffer);
}