/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_wrap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 12:01:59 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/26 12:02:13 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Global control flag to inject read errors
int next_read_error = 0;

ssize_t read(int fildes, void *buf, size_t nbyte) {
	static ssize_t (*real_read)(int, void *, size_t) = NULL;

	if (!real_read) {
		real_read = dlsym(RTLD_NEXT, "read");
		if (!real_read) {
			fprintf(stderr, "dlsym failed: %s\n", dlerror());
			exit(1);
		}
	}

	fprintf(stderr, ">> read(fd=%d, nbyte=%zu, next_read_error=%d)\n", fildes, nbyte, next_read_error);

	// Enforce BUFFER_SIZE
	#ifdef BUFFER_SIZE
	if (nbyte != BUFFER_SIZE && nbyte != 0) {
		fprintf(stderr, "❌ read size mismatch: expected BUFFER_SIZE = %d, got %zu\n", BUFFER_SIZE, nbyte);
		exit(1);
	}
	#endif

	// Simulate a single read error
	if (next_read_error) {
		next_read_error = 0;
		fprintf(stderr, "⚠️ Injected read() failure\n");
		return -1;
	}

	ssize_t result = real_read(fildes, buf, nbyte);
	fprintf(stderr, "✅ real_read returned %zd bytes\n", result);
	return result;
}
