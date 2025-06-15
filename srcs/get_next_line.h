/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/04 22:26:23 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/06 17:28:16 by okuilboe      ########   odam.nl         */
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
	int		read_cnt;
	size_t	buff_siz;
	size_t	i_buf;
	size_t	i_rst;
	size_t	i_nxl;
	char	buffer[BUFFER_SIZE + 1];
	char	*next_lin;
	size_t	next_lin_siz;
	char	*buf_rest;
} t_state;

char	*get_next_line(int fd);

#endif