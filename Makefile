NAME = game_of_life
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I SDL/include
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(OBJ)
	export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):./
	$(CC) $(OBJ) libsdl2.so $(INCLUDE) -o $(NAME)
