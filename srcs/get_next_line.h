/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/04 22:26:23 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/30 20:33:26 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define MAX_INPUTS 1024

# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/**
 * @brief Represents the state used by get_next_line() for each file descriptor.
 * 
 * Stores internal buffer and status flags to manage state across multiple calls
 * and file descriptors.
 */
typedef struct s_state
{
	int		flag_eonl;		/**< Next_line buffer full.						*/
	int		flag_eol;		/**< End_of_line ('\n') reached in buffer.		*/
	int		flag_eob;		/**< Reached the end of the read buffer.		*/
	int		flag_eof;		/**< Reached EOF in file descriptor.			*/
	int		flag_err;		/**< Allocation or read() error occured.		*/
	int		initialized;	/**< Stops stb from reinit on consecutive runs.	*/
	size_t	buff_siz;		/**< Allocation size of the read buffer 'buffer'*/
	size_t	nxln_siz;		/**< Allocation size of the 'next_line' buffer.	*/
	size_t	i_buf;			/**< Read index for 'buffer'.					*/
	size_t	i_nxl;			/**< Write index for 'next_line'.				*/
	char	*buffer;		/**< Read buffer.								*/
}	t_state;

char	*get_next_line(int fd);
int		initialize_variables(char **next_line, t_state *stb);
int		init_next_line(char **nxln, t_state *stb);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
