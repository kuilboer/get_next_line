/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/04 22:26:23 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/16 13:33:11 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 16

# include <stddef.h>

typedef struct s_state
{
	int		flag_eol;
	int 	flag_eob;
	int 	flag_eof;
	size_t	buff_siz;
	size_t	nxln_siz;
	size_t	i_buf;
	size_t	i_nxl;
	char	buffer[BUFFER_SIZE + 1];
} t_state;

char	*get_next_line(int fd);

#endif