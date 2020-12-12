# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/11 04:39:05 by gbourgeo          #+#    #+#              #
#    Updated: 2020/12/12 15:02:59 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = readbin
ARCH =

SYS_NAME := $(shell uname -s)
SYS_ARCH := $(shell uname -m)

ifeq ($(SYS_ARCH), x86)
NAME = readbin32
ARCH = -m32
endif

SRC_DIR = srcs/
HDR_DIR = includes/
OBJ_DIR = objs/

SRC = main.c	\
	print_hex.c	\
	parse_opt.c	\

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

ifeq ($(SYS_NAME), Linux)
ELF_SRC_D = $(SRC_DIR)elf/

ELF_SRC = elf_file_info.c	\
		elf_file_info_32.c	\
		elf_file_info_64.c	\

OBJ += $(addprefix $(OBJ_DIR), $(ELF_SRC:.c=.o))
endif

# ifeq ($(BIT32), 1)
# ASMFLAG		= -f elf32
# endif

ifeq ($(SYS_NAME), Darwin)
MACHO_SRC_D = $(SRC_DIR)macho/
MACHO_SRC = macho_file_info.c		\
			macho_file_info_64.c	\

OBJ += $(addprefix $(OBJ_DIR), $(MACHO_SRC:.c=.o))
endif

LIB_DIR = libft/
LIB_HDR = $(LIB_DIR)includes

WWW 	= gcc $(ARCH)
FLAGS	= -Wall -Werror -Wextra
INCLUDE	= -I$(HDR_DIR) -I$(LIB_HDR)
LIBS	= -L$(LIB_DIR) -lft

all: lib $(NAME)

$(NAME): $(OBJ)
	$(WWW) -o $@ $^ $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)

ifeq ($(SYS_NAME), Linux)
$(OBJ_DIR)%.o: $(ELF_SRC_D)%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)
endif

ifeq ($(SYS_NAME), Darwin)
$(OBJ_DIR)%.o: $(MACHO_SRC_D)%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)
endif

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
