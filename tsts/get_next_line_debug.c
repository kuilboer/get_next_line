/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_debug.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 15:17:45 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/26 22:23:46 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "test_utils.h"
#include "../get_next_line.h"

// // Your get_next_line() function
// char *get_next_line(int fd);

// Helper that facilitates printing \n character in test title.
void print_escaped(const char *str) {
	while (*str) {
		if (*str == '\n')
			printf("\\n");
		else
			putchar(*str);
		str++;
	}
}

// Helper: decode the input format (e.g., "10\n9") into actual content
void decode(const char *buffer, char *result, size_t maxlen) {
	int offset = 0;
	while (*buffer && offset < (int)(maxlen - 1)) {
		if (*buffer >= '0' && *buffer <= '9') {
			int size = atoi(buffer);
			for (int i = 0; i < size && offset < (int)(maxlen - 1); i++) {
				result[offset] = 'a' + (offset % 26);
				offset++;
			}
			while (*buffer >= '0' && *buffer <= '9') buffer++;
		} else if (*buffer == '\n') {
			result[offset++] = '\n';
			buffer++;
		} else {
			fprintf(stderr, "Invalid encoding: %c\n", *buffer);
			exit(EXIT_FAILURE);
		}
	}
	result[offset] = '\0';
}

// Helper: write to temp file
void write_temp_file(const char *filename, const char *content) {
	FILE *fp = fopen(filename, "w");
	if (!fp) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	fputs(content, fp);
	fclose(fp);
}

// Helper: split decoded string into expected lines
char **split_lines_from_string(const char *str, int *count) {
	char **lines = malloc(1000 * sizeof(char *));
	const char *start = str;
	int idx = 0;

	while (*start) {
		const char *end = strchr(start, '\n');
		if (end) {
			size_t len = end - start + 1; // include the \n
			lines[idx] = malloc(len + 1); // +1 for \0
			memcpy(lines[idx], start, len);
			lines[idx][len] = '\0';
			start = end + 1;
			idx++;
		} else {
			// last line with no newline
			size_t len = strlen(start);
			lines[idx] = malloc(len + 1);
			memcpy(lines[idx], start, len);
			lines[idx][len] = '\0';
			idx++;
			break;
		}
	}

	*count = idx;
	return lines;
}


// One test case
void run_test_case(const char *encoded, int index) {
	printf("==== Test %02d: \"", index + 1);
	print_escaped(encoded);
	printf("\" ====\n");

	char decoded[10000];
	decode(encoded, decoded, sizeof(decoded));

	write_temp_file("temp_test.txt", decoded);

	int fd = open("temp_test.txt", O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	int expected_count = 0;
	char **expected_lines = split_lines_from_string(decoded, &expected_count);

	char *line;
	int lineno = 0;
	int mismatches = 0;

	while ((line = get_next_line(fd)) != NULL) {
		const char *expected = (lineno < expected_count) ? expected_lines[lineno] : "(missing)";
		if (strcmp(line, expected) != 0) {
			printf("❌ Line %2d:\n    Expected: \"%s\"\n    Got     : \"%s\"\n", lineno, expected, line);
			mismatches++;
		} else {
			printf("✅ Line %2d: \"%s\"\n", lineno, line);
		}
		free(line);
		lineno++;
	}

	close(fd);

	// Cleanup expected lines
	for (int i = 0; i < expected_count; i++)
		free(expected_lines[i]);
	free(expected_lines);

	printf("==> %s (%d mismatches)\n", mismatches ? "FAILED ❌" : "PASSED ✅", mismatches);
}

// Entry point
int main(void) {
	const char *tests[] = {
		"9", "9\n", "10", "10\n", "11", "11\n", "19", "19\n", "20", "20\n", "21", "21\n",
		"9\n9\n", "9\n10", "9\n10\n", "10\n8\n", "10\n9", "10\n9\n"
	};

	int total = sizeof(tests) / sizeof(tests[0]);
	for (int i = 0; i < total; i++) {
		run_test_case(tests[i], i);
	}
	test_read_error_case();
	test_multiple_fds();
	test_1char_case();
	return 0;
}
