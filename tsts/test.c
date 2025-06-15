/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 10:59:42 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/12 21:59:42 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "../srcs/get_next_line.h"

char	*find_next_line(int fd)
{
	char 		line[BUFFER_SIZE + 1];
	static char	buff[BUFFER_SIZE + 1];
	static int	i;
	ssize_t		read_cnt;

	read_cnt = read_file(fd, buff);
	buff[read_cnt] = "\0"
	if (read_cnt == '0')
		/*end of file*/
	else if (read_cnt > 0)
		line = assemble_line(buff)
	else
		/*an error has occured*/
		return (NULL);
	return (line)
}

char	*read_file(int fd, char *buffer)
{
	static char buffer[42];
	ssize_t len;

	len = read(fd, buffer, (sizeof(buffer) - 1));
	if (len == -1)
	{
		printf("Error reading file");
		return (-1);
	}
	else
		printf("Read %d bytes of data\n", len);
		return (len);
		
}

int main(void)
{
	int		fd;
	char	*line;

	if ((fd = open("test_input.txt", O_RDONLY)) == -1)
	{
		printf("File open failed.\n");
		return (0);
	}
	else
	{
		printf("File handle obtained.\n");
		printf("File descriptor: %d\n", fd);
	}
	line = find_next_line(fd);
	printf("data read:\n\n %s", line);
	close(fd);
	return (0);
}