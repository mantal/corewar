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
PROJECT=COMPILER
NAME=asm
LIB = ../common

RED=\033[33;91m
ORANGE=\033[33;93m
AQUA=\033[33;36m
GRAY=\033[33;39m
GREEN=\033[33;32m
BAR=.............................

CFLAGS = -std=c11 -Wall -Wextra -Wconditional-uninitialized -Weverything \
	-Wno-shorten-64-to-32 -Wno-padded -Wno-missing-prototypes \
	-Wno-sign-conversion -pipe -O0 -g3 -fsanitize=address \
	-I./includes

SRC= main.c
SRCDIR= src
OUTDIR= out
SRCS= $(addprefix $(SRCDIR)/, $(SRC))
OBJ= $(addprefix $(OUTDIR)/, $(SRC:.c=.o))

WORDS = $(words $(SRC))
DIGITS=$(shell echo $$(($(shell echo $(WORDS) | wc -c) - 1)))

all: $(NAME)

$(NAME): $(OUTDIR) $(OBJ)
	@printf "\r					$(AQUA)[$(GREEN)$(PROJECT)$(AQUA)] %.$(DIGITS)d$(GRAY)/$(AQUA)$(WORDS)$(GRAY) \r[$(GREEN)$(subst .,=,$(BAR))$(GRAY)]\n" $(WORDS)
	@(cd $(LIB) && $(MAKE) -s);
	@$(CC) -o ../$(NAME) -I./../libft -I./../common/includes -L./../common $(CFLAGS) $(OBJ) -lcommon

$(OUTDIR)/%.o: $(SRCDIR)/%.c
	@$(eval compteur=$(shell echo $$(($(compteur)+1))))
	@$(eval pd=$(shell echo $$(( ($(compteur) * ($(shell echo $(BAR) | wc -c)  - $(DIGITS))/ $(WORDS))))))
	@printf "\r					$(AQUA)[$(RED)$(PROJECT)$(AQUA)] %.$(DIGITS)d$(GRAY)/$(AQUA)$(WORDS) \r$(GRAY)[$(AQUA)$(BAR)$(GRAY)]" $(compteur)
	@printf "\r					$(AQUA)[$(RED)$(PROJECT)$(AQUA)] %.$(DIGITS)d$(GRAY)/$(AQUA)$(WORDS) \r$(GRAY)[$(GREEN)%.*s>" $(compteur) $(pd) $(subst  .,=,$(BAR))
	@$(CC) -I ../libft -I ../common/includes -o $@ -c $? $(CFLAGS)

clean:
	@(cd $(LIB) && $(MAKE) $@);
	@rm -f $(OBJ)

$(OUTDIR):
	@mkdir -p $(OUTDIR)

fclean: clean
	@(cd $(LIB) && $(MAKE) $@);
	@rm -f ../$(NAME)
	@rm -rf $(OUTDIR) $(OUTDIR)

.PHONY: clean fclean re all $(NAME) suicide

re: fclean all

suicide: fclean
	@rm -rf $(SRCDIR)
