/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 14:48:51 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/30 22:38:42 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void	clean_up_after_error(char **nxln, t_state *stb)
{
	// if (stb->flag_err || stb->eob)
	// 	printf("\nflag_err = %d\nflag_eof = %d" stb->flag_err, stb->flag_eof);
	// if (stb->buffer)
	// 	prinf("\nBuffer = "%s"\n", stb->buffer)
	// else
	// 	printf("Buffer = (nil);",stb->buffer);
	if (*nxln)
		free(*nxln);
	//ft_memset(stb->buffer, 0, stb->buff_siz + 1);
	if (stb->buffer)
		free(stb->buffer);
	stb->buffer = NULL;
	*nxln = NULL;
	stb->flag_err = 1;
}

static int	read_buffer_from_file_descriptor(int fd, t_state *stb)
{
	int	result;

	ft_memset(stb->buffer, 0, stb->buff_siz + 1);
	result = read(fd, stb->buffer, stb->buff_siz);
	if (result == -1)
	{
		ft_memset(stb->buffer, 0, stb->buff_siz + 1);
		stb->flag_err = 1;
		return (0);
	}
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

static int trim_next_line(char **nxln, t_state *stb)
{
	char	*tmp;

	stb->nxln_siz = stb->i_nxl;
	tmp = malloc(sizeof(char) * (stb->nxln_siz + 1));
		if (!tmp)
			return (0);
		ft_memset(tmp, 0, stb->nxln_siz + 1);
		ft_memcpy(tmp, *nxln, stb->nxln_siz);
		free(*nxln);
		*nxln = tmp;
	return (1);
}

static void	read_next_line_from_buffer(char **nxln, t_state *stb)
{
	while (stb->i_buf < stb->buff_siz && stb->buffer[stb->i_buf] && stb->i_nxl < stb->nxln_siz)
	{
		(*nxln)[stb->i_nxl] = stb->buffer[stb->i_buf];
		if (stb->buffer[stb->i_buf] == '\n')
		{
			(*nxln)[++stb->i_nxl] = '\0';
			stb->flag_eol = 1;
			stb->i_buf++;
			if (trim_next_line(nxln, stb))
				return ;
		}
		stb->i_buf++;
		stb->i_nxl++;
	}
	if (!stb->buffer[stb->i_buf])
		stb->flag_eob = 1;
	if (stb->i_nxl >= stb->nxln_siz)
		stb->flag_eonl = 1;
	(*nxln)[stb->i_nxl] = '\0';
	return ;
}

char	*get_next_line(int fd)
{
	static t_state	stb[MAX_INPUTS];
	char			*next_line;

	if (fd < 0 || fd >= MAX_INPUTS || BUFFER_SIZE < 1)
		return (NULL);
	if (!initialize_variables(&next_line, &stb[fd]))
		clean_up_after_error(&next_line, &stb[fd]);
	while (!(stb[fd].flag_eof || stb[fd].flag_err || stb[fd].flag_eol))
	{
		read_next_line_from_buffer(&next_line, &stb[fd]);
		if (stb[fd].flag_eonl)
		{
			if (!init_next_line(&next_line, &stb[fd]))
				clean_up_after_error(&next_line, &stb[fd]);
		}
		if (stb[fd].flag_eob)
		{
			if (!read_buffer_from_file_descriptor(fd, &stb[fd]))
				clean_up_after_error(&next_line, &stb[fd]);
		}
	}
	if (stb[fd].flag_eof && !(stb[fd].i_nxl > 0))
		clean_up_after_error(&next_line, &stb[fd]);
	return (next_line);
}
