#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// #ifndef VARS
// # define VARS
// int		DIMENTION;
// int		NB_CELLS;
// #endif

#define DIMENTION 1000
#define NB_CELLS 50

#define RAND 0
#define CLEAR 1

typedef enum bool
{
	false,
	true
}bool;

typedef struct s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Event		ev;
	bool			isRunning;
	bool			write;
	struct s_world	*first;
	int				**cells;
	int				**cells_tmp;
	int				x;
	int				y;
}t_sdl;

// main.c

int		main(void);
t_sdl	*define_struct(void);
void	pick_events(t_sdl *gol);
void	render_cells(t_sdl *gol);
int		error(char *str);
void	print_cell(int x, int y, SDL_Renderer *renderer);
void	write_cells_mouse(t_sdl *gol, int cell);

// array.c

int 	**cells_tab(void);
void	free_arr(int **array);
int		nb_neighbours(int **array, int y, int x);
void	copy_array(int **src, int **dst);
void	game_of_life(int **array, int **renderer_tab);
void	fill_with(int **cells, int thing);
