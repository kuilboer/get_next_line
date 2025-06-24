/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 14:48:51 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/24 16:33:12 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

static void	clean_up_after_error(char **nxln, t_state *stb)
{
	if (*nxln)
		free(nxln);
	stb->flag_err = 1;
	nxln = NULL;
}

static int	read_buffer_from_file_descriptor(int fd, t_state *stb)
{
	int	result;

	ft_memset(stb->buffer, 0, stb->buff_siz + 1);
	result = read(fd, stb->buffer, stb->buff_siz);
	if (result == -1)
		return (0);
	else if (result == 0)
	{
		stb->flag_eof = 1;
	}
	else
	{
		stb->buffer[result] = '\0';
		stb->flag_eob = 0;
		stb->i_buf = 0;
	}
	return (1);
}

static void	read_next_line_from_buffer(char **nxln, t_state *stb)
{
	while (stb->buffer[stb->i_buf] && stb->i_nxl < stb->nxln_siz)
	{
		(*nxln)[stb->i_nxl] = stb->buffer[stb->i_buf];
		if (stb->buffer[stb->i_buf] == '\n')
		{
			(*nxln)[++stb->i_nxl] = '\0';
			stb->flag_eol = 1;
			stb->i_buf++;
			return ;
		}
		stb->i_buf++;
		stb->i_nxl++;
	}
	if (!stb->buffer[stb->i_buf])
		stb->flag_eob = 1;
	if (stb->i_nxl >= stb->nxln_siz)
		stb->flag_eonl = 1;
	return ;
}

char	*get_next_line(int fd)
{
	static t_state	stb[1024];
	char			*next_line;

	if (!initialize_variables(&next_line, &stb[fd]))
		clean_up_after_error(&next_line, &stb[fd]);
	while (!(stb[fd].flag_eof || stb[fd].flag_err || stb[fd].flag_eol))
	{
		read_next_line_from_buffer(&next_line, &stb[fd]);
		if (stb[fd].flag_eonl)
			if (!init_next_line(&next_line, &stb[fd]))
				clean_up_after_error(&next_line, &stb[fd]);
		if (stb[fd].flag_eob)
			if (!read_buffer_from_file_descriptor(fd, &stb[fd]))
				clean_up_after_error(&next_line, &stb[fd]);
	}
	if (stb->flag_eof && !next_line[0])
		clean_up_after_error(&next_line, &stb[fd]);
	return (next_line);
}
