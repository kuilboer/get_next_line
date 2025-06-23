# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: okuilboe <okuilboe@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/06/04 23:00:59 by okuilboe      #+#    #+#                  #
#    Updated: 2025/06/23 22:10:43 by okuilboe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ==== CONFIG =====

NAME = get_next_line.a

# ==== COMPILER =====

CC			:= cc
CFLAGS		:= -g -Wall -Wextra -Werror
CPPFLAGS	:= -D BUFFER_SIZE=42
LDFLAGS		:=

# ==== FILES =====

SRCS := 					\
	get_next_line.c			\
	get_next_line_utils.c	\

OBJS := $(SRCS:.c=.o) 

.PHONY: all lib clean fclean re

bonus: all

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
