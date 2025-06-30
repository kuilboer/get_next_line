/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 17:28:55 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/30 19:54:52 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "get_next_line.h"
#include <sys/stat.h>

int main(void)
{
	char *line;

	int fd = open("one_line_no_nl.tekst", O_RDONLY);
	line = get_next_line(fd);
	while(line)
	{
		printf("line = %s\n", line ); fflush(NULL);
		free (line);
		line = get_next_line(fd);
	}
	close(fd);
}