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
PROJECT= COREWAR
NAME=corewar
LIB = libft

all: compiler corewar

common/libcommon.a:
	@(cd common && $(MAKE) -s)

asm: common
	@(cd compiler && $(MAKE) -s)

corewar: common
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

.PHONY: clean fclean re all

re: fclean all

suicide: fclean
	@(cd compiler && $(MAKE) $@);
	@(cd common && $(MAKE) $@);
	@(cd vm && $(MAKE) $@);
