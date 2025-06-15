/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/04 22:38:12 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/07 09:05:42 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * This file stores all the helper functions for get_next_line
 */

/*
* The memcpy() function copies n bytes from memory area src to memory area dest.
* The memory areas must not overlap.  Use memmove(3) if the memory areas do
* overlap.

* Parameters:
*	- src : memory area that stores the source data to copy;
*	- dest: memory area to copy to;
*	- n   : Integer specifying the maximum number of bytes to copy.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d_buf;
	unsigned char	*s_buf;

	if (!dest && !src && n > 0)
		return (NULL);
	d_buf = (unsigned char *)dest;
	s_buf = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d_buf[i] = s_buf[i];
		i++;
	}
	return ((void *)dest);
}

 /**
  * @brief The memset() function fills the first 'n' bytes of the memory area 
  * pointed to by 's' with the constant byte 'c'.
  * @param	s pointer to memory area to initialize.
  * @param	c character byte code to write to 's'.
  * @param	n maxiimum number of bytes to write.
  */ 
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return ((void *)s);
}
size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return ((size_t)i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return ((size_t)i);
}

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		s_len;

	s_len = ft_strlen(s);
	new_str = malloc((s_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s, (s_len + 1));
	return (new_str);
}


int	next_line_complete(char *buffer, char *next_line)
{
	static char buf_rest[BUFFER_SIZE + 1];

	i = 0;
	j = 0;
	while (buf_rest[i])
		next_line[i] = buf_rest[i++];
	ft_memset(buf_rest, 0,	BUFFER_SIZE + 1);
	while (buffer[j])
	{
		next_line[i++] = buffer[j];
		if (buffer[j++] == '\n')
			break;
	}
	if (next_line[i-1])
	next_line[i] = '\0'
	while (buffer[i])
		buf_rest[j++] = buffer[i++];
	buf_rest[i] = '\0';

	
		
		next_line[i] = buffer[i++];
	next_line[i] = '\0';
	while (buffer[i])
		buf_rest[]

		if (buffer[i] == '/n')
			return ()
		next_line[i] = buffer[i];
		i++;
	}
}
 
int	read_from_file(int fd, char *buffer)
{
	ssize_t	ret;

	ret = read(fd, buffer, (sizeof(buffer) - 1));
	if (ret == 0)
		/* end of file*/
	else if (ret > 0)
		/* Bytes read.*/
		buffer[ret] = "\0";
	else
		return (NULL)
	return (ret);
}