# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/11 04:39:05 by gbourgeo          #+#    #+#              #
#    Updated: 2020/11/18 20:12:42 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= readbin
ARCH	=
ifeq ($(BIT32), 1)
NAME	= readbin32
ARCH	= -m32
endif

UNAME_S	:= $(shell uname -s)
UNAME_M := $(shell uname -m)

ifeq ($(UNAME_S), Linux)
SRC_D		= elf/
SRC		= main.c			\
		elf_file_info_32.c	\
		elf_file_info_64.c	\
		elf_file_info_opt.c	\
		print_hex.c			\

ifeq ($(BIT32), 1)
ASMFLAG		= -f elf32
endif
endif

ifeq ($(UNAME_S), Darwin)
SRC_D		= macho
SRC		= macho_file_info.c
endif

SRC_DIR	= $(SRC_D)srcs/
HDR_DIR	= $(SRC_D)includes/
OBJ_DIR	= $(SRC_D)obj/
OBJ	= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIB_DIR	= libft/
LIB_HDR	= $(LIB_DIR)includes

WWW 	= gcc $(ARCH)
FLAGS	= -Wall -Werror -Wextra
INCLUDE	= -I$(HDR_DIR) -I$(LIB_HDR)
LIBS	= -L$(LIB_DIR) -lft

all: lib $(NAME)

$(NAME): $(OBJ) $(OBJ_S)
	$(WWW) -o $@ $^ $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)

.PHONY: lib clean fclean re

lib:
	@make ARCH=$(ARCH) -C $(LIB_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	@make -C $(LIB_DIR) clean
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean
	/bin/rm -f $(NAME)

re: fclean all
