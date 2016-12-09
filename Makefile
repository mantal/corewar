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
NAME=corewar
LIB1 = libft

RED=\033[33;91m
ORANGE=\033[33;93m
AQUA=\033[33;36m
GRAY=\033[33;39m
GREEN=\033[33;32m
BAR=.............................

CFLAGS = -std=c11 -Wall -Wextra -Wconditional-uninitialized -Weverything \
	-Wno-shorten-64-to-32 -Wno-padded -Wno-missing-prototypes \
	-Wno-sign-conversion -Wno-sign-compare -pipe -O0 -g3 -fsanitize=address \
	-I./includes

SRC = main.c
ASMSRC = asm.c $(SRC)
CORSRC = corewar.c $(SRC)
SRCDIR = src
ASMOUTDIR= out/asm
COROUTDIR= out/corewar
ASMSRCS = $(addprefix $(SRCDIR)/, $(ASMSRC))
CORSRCS = $(addprefix $(SRCDIR)/, $(CORSRC))
ASMOBJ = $(addprefix $(ASMOUTDIR)/, $(ASMSRC:.c=.o))
COROBJ = $(addprefix $(COROUTDIR)/, $(CORSRC:.c=.o))

ASMWORDS = $(words $(ASMSRC))
CORWORDS = $(words $(CORSRC))
ASMDIGITS=$(shell echo $$(($(shell echo $(ASMWORDS) | wc -c) - 1)))
CORDIGITS=$(shell echo $$(($(shell echo $(CORWORDS) | wc -c) - 1)))

all: asm corewar

asm: $(ASMOUTDIR) $(ASMOBJ)
	@printf "\r					$(AQUA)[$(GREEN)ASM$(AQUA)] %.$(ASMDIGITS)d$(GRAY)/$(AQUA)$(ASMWORDS)$(GRAY) \r[$(GREEN)$(subst .,=,$(BAR))$(GRAY)]\n" $(ASMWORDS)
	@(cd $(LIB1) && $(MAKE) -s);
	@$(CC) -o asm -I./libft/includes -L./libft $(CFLAGS) $(ASMOBJ) -lft

corewar: $(COROUTDIR) $(COROBJ)
	@printf "\r					$(AQUA)[$(GREEN)COREWAR$(AQUA)] %.$(CORDIGITS)d$(GRAY)/$(AQUA)$(CORWORDS)$(GRAY) \r[$(GREEN)$(subst .,=,$(BAR))$(GRAY)]\n" $(CORWORDS)
	@(cd $(LIB1) && $(MAKE) -s);
	@$(CC) -o corewar -I./libft/includes -L./libft $(CFLAGS) $(COROBJ) -lft

$(ASMOUTDIR)/%.o: $(SRCDIR)/%.c
	@$(eval compteur=$(shell echo $$(($(compteur)+1))))
	@$(eval pd=$(shell echo $$(( ($(compteur) * ($(shell echo $(BAR) | wc -c)  - $(ASMDIGITS))/ $(ASMWORDS))))))
	@printf "\r					$(AQUA)[$(RED)ASM$(AQUA)] %.$(ASMDIGITS)d$(GRAY)/$(AQUA)$(ASMWORDS) \r$(GRAY)[$(AQUA)$(BAR)$(GRAY)]" $(compteur)
	@printf "\r					$(AQUA)[$(RED)ASM$(AQUA)] %.$(ASMDIGITS)d$(GRAY)/$(AQUA)$(ASMWORDS) \r$(GRAY)[$(GREEN)%.*s>" $(compteur) $(pd) $(subst  .,=,$(BAR))
	@$(CC) -I $(LIB1)/includes -o $@ -c $? $(CFLAGS)

$(COROUTDIR)/%.o: $(SRCDIR)/%.c
	@$(eval compteur=$(shell echo $$(($(compteur)+1))))
	@$(eval pd=$(shell echo $$(( ($(compteur) * ($(shell echo $(BAR) | wc -c)  - $(CORDIGITS))/ $(CORWORDS))))))
	@printf "\r					$(AQUA)[$(RED)COREWAR$(AQUA)] %.$(DIGITS)d$(GRAY)/$(AQUA)$(CORWORDS) \r$(GRAY)[$(AQUA)$(BAR)$(GRAY)]" $(compteur)
	@printf "\r					$(AQUA)[$(RED)COREWAR$(AQUA)] %.$(DIGITS)d$(GRAY)/$(AQUA)$(CORWORDS) \r$(GRAY)[$(GREEN)%.*s>" $(compteur) $(pd) $(subst  .,=,$(BAR))
	@$(CC) -I $(LIB1)/includes -o $@ -c $? $(CFLAGS)

clean:
	@(cd $(LIB1) && $(MAKE) $@);
	@rm -f $(OBJ)

$(ASMOUTDIR):
	@mkdir -p $(ASMOUTDIR)

$(COROUTDIR):
	@mkdir -p $(COROUTDIR)

fclean: clean
	@(cd $(LIB1) && $(MAKE) $@);
	@rm -f $(NAME)
	@rm -f asm corewar
	@rm -rf $(ASMOUTDIR) $(COROUTDIR)

.PHONY: clean fclean re all $(NAME) debug release suicide asm corewar

re: fclean all

suicide: fclean
	@rm -rf $(SRCDIR)
