/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/16 19:40:51 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/23 22:55:51 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

/**
 * @brief	Copies the first 'n' bytes of data from memory area
 * pointed to by 'src' to the memory area pointed to by 'dest'.
 * @param	src pointer to memory area storing source data;
 * @param	dest pointer to memory area to copy data to.
 * @param	n unsigned int signifying the number of bytes to copy.
 * @returns a pointer to dest if operation was successfull.
 * 			NULL if wrong input was detected.
 */
static void	*ft_memcpy(void *dest, const void *src, size_t n)
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
 * @brief 	Allocate memory for string buffer of BUFFER_SIZE and/or
 * 			initialze buffer to 0 depending if its memory was allocate before.
 * @param buf pointer to buffer memory.
 * @returns	Size of allocated memory if succesfull
 * 			0 if an error occured
 */
static int	initialize_buffer(char **buf)
{
	size_t	size;

	if (!*buf)
	{
		size = BUFFER_SIZE;
		*buf = malloc(sizeof(char) * (size + 1));
		if (!*buf)
			return (0);
	}
	ft_memset(*buf, 0, size + 1);
	return (size);
}

/**
 * @brief Initialize or grow allocated memory for string 'next_line'
 * @param stb pointer to state table
 * @param nl  pointer to string next_line
 */
int	init_next_line(char **nxln, t_state *stb)
{
	char	*tmp;
	size_t	nxln_old_sz;

	if (!*nxln)
	{
		stb->nxln_siz = initialize_buffer(nxln);
		if (!stb->nxln_siz)
			return (0);
	}
	else
	{
		nxln_old_sz = stb->nxln_siz;
		stb->nxln_siz *= 2;
		tmp = malloc(sizeof(char) * (stb->nxln_siz + 1));
		if (!tmp)
			return (0);
		ft_memset(tmp, 0, stb->nxln_siz + 1);
		ft_memcpy(tmp, *nxln, nxln_old_sz);
		free(*nxln);
		*nxln = tmp;
	}
	return (1);
}

/**
 * @brief ft_memset() fills the first 'n' bytes of the memory area 
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

/**
 * @brief 	Initialize or reset variables to 0.
 * @param	stb static statetable that persists state between function calls.
 * @param	next_line write buffer to store the next line read from 'buffer'
 * @returns	1 for success, 	0 for failure.
 */
int	initialize_variables(t_state *stb, char **next_line)
{
	next_line = NULL;
	if (!stb->initialized)
	{
		*stb = (t_state){0};
		stb->initialized = 1;
	}
	if (!init_next_line(next_line, stb))
		return (0);
	stb->nxln_siz = BUFFER_SIZE;
	stb->i_nxl = 0;
	return (1);
}
