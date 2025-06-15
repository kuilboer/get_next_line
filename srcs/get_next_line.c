/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/04 22:28:10 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/07 09:05:40 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
static int	initialize_buffer(char **buf)
{
	size_t	size;

	if (!buf)
	{
		size = BUFFER_SIZE;
		*buf = malloc(sizeof(char) * (size + 1));
		if (!*buf)
			return (0);
	}
	ft_memset(*buf, 0, size + 1);
	return (1);
}

static int	init_next_line(char *nl, t_state *stb)
{
	char	*tmp;
	size_t	next_lin_old_size;

	if (!stb->next_lin)
		if (!initialize_buffer(stb->next_lin))
			return (0);
	else
	{
		next_lin_old_size = stb->next_lin_siz;
		stb->next_lin_siz += BUFFER_SIZE; 
		tmp = malloc(sizeof(char) * (stb->next_lin_siz + 1));
		if (!tmp)
			return (0);
		ft_memset(tmp, 0, stb->next_lin_siz + 1);
		ft_memcpy(tmp, stb->next_lin, next_lin_old_size);
		free(stb->next_lin);
		stb->next_lin = tmp;		
	}
	return (1);
}


static void read_from_buffer(t_state *stb)
{
	size_t	i;

	i = 0;
	while (stb->buffer[stb->i_buf])
	{
		stb.next_lin[stb.i_nxl] = stb->buffer[stb->i_buf];
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

static int	read_from_file_descriptor(int fd, t_state *stb)
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

/**
 * @brief	Read the next line from file or standard input.
 * @param fd File Descriptor.
 * @return 
 * 	- stb.next_lin a free()able handle to char string containing the nextline
 * 	  read including the \\n.
 * 
 *	- NULL if there is no more content to read or an error occured.
 */
char	*get_next_line(int fd)
{
	static char buf_rest[BUFFER_SIZE + 1];
	t_state stb;

	stb = (t_state){0};
	stb.buff_siz = BUFFER_SIZE;
	if (!init_next_line(&stb))
		return (NULL);
	if (!read_from_file_descriptor(fd, &stb))
	{
		free(stb.next_lin);
		return(NULL);
	}
	if (unprocessed_buffer())
	while (stb.buffer[stb.i_buf])
	{
		while (buf_rest[stb.i_rst])
		{
			stb.next_lin[stb.i_nxl++] = buf_rest[stb.i_rst++];
			if (stb.buf_rest[stb.i_rst] == "\n")
			{
				stb.flag_eol = 1;
				break ;
			}
		ft_memset(buf_rest, 0, BUFFER_SIZE + 1);
		while (stb.buffer[stb.i_buf])
		{
			stb.next_lin[stb.i_nxl++] = stb.buffer[stb.i_buf++];
		}
	}	
	return (next_line);
}


/** 
	 * 1. All helper functions go in the get_next_line_utils.c file.
	 * 2. What is a file descriptor and how to use it;
	 * 3. What are static variables and why are they significant for this assignment?
	 *    https://en.wikipedia.org/wiki/Static_variable
	 * 4. Read-up on -D BUFFER_SIZE Precompiler Macro;
	 * 5. Readup on the read() funcion;
	 * 6. Reading a file one line per call how to track reading state between consecutive calls?
	 * 7. How to manage read buffer and have the line ready for return if and when a lin termination character is read.
	 * 8. 
	 * 
	 */
