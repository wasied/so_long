/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:16:17 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/02/15 10:56:18 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* alloc_read_buffer
-> Read the file descriptor and return the allocated buffer string
*/
char	*alloc_read_buffer(int fd)
{
	char		*buf;
	ssize_t		res;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	res = read(fd, buf, BUFFER_SIZE);
	if (res <= 0)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

/* add_read_to_buffer
-> Add the next fd read to the current buffer
*/
ssize_t	add_read_to_buffer(char **buf, char *nxt)
{
	char	*tmp;
	size_t	new_size;

	tmp = NULL;
	new_size = ft_strlen(nxt);
	if (*buf)
	{
		new_size += ft_strlen(*buf);
		tmp = ft_strndup(*buf, ft_strlen(*buf));
		free(*buf);
	}
	*buf = ft_calloc(new_size + 1, sizeof(char));
	if (tmp)
	{
		ft_strlcat(*buf, tmp, -1);
		free(tmp);
	}
	if (!*buf)
		return (-1);
	ft_strlcat(*buf, nxt, -1);
	free(nxt);
	return (0);
}

/* check_remaind
-> Check for \n in the remainder string before reading anything
*/
char	*check_remaind(char **rmd)
{
	char	*fnd;
	char	*buf;
	char	*cpy;

	cpy = ft_strndup(*rmd, ft_strlen(*rmd));
	if (!cpy)
		return (NULL);
	fnd = ft_strchr(cpy, '\n');
	if (fnd)
	{
		buf = ft_strndup(*rmd, ft_strlen(*rmd) - (ft_strlen(fnd) - 1));
		free(*rmd);
		if (buf && ft_strlen(buf) == 0)
			free(buf);
		if (buf && ft_strlen(fnd + 1) > 0)
			*rmd = ft_strndup(fnd + 1, ft_strlen(fnd + 1));
		else
			*rmd = NULL;
		free(cpy);
		return (buf);
	}
	free(*rmd);
	*rmd = cpy;
	return (NULL);
}

/* loop_buf
-> Loop through the buffer to find a new line
-> Return values:
	- 0 = continue without returning anything
	- 1 = return NULL
*/
size_t	loop_buf(int fd, char **buf, char **rmd)
{
	char	*fnd;
	char	*tmp;
	char	*nxt;

	fnd = NULL;
	nxt = NULL;
	while (1)
	{
		nxt = alloc_read_buffer(fd);
		if (!nxt)
			break ;
		if (add_read_to_buffer(buf, nxt) == -1)
			return (1);
		fnd = ft_strchr(*buf, '\n');
		if (fnd)
		{
			if (ft_strlen(fnd + 1) > 0)
				*rmd = ft_strndup(fnd + 1, ft_strlen(fnd + 1));
			tmp = ft_strndup(*buf, ft_strlen(*buf) - (ft_strlen(fnd) - 1));
			free(*buf);
			*buf = tmp;
			break ;
		}
	}
	return (0);
}

/* get_next_line
-> The main function used to get the next line string of a file descriptor
*/
char	*get_next_line(int fd)
{
	static char	*rmd = NULL;
	char		*buf;
	char		*tmp;

	buf = NULL;
	if (fd >= 0 && BUFFER_SIZE > 0 && rmd)
	{
		tmp = check_remaind(&rmd);
		if (tmp)
			return (tmp);
		else
		{
			if (ft_strlen(rmd) > 0)
			{
				buf = ft_strndup(rmd, ft_strlen(rmd));
				if (!buf)
					return (NULL);
			}
			free(rmd);
			rmd = NULL;
		}
	}
	if (BUFFER_SIZE > 0 && fd >= 0 && loop_buf(fd, &buf, &rmd) == 1)
		return (NULL);
	return (buf);
}
