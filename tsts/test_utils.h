/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_utils.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 17:08:55 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/26 22:24:24 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// tsts/test_utils.h
#ifndef TEST_UTILS_H
# define TEST_UTILS_H

void write_temp_file(const char *filename, const char *content);

// Read error test cases
void test_read_error_case(void);

// Read from multiple file descriptors
void test_multiple_fds(void);

// test single character actions
void test_1char_case(void);

// Global variable signifying to emulate a read error on the next test.
extern int next_read_error;

#endif