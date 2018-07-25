# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/13 17:45:03 by dotmauws          #+#    #+#              #
#    Updated: 2018/07/25 09:54:42 by wseegers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ray2d
CC = clang
#CFLAGS = -Werror -Wall -Wextra 
CFLAGS =
INC = -I toolkit-wtc/include
LIB = -Ltoolkit-wtc -lwtcc -lwtcfx

SRC_PATH = src
ALL_SRC = $(wildcard src/*.c)
SRC = $(ALL_SRC:src/%=%)
BIN_PATH = bin
BIN := $(SRC:%.c=$(BIN_PATH)/%.o)
DOS := $(sh uname)EP := $(BIN:%.o=%.d)
OS := $(shell uname)

ifeq ($(OS), Darwin)
	LFLAGS = -lmlx -framework OpenGL -framework AppKit
else
	LFLAGS = -lmlx -lXext -lX11 -lm
endif

all : make_LIB $(NAME)
	@echo "wseegers" > author

make_LIB :
	make -C toolkit-wtc

$(NAME) : $(BIN)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(LFLAGS) $(LIB)

$(BIN_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(BIN_PATH)
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

-include $(DEP)

clean :
	rm -rf $(BIN_PATH)

fclean : clean
	rm -f $(NAME)
	make fclean -C toolkit-wtc

re : fclean all

.PHONEY : usage all make_all  clean  fclean  re