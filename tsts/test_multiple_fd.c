/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_multiple_fd.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 16:44:21 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/26 17:15:01 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "test_utils.h"

// Declare your function
char *get_next_line(int fd);

int assert_line(const char *label, int step, const char *actual, const char *expected) {
	if ((actual == NULL && expected != NULL) ||
		(actual != NULL && expected == NULL) ||
		(actual && expected && strcmp(actual, expected) != 0)) {
		printf("❌ %d. %s: Expected \"%s\", Got \"%s\"\n", step, label,
		       expected ? expected : "NULL",
		       actual ? actual : "NULL");
		return 1;
	} else {
		printf("✅ %d. %s: \"%s\"\n", step, label, actual ? actual : "NULL");
		return 0;
	}
}

void test_multiple_fds(void) {
	printf("\n==== Test Suite: multiple FDs ====\n");

	const char *file_a = "/tmp/file_a.txt";
	const char *file_b = "/tmp/file_b.txt";
	const char *file_c = "/tmp/file_c.txt";

	write_temp_file(file_a, "aaa\nbbb\nccc\n");
	write_temp_file(file_b, "111\n222\n");
	write_temp_file(file_c, "xxx\nyyy\nzzz\n");

	int fda = open(file_a, O_RDONLY);
	int fdb = open(file_b, O_RDONLY);
	int fdc = open(file_c, O_RDONLY);
	if (fda < 0 || fdb < 0 || fdc < 0) {
		perror("open for reading");
		exit(EXIT_FAILURE);
	}

	const char *expected[] = {
		"aaa\n", "111\n", "xxx\n",
		"bbb\n", "222\n", "yyy\n",
		"ccc\n", NULL,    "zzz\n",
		NULL,   NULL,    NULL
	};

	int fds[] = { fda, fdb, fdc };
	const char *labels[] = { "fda", "fdb", "fdc" };

	int total = sizeof(expected) / sizeof(expected[0]);
	int mismatches = 0;

	for (int i = 0; i < total; i++) {
		char *line = get_next_line(fds[i % 3]);
		mismatches += assert_line(labels[i % 3], i + 1, line, expected[i]);
		free(line);
	}

	close(fda);
	close(fdb);
	close(fdc);
	unlink(file_a);
	unlink(file_b);
	unlink(file_c);

	printf("\n==> Multi-FD Test %s\n", mismatches ? "FAILED ❌" : "PASSED ✅");
}
