/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_new.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 14:48:51 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/16 20:33:24 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
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
static int	init_next_line(char **nxln, t_state *stb)
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
		stb->nxln_siz *= 2 ; 
		tmp = malloc(sizeof(char) * (stb->nxln_siz + 1));
		if (!tmp)
			return (0);
		ft_memset(tmp, 0, stb->nxln_siz + 1);
		ft_memcpy(tmp, *nxln, nxln_old_sz);
		free(*nxln);
		*nxln= tmp;		
	}
	return (1);
}

int	init_state_table(t_state *stb, char **next_line)
{
	next_line = NULL;
	if (!stb->initialized)
	{
		*stb = (t_state){0};
		stb->initialized = 1;
		stb->nxln_siz = BUFFER_SIZE + 1;
	}
	if (!init_next_line(*next_line, stb))
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_state	stb[1024];
	char			*next_line;

	initialize_variables(&stb[fd], &next_line, &);
	while(!stb[fd].flag_eof)
	{
		while (!stb[fd].flag_eob && )
		{
			while (!stb[fd].flag_eob)
			{
				read_from_buffer(&stb);
				if (stb[fd].flag_eol)
					stb[fd].flag_eol = 0;
					return (next_line);
			}
			if (!read_from_file_descriptor(fd, &stb[fd]));
				return (NULL);
			stb[fd].flag_eob = 0;
		}
		
	}
	return (NULL)
}











	while (!stb[fd].flag_eol)
		process_read_buffer(&stb)





	while (stb[fd].buffer[stb[fd].i_buf] && stb[fd].i_buf < stb[fd].read_cnt)
	{
		stb[fd].next_lin[stb[fd].i_nxl] = stb[fd].buffer[stb[fd].i_buf];
		if (stb[fd].buffer[stb[fd].i_buf] == '\0')
			break ;
	

		/* copy characters from buffer to next line*/
		if (stb.buffer[stb.i_buf] && stb.i_buf < stb.read_cnt)
	}
}
