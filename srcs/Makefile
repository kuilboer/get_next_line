# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: okuilboe <okuilboe@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/06/04 23:00:59 by okuilboe      #+#    #+#                  #
#    Updated: 2025/06/30 19:48:07 by okuilboe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ==== CONFIG =====

NAME = get_next_line.a

TSTS_SRC_DIR	:= ../tsts		# default symlink target used if not provided
TSTS_LNK_TGT	:= $(CURDIR)/tsts
TSTS_NAME		:= gnl_debug

# ==== COMPILER =====

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= #-D BUFFER_SIZE=42
LDFLAGS		:=

# ==== FILES =====

SRCS := 						\
	get_next_line.c				\
	get_next_line_utils.c		\

BONUS :=						\
	get_next_line_bonus.c		\
	get_next_line_utils_bonus.c	\

TSTS :=							\
	tsts/read_wrap.c			\
	tsts/read_error_test.c		\
	tsts/get_next_line_debug.c	\
	tsts/test_multiple_fd.c		\
	tsts/test_1char.c			\


	

OBJS := $(SRCS:.c=.o)

.PHONY: all lib clean fclean re

# bonus: all

test_debug: $(TSTS_LNK_TGT)
	$(CC) -g -O0 $(CFLAGS) $(CPPFLAGS) -D BUFFER_SIZE=10	\
		$(TSTS) $(SRCS) -ldl -I. -o $(TSTS_NAME)
#	./gnl_debug

$(TSTS_LNK_TGT):
	@echo "re-creating symlink to the target tester code."
	@ln -snf $(TSTS_SRC_DIR) $(TSTS_LNK_TGT) # Create symbolic link to the libft directory

all: $(NAME) 

bonus:
	@echo "(re-)Creating bonus files." 
	@rm -f *_bonus*
	@cp get_next_line.c get_next_line_bonus.c
	@cp get_next_line.h get_next_line_bonus.h
	@cp get_next_line_utils.c get_next_line_utils_bonus.c
	@sed -i 's/^#ifndef GET_NEXT_LINE_H/#ifndef GET_NEXT_LINE_BONUS_H/; s/^# define GET_NEXT_LINE_H/# define GET_NEXT_LINE_BONUS_H/' get_next_line_bonus.h

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	@echo $?
	$(CC) -c -g -O0 $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) $^ -o $@

clean:
	@echo "Removing object files." 
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(TSTS_LNK_TGT)
	@rm -f $(TSTS_NAME)
	@rm -f *_bonus*
	@rm -f *.txt

re: fclean all

retest: fclean test_debug
