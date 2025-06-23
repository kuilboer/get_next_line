/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_new.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/16 19:40:51 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/23 12:00:37 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static void read_next_line_from_buffer(char **nxln, t_state *stb)
{
	while (stb->buffer[stb->i_buf])
	{
		nxln[stb->i_nxl] = stb->buffer[stb->i_buf];
		if (stb.buf_rest[stb.i_rst] == "\n")
		{
			stb->next_lin[++stb->i_nxl] = '\0';
			stb->flag_eol = 1;
			stb->i_buf++;
			stb->i_nxl = 0;
			return ;
		}
		stb->i_buf++;
		stb->i_nxl++;
	}
	stb->flag_eob = 1;
	return;
}

static int	read_buffer_from_file_descriptor(int fd, t_state *stb)
{
	ft_memset(stb->buffer, 0, stb->buff_siz + 1);
	stb->read_cnt = read(fd, stb->buffer, stb->buff_siz);
	if (stb->read_cnt == -1)
			return (0);
		else if (stb->read_cnt == 0)
			stb->flag_eof = 1;
		else
			stb->buffer[stb->read_cnt] = '\0';
			stb->flag_eob = 0;
	return(1);
}