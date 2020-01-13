# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/19 14:04:50 by rabduras          #+#    #+#              #
#    Updated: 2019/11/28 16:20:32 by rabduras         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra -Iincludes
NAME = libft.a

LIBC = ft_atoi ft_bzero ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint \
	ft_memccpy ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_strcat ft_strchr \
	ft_strcmp ft_strcpy ft_strdup ft_strlcat ft_strlen ft_strncat ft_strncmp ft_strncpy \
	ft_strnstr ft_strrchr ft_strstr ft_tolower ft_toupper
ADDITIONAL = ft_itoa ft_memalloc ft_memdel ft_putchar_fd ft_putchar ft_putendl_fd \
	ft_putendl ft_putnbr_fd ft_putnbr ft_putstr_fd ft_putstr ft_strclr ft_strdel ft_strequ \
	ft_striter ft_striteri ft_strjoin ft_strmap ft_strmapi ft_strnequ ft_strnew ft_strsplit \
	ft_strsub ft_strtrim
BONUS = ft_lstadd ft_lstdel ft_lstdelone ft_lstiter ft_lstmap ft_lstnew
EXTRA = ft_islower ft_isspace ft_isuppper ft_strconcat ft_lstfold get_next_line

LIBC_A = $(patsubst %, libc_functions/%, $(addsuffix .c, $(LIBC)))
ADDITIONAL_A = $(patsubst %, additional_functions/%, $(addsuffix .c, $(ADDITIONAL)))
BONUS_A = $(patsubst %, bonus_part/%, $(addsuffix .c, $(BONUS)))
EXTRA_A = $(patsubst %, extra_functions/%, $(addsuffix .c, $(EXTRA)))

SRCS = $(LIBC_A) $(ADDITIONAL_A) $(BONUS_A) $(EXTRA_A)

OBJS = $(SRCS:.c=.o)

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

all: $(NAME)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
