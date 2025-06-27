/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_error_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 09:52:11 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/26 11:41:06 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Declare get_next_line prototype
char *get_next_line(int fd);

// External variable to control read mock
extern int next_read_error;

void test_gnl(int fd, const char *expected, int index) {
	char *line = get_next_line(fd);
	fprintf(stderr, "==> test_gnl(%d): next_read_error = %d\n", index, next_read_error);

	if ((line == NULL && expected != NULL) ||
		(line != NULL && expected == NULL) ||
		(line && expected && strcmp(line, expected) != 0)) {

		printf("❌ Test %d:\n", index);
		printf("    Expected: \"%s\"\n", expected ? expected : "NULL");
		printf("    Got     : \"%s\"\n", line ? line : "NULL");

		if (next_read_error == 0 && expected != NULL) {
			fprintf(stderr, "\033[33mProbable reason\033[0m: static buffer not cleared after read() error\n");
		}
	} else {
		printf("✅ Test %d: \"%s\"\n", index, line ? line : "NULL");
	}
	free(line);
}

void test_read_error_case(void) {
	printf("\n==== Test Suite: read_error.txt ====\n");

	const char *filename = "tsts/read_error.txt";
	int fd = open(filename, O_RDONLY);
	printf("Opened %s -> fd = %d\n", filename, fd);
	if (fd < 0) {
		perror("open");
		return;
	}

	/* 1 */ test_gnl(fd, "aaaaaaaaaa\n", 1);
	/* 2 */ test_gnl(fd, "bbbbbbbbbb\n", 2);

	// Inject a read() error
	next_read_error = 1;

	// Skip flush logic for BUFFER_SIZE <= 100
	#if BUFFER_SIZE > 100
	char *tmp;
	do {
		tmp = get_next_line(fd);
		free(tmp);
	} while (tmp != NULL);
	#endif

	/* 3 */ test_gnl(fd, NULL, 3);

	next_read_error = 0;
	close(fd);

	fd = open(filename, O_RDONLY);

	/* 4–8: Retest everything from a clean file descriptor */
	/* 4 */ test_gnl(fd, "aaaaaaaaaa\n", 4);
	/* 5 */ test_gnl(fd, "bbbbbbbbbb\n", 5);
	/* 6 */ test_gnl(fd, "cccccccccc\n", 6);
	/* 7 */ test_gnl(fd, "dddddddddd\n", 7);
	/* 8 */ test_gnl(fd, NULL, 8);

	close(fd);
}
