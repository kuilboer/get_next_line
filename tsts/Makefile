# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: okuilboe <okuilboe@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/04/25 16:17:43 by okuilboe      #+#    #+#                  #
#    Updated: 2025/06/24 16:43:56 by okuilboe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ==== CONFIG ====

NAME		:= gnltest

LIB_SRC_DIR	:= ../srcs		# default symlink target used if not provided
LIB_LNK_TGT	:= $(CURDIR)/gnl

LIBRARY		= $(LIB_LNK_TGT)/get_next_line.a

CC 			:= cc
CFLAGS		:= -g -O0 #-Wall -Werror -Wextra
CPPFLAGS	:= -I. -Ignl
LDFLAGS 	:= -l:get_next_line.a

# ==== FILES ====

SRCS		:= $(wildcard *.c) $(wildcard utils/*.c)
OBJS		:= $(SRCS:.c=.o)

# ==== RULES =====

.PHONY = all link-lib clean fclean

all: $(LIBRARY) $(NAME)

$(LIBRARY): $(LIB_LNK_TGT)
	@$(MAKE) -C $(LIB_LNK_TGT)

$(LIB_LNK_TGT):
	@echo "re-creating symlink to the target library."
	@ln -snf $(LIB_SRC_DIR) $(LIB_LNK_TGT)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIB_LNK_TGT) $(LDFLAGS) -o $(NAME)

%.o: %.c
	@echo $?
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@

clean:
	@$(MAKE) -C $(LIB_LNK_TGT) clean
	@echo "Purging object files"
	rm -f $(OBJS)


fclean: clean
	@$(MAKE) -C $(LIB_LNK_TGT) fclean
	rm -f $(NAME)
	rm -f $(LIB_LNK_TGT)

re: fclean all

