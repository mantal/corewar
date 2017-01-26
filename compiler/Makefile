# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/09 16:55:59 by bel-baz           #+#    #+#              #
#    Updated: 2016/12/19 11:01:08 by tguillem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME=$(shell uname)
PROJECT=COMPILER
NAME=../asm
LIB = ../libft
LIBFT=$(LIB)/libft.a
RED=\033[33;91m
ORANGE=\033[33;93m
AQUA=\033[33;36m
GRAY=\033[33;39m
GREEN=\033[33;32m
BAR=.............................

CFLAGS = -std=c11 -Wall -Wextra -Wconditional-uninitialized -Weverything \
	-Wno-shorten-64-to-32 -Wno-padded -Wno-missing-prototypes \
	-Wno-sign-conversion -pipe -O0 -g3 \
	-I./includes

SRC = main.c reader.c parser.c op_utils.c errors.c instructions_parser.c \
	  utils.c parameters_parser.c validator.c check_instructions.c ft_atoli.c \
	  write_output.c encoder.c parameters_parser_utils.c errors_2.c errors_3.c \
	  op.c
SRCDIR= src
OUTDIR= out
SRCS= $(addprefix $(SRCDIR)/, $(SRC))
OBJ= $(addprefix $(OUTDIR)/, $(SRC:.c=.o))

WORDS = $(words $(SRC))
DIGITS=$(shell echo $$(($(shell echo $(WORDS) | wc -c) - 1)))

all: $(NAME)

$(LIBFT):
	@(cd $(LIB) && $(MAKE) -s);

$(NAME): $(LIBFT) $(OUTDIR) $(OBJ)
	@printf "\r					$(AQUA)[$(GREEN)$(PROJECT)$(AQUA)] %.$(DIGITS)d$(GRAY)/$(AQUA)$(WORDS)$(GRAY) \r[$(GREEN)$(subst .,=,$(BAR))$(GRAY)]\n" $(WORDS)
	@$(CC) -o $(NAME) -I./../libft -L./../libft $(CFLAGS) $(OBJ) -lft

$(OUTDIR)/%.o: $(SRCDIR)/%.c
	@$(eval compteur=$(shell echo $$(($(compteur)+1))))
	@$(eval pd=$(shell echo $$(( ($(compteur) * ($(shell echo $(BAR) | wc -c)  - $(DIGITS))/ $(WORDS))))))
	@printf "\r					$(AQUA)[$(RED)$(PROJECT)$(AQUA)] %.$(DIGITS)d$(GRAY)/$(AQUA)$(WORDS) \r$(GRAY)[$(AQUA)$(BAR)$(GRAY)]" $(compteur)
	@printf "\r					$(AQUA)[$(RED)$(PROJECT)$(AQUA)] %.$(DIGITS)d$(GRAY)/$(AQUA)$(WORDS) \r$(GRAY)[$(GREEN)%.*s>" $(compteur) $(pd) $(subst  .,=,$(BAR))
	@$(CC) -I ../libft -o $@ -c $? $(CFLAGS)

clean:
	@(cd $(LIB) && $(MAKE) $@);
	@rm -f $(OBJ)

$(OUTDIR):
	@mkdir -p $(OUTDIR)

fclean: clean
	@(cd $(LIB) && $(MAKE) $@);
	@rm -f $(NAME)
	@rm -rf $(OUTDIR) $(OUTDIR)

.PHONY: clean fclean re all suicide

re: fclean all

suicide: fclean
	@rm -rf $(SRCDIR)
