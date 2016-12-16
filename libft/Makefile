# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                    +:+ +:+         +:+       #
#    By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+         #
#                                                +#+#+#+#+#+   +#+             #
#    Created: 2013/11/29 09:40:24 by dlancar           #+#    #+#              #
#    Updated: 2016/12/02 18:15:05 by dlancar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT=LIBFT
NAME	= libft.a
LIST = ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
	   ft_lstsize.c ft_lstmap.c ft_lstget.c
GNL =  get_next_line.c resource_manager.c
SRC		= ft_bzero.c ft_memset.c ft_memcpy.c ft_memccpy.c ft_memmove.c 		\
			ft_memchr.c ft_memcmp.c ft_malloc.c								\
																			\
			ft_strdup.c ft_strlen.c										 	\
			ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c 				\
			ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strncmp.c 	\
			ft_strnstr.c ft_strcmp.c ft_strndup.c ft_strclen.c ft_strjoin.c	\
			ft_strtrim.c ft_strchar.c ft_striter.c ft_strmap.c				\
			ft_striteri.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c	\
			ft_strjoinf.c ft_strnjoin.c ft_strnjoinf.c ft_strsplit.c 		\
			ft_strsplitstr.c ft_strisdigit.c ft_strmerge.c ft_strrpl.c		\
																			\
			ft_tolower.c ft_toupper.c ft_isprint.c ft_isascii.c				\
			ft_isdigit.c ft_isalnum.c ft_isalpha.c ft_isspace.c				\
																			\
			ft_putchar.c ft_putchar_fd.c ft_putstr.c ft_putstr_fd.c			\
			ft_putint.c ft_putint_fd.c										\
			ft_putdouble.c ft_putdouble_fd.c ft_printf.c					\
			ft_vprintf.c ft_vprintf_fd.c ft_printf_fd.c ft_asprintf.c 		\
			ft_putubase_fd.c log.c											\
																			\
			ft_atoi.c ft_itoa.c												\
																			\
			ft_math.c ft_vec3.c ft_vec3d.c ft_double.c ft_vec2d.c			\
																			\
			ft_get_next.c													\
																			\
			ft_array.c ft_array_2.c	ft_array_3.c							\
																			\
			error.c															\
																			\
			count_digit.c													\
																			\
			ft_config.c														\
																			\
			socket.c socket_utils.c socket_var.c select.c					\
																			\
			cbuffer.c cbuffer_2.c											\
																			\
			io.c malloc_.c realloc_.c free_.c mem.c							\
																			\
			args.c ft_memalloc.c ft_memdel.c ft_prgm.c				 		\
																			\
			ft_strdel.c	ft_strnew.c endian.c								\
																			\
			$(addprefix get_next_line/, $(GNL)) 							\
			                                                                \
			endianess.c                                                     \
			$(addprefix list/, $(LIST))

OBJ		= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -Weverything -std=c11 -g3 -O0 \
		  -Wno-padded -Wno-pointer-arith -Wno-float-equal -Wno-shorten-64-to-32 -Wno-conversion -Wno-incompatible-pointer-types-discards-qualifiers

RED=\033[33;91m
ORANGE=\033[33;93m
AQUA=\033[33;36m
GRAY=\033[33;39m
GREEN=\033[33;32m
BAR=.............................
WORDS = $(words $(SRC))
DIGITS=$(shell echo $$(($(shell echo $(WORDS) | wc -c) - 1)))

all: $(NAME)

$(NAME): $(OBJ)
	@printf "\r					$(AQUA)[$(GREEN)$(PROJECT)$(AQUA)] %.$(DIGITS)d$(GRAY)/$(AQUA)$(WORDS)$(GRAY) \r[$(GREEN)$(subst .,=,$(BAR))$(GRAY)]\n" $(WORDS)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@$(eval compteur=$(shell echo $$(($(compteur)+1))))
	@$(eval pd=$(shell echo $$(( ($(compteur) * ($(shell echo $(BAR) | wc -c)  - $(DIGITS))/ $(WORDS))))))
	@printf "\r					$(AQUA)[$(RED)$(PROJECT)$(AQUA)] %.$(DIGITS)d$(GRAY)/$(AQUA)$(WORDS) \r$(GRAY)[$(AQUA)$(BAR)$(GRAY)]" $(compteur)
	@printf "\r					$(AQUA)[$(RED)$(PROJECT)$(AQUA)] %.$(DIGITS)d$(GRAY)/$(AQUA)$(WORDS) \r$(GRAY)[$(GREEN)%.*s>" $(compteur) $(pd) $(subst  .,=,$(BAR))
	@$(CC) -o $@ -c $? $(CFLAGS)

.PHONY: clean fclean re

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

suicide: fclean
	@rm -f $(SRC)
