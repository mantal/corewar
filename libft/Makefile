# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                    +:+ +:+         +:+       #
#    By: dlancar <dlancar@student.42.fr>            +#+  +:+       +#+         #
#                                                +#+#+#+#+#+   +#+             #
#    Created: 2013/11/29 09:40:24 by dlancar           #+#    #+#              #
#    Updated: 2017/01/27 12:55:07 by tguillem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
LIST = ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
	   ft_lstsize.c ft_lstmap.c ft_lstget.c ft_lstpushback.c
SRC		= ft_bzero.c ft_memset.c ft_memcpy.c ft_memccpy.c ft_memmove.c 		\
			ft_memchr.c ft_memcmp.c ft_malloc.c								\
																			\
			ft_strdup.c ft_strlen.c										 	\
			ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c 				\
			ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strncmp.c 	\
			ft_strnstr.c ft_strcmp.c ft_strndup.c ft_strclen.c ft_strjoin.c	\
			ft_strtrim.c ft_strchar.c ft_striter.c ft_strmap.c ft_strnchr.c	\
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
			ft_vprintf.c ft_vprintf_fd.c ft_printf_fd.c 			 		\
			ft_putubase_fd.c log.c											\
																			\
			ft_atoi.c ft_itoa.c												\
																			\
			ft_math.c ft_vec3.c ft_vec3d.c ft_double.c ft_vec2d.c			\
																			\
			ft_get_next.c get_next.c										\
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
			args.c ft_memalloc.c ft_memdel.c ft_prgm.c ft_strdel.c          \
			ft_strnew.c endian.c endianess.c $(addprefix list/, $(LIST))

OBJ		= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -Werror -std=c11

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@$(CC) -I./ -o $@ -c $? $(CFLAGS)

.PHONY: clean fclean re

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

suicide: fclean
	@rm -f $(SRC)
