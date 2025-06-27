/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_1char.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 22:20:01 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/26 22:29:32 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *get_next_line(int fd);

void test_1char_case(void)
{
	const char *filename = "1char_tmp.txt";
	const char *content = "0"; // single character, no newline

	// Write test content to a temp file
	write_temp_file(filename, content);

	// Open for reading
	int fd = open(filename, O_RDONLY);
	if (fd < 0) { perror("open for read"); exit(1); }

	printf("\n==== Custom Test: 1char.txt equivalent ====");

	char *line = get_next_line(fd);
	if (line == NULL)
		printf("\n❌ Test 1: Expected \"0\" but got NULL\n");
	else if (strcmp(line, "0") == 0)
		printf("\n✅ Test 1: Got expected line \"%s\"\n", line);
	else
		printf("\n❌ Test 1: Unexpected result \"%s\"\n", line);
	free(line);

	line = get_next_line(fd);
	if (line == NULL)
		printf("✅ Test 2: Got NULL as expected on second call\n");
	else {
		printf("❌ Test 2: Expected NULL but got \"%s\"\n", line);
		free(line);
	}

	close(fd);
	unlink(filename); // clean up
}
