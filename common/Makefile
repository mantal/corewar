# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/09 16:55:59 by bel-baz           #+#    #+#              #
#    Updated: 2016/12/09 16:56:00 by bel-baz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME=$(shell uname)
PROJECT= COREWAR
NAME=libcommon.a
LIB = ../libft

CFLAGS = -std=c11 -Wall -Wextra -Wconditional-uninitialized -Weverything \
	-Wno-shorten-64-to-32 -Wno-padded -Wno-missing-prototypes \
	-Wno-sign-conversion -pipe -O0 -g3 \
	-I./includes

SRC = op.c
SRCDIR = src
OUTDIR= out/
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJ = $(addprefix $(OUTDIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OUTDIR) $(OBJ)
	@(cd $(LIB) && $(MAKE));
	@ar rc $(NAME) $(OBJ) $(LIB)/*.o
	@ranlib $(NAME)

$(OUTDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -I $(LIB) -o $@ -c $? $(CFLAGS)

clean:
	@(cd $(LIB) && $(MAKE) $@);
	@rm -f $(OBJ)

$(OUTDIR):
	@mkdir -p $(OUTDIR)

fclean: clean
	@(cd $(LIB) && $(MAKE) $@);
	@rm -f $(NAME)
	@rm -rf $(OUTDIR)

.PHONY: clean fclean re suicide

re: fclean all

suicide: fclean
	@rm -rf $(SRCDIR)
