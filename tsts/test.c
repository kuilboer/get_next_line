/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 10:59:42 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/24 14:08:29 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../srcs/get_next_line.h"

int main(void)
{
	int		fd;
	int		i = 0;
	char	*line;

	if ((fd = open("/home/olaf/dev/olaf/codam/get_next_line/tsts/test_input.txt", O_RDONLY)) == -1)
	{
		printf("File open failed.\n");
		//return (0);
	}
	else
	{
		printf("File handle obtained.\n");
		printf("File descriptor: %d\n", fd);
		printf("data read:\n\n");
	}
	line = get_next_line(fd);
	while (line && i < 100)
	{
		
		printf("line[%3d]: %s\n", i, line);
		if (line)
			free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (0);
}