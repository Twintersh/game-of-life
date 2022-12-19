
CC = gcc
NAME = game_of_life
SRC = src/main.c src/array.c
OBJ=$(SRC:.c=.o)
CFLAGS = -Werror -Wall -Wextra -g
LFLAGS = `sdl2-config --cflags --libs`

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

re : fclean all

clean :
	@rm -rf $(OBJ)
	@echo Done

fclean : clean
	@rm -rf $(NAME)

.PHONY : clean re fclean all
