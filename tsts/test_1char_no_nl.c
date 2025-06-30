/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_1char_no_nl.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 17:11:55 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/06/29 18:31:41 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"


write_temp_file("temp_1chr_no_nl.txt", "0");

int fd = open("temp_1chr_no_nl.txt", O_RDONLY);
if (fd < 0) {
	perror("open");
	exit(EXIT_FAILURE);
}

