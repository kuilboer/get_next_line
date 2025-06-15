/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_new.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 14:48:51 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/07 09:05:44 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>

char	*get_next_line(int fd)
{
	static t_state	stb[1024];
	char			*next_line;

	stb[fd] = (t_state){0};
	if (!init_next_line(&stb[fd]))
		return (NULL);
	while(!stb[fd].flag_eof)
	{
		while (!stb[fd].flag_eob && )
		{
			while (!stb[fd].flag_eob)
			{
				read_from_buffer(&stb);
				if (stb[fd].flag_eol)
					stb[fd].flag_eol = 0;
					return (&next_line);
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
