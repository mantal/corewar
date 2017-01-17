# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                    +:+ +:+         +:+       #
#    By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+         #
#                                                +#+#+#+#+#+   +#+             #
#    Created: 2013/11/29 09:40:24 by dlancar           #+#    #+#              #
#    Updated: 2016/11/30 18:44:11 by dlancar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= corewar
SRC		= main.c load.c vm.c op.c ex_op.c args_parser.c
OBJ		= $(SRC:.c=.o)
LIB		= ../../libft
INCL	= $(LIB)
LBFLAG	= -lft
CFLAGS  = -std=c11 -Wall -Wextra -Weverything -Wno-unused-parameter\
		  -Wno-shorten-64-to-32 -Wno-padded -Wno-missing-prototypes -Wno-gnu-binary-literal
debug: CFLAGS += -O0 -g3 -fsanitize=address
release: CFLAGS += -O3 -march=native

all: debug

debug: $(NAME)
release: $(NAME)

$(NAME): $(OBJ)
	@(cd $(LIB) && $(MAKE))
	@$(CC) -o $(NAME) $(CFLAGS) -I../includes -I../../libft -L../../libft $(LBFLAG) $(OBJ)

%.o: %.c
	@clang -I ../includes -I $(INCL) -o $@ -c $? $(CFLAGS)

.PHONY: clean fclean re

clean:
	@(cd $(LIB) && $(MAKE) $@)
	@rm -f $(OBJ)

fclean: clean
	@(cd $(LIB) && $(MAKE) $@)
	@rm -f $(NAME)

re: fclean all

suicide: fclean
	@rm -f $(SRC)
