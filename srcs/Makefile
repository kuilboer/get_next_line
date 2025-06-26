# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: okuilboe <okuilboe@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/06/04 23:00:59 by okuilboe      #+#    #+#                  #
#    Updated: 2025/06/26 22:25:05 by okuilboe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ==== CONFIG =====

NAME = get_next_line.a

# ==== COMPILER =====

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= #-D BUFFER_SIZE=42
LDFLAGS		:=

# ==== FILES =====

SRCS := 						\
	get_next_line.c				\
	get_next_line_utils.c		\

TSTS :=							\
	tsts/read_wrap.c			\
	tsts/read_error_test.c		\
	tsts/get_next_line_debug.c	\
	tsts/test_multiple_fd.c		\
	tsts/test_1char.c			\


	

OBJS := $(SRCS:.c=.o) 

.PHONY: all lib clean fclean re

bonus: all

test_debug:
	$(CC) -g -O0 $(CFLAGS) $(CPPFLAGS) -D BUFFER_SIZE=10	\
		$(TSTS) $(SRCS) -ldl -I. -o gnl_debug
#	./gnl_debug

all: $(NAME)

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

re: fclean all
