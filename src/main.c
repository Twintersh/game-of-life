#include "../game_of_life.h"

int main(void)
{
	t_sdl	*gol;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (error("SDL failded to initialise : %s\n"));
	gol = define_struct();
	if (gol->window == NULL || gol->renderer == NULL)
		return(error("SDL window or renderer failed to initialise : %s\n"));
	SDL_SetRenderDrawColor(gol->renderer, 0, 0, 0 , 255);
	SDL_RenderClear(gol->renderer);
	SDL_SetRenderDrawColor(gol->renderer, 255, 255, 255, 255);
	SDL_RenderPresent(gol->renderer);
	while (gol->isRunning)
	{
		if (SDL_PollEvent(&gol->ev) != 0)
			pick_events(gol);
		if (gol->write)
			write_cells_mouse(gol, 1);
	}
	SDL_DestroyRenderer(gol->renderer);
	SDL_DestroyWindow(gol->window);
	SDL_Quit();
	free_arr(gol->cells);
	free_arr(gol->cells_tmp);
	free(gol);
	return (0);
}


t_sdl	*define_struct(void)
{
	t_sdl *tmp;

	tmp = malloc(sizeof(t_sdl));
	tmp->window = SDL_CreateWindow("Game Of Life",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		DIMENTION,
		DIMENTION,
		0);
	tmp->renderer = SDL_CreateRenderer(tmp->window, 0, 0);
	tmp->cells = cells_tab();
	tmp->cells_tmp = cells_tab();
	tmp->write = false;
	tmp->isRunning = true;
	tmp->x = DIMENTION / 2;
	tmp->y = DIMENTION / 2;
	return (tmp);
}


void	pick_events(t_sdl *gol)
{
	switch (gol->ev.type)
	{
		case SDL_QUIT :
			gol->isRunning = 0;
			break ;
		case SDL_MOUSEBUTTONDOWN :
			if (gol->ev.button.button == SDL_BUTTON_RIGHT)
				write_cells_mouse(gol, 0);
			else
				gol->write = true;
			break ;
		case SDL_MOUSEBUTTONUP :
			gol->write = false;
			break ;
		case SDL_KEYDOWN :
			if (gol->ev.key.keysym.sym == 'r')
				fill_with(gol->cells, RAND);
			else if (gol->ev.key.keysym.sym == 'c')
				fill_with(gol->cells, CLEAR);
			else
				game_of_life(gol->cells_tmp, gol->cells);
			break ;
		default :
			return ;
	}
	render_cells(gol);
	SDL_RenderPresent(gol->renderer);
}

void	render_cells(t_sdl *gol)
{
	int x = 0, y = 0;

	while (y < NB_CELLS)
	{
		x = 0;
		while (x < NB_CELLS)
		{
			if (gol->cells[x][y] % 2)
				SDL_SetRenderDrawColor(gol->renderer, 255, 255, 255, 255);
			else
				SDL_SetRenderDrawColor(gol->renderer, 0, 0, 0, 255);
			print_cell(x * DIMENTION / NB_CELLS, y * DIMENTION / NB_CELLS, gol->renderer);
			x++;
		}
		y++;
	}
}

int	error(char *str)
{
	fprintf(stderr, str, SDL_GetError());
	return (1);
}

void	print_cell(int x, int y, SDL_Renderer *renderer)
{
	SDL_Rect r = {x, y, DIMENTION / NB_CELLS, DIMENTION / NB_CELLS};
	SDL_RenderFillRect(renderer, &r);
}

void	write_cells_mouse(t_sdl *gol, int cell)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	gol->cells[x / (DIMENTION / NB_CELLS)][y / (DIMENTION / NB_CELLS)] = cell;
	render_cells(gol);
	SDL_RenderPresent(gol->renderer);
}
