# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-baz <bel-baz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/09 16:55:59 by bel-baz           #+#    #+#              #
#    Updated: 2016/12/19 17:00:40 by bel-baz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME=$(shell uname)
PROJECT=COREWAR
NAME=corewar
LIB =libft
LIBFT=libft/libft.a
COMPILER=asm
VM=corewar

all: $(COMPILER) $(VM)

$(LIBFT):
	@(cd libft && $(MAKE) -s)

$(COMPILER): $(LIBFT)
	@(cd compiler && $(MAKE) -s)

$(VM): $(LIBFT)
	@(cd vm && $(MAKE) -s)

clean:
	@(cd compiler && $(MAKE) $@);
	@(cd libft && $(MAKE) $@);
	@(cd vm && $(MAKE) $@);
	@rm -f $(OBJ)

fclean: clean
	@(cd compiler && $(MAKE) $@);
	@(cd libft && $(MAKE) $@);
	@(cd vm && $(MAKE) $@);

re: fclean all

suicide: fclean
	@(cd compiler && $(MAKE) $@);
	@(cd libft && $(MAKE) $@);
	@(cd vm && $(MAKE) $@);

.PHONY: clean fclean re suicide