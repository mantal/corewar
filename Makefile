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
COMMON=common/libcommon.a
COMPILER=asm
VM=corewar

all: $(COMPILER) $(VM)

$(COMMON):
	@(cd common && $(MAKE) -s)

$(COMPILER): $(COMMON)
	@(cd compiler && $(MAKE) -s)

$(VM): $(COMMON)
	@(cd vm && $(MAKE) -s)

clean:
	@(cd compiler && $(MAKE) $@);
	@(cd common && $(MAKE) $@);
	@(cd vm && $(MAKE) $@);
	@rm -f $(OBJ)

fclean: clean
	@(cd compiler && $(MAKE) $@);
	@(cd common && $(MAKE) $@);
	@(cd vm && $(MAKE) $@);

re: fclean all

suicide: fclean
	@(cd compiler && $(MAKE) $@);
	@(cd common && $(MAKE) $@);
	@(cd vm && $(MAKE) $@);

.PHONY: clean fclean re suicide