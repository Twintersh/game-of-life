#include "../game_of_life.h"

int **cells_tab(void)
{
	int	**array;
	int	i;
	int j;

	i = 0;
	array = malloc(sizeof(int *) * NB_CELLS);
	while (i < NB_CELLS)
	{
		array[i] = malloc(sizeof(int *) * NB_CELLS);
		i++;
	}
	i = 0;
	while (i < NB_CELLS)
	{
		j = 0;
		while (j < NB_CELLS)
		{
			array[i][j] = 0;
			j++;
		}
		i++;
	}
	return (array);
}

void	free_arr(int **array)
{
	int i;

	i = 0;
	while (i <= NB_CELLS)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	nb_neighbours(int **array, int y, int x)
{
	int neighbours = 0;

	if (y != (NB_CELLS - 1) && x != (NB_CELLS - 1))
		neighbours += array[y + 1][x + 1] % 2;
	if (y != (NB_CELLS - 1))
		neighbours += array[y + 1][x] % 2;
	if (y != (NB_CELLS - 1) && x != 0)
		neighbours += array[y + 1][x - 1] % 2;
	if (y != 0 && x != (NB_CELLS - 1))
		neighbours += array[y - 1][x + 1] % 2;
	if (y != 0)
		neighbours += array[y - 1][x] % 2;
	if (y != 0 && x != 0)
		neighbours += array[y - 1][x - 1] % 2;
	if (x != (NB_CELLS - 1))
		neighbours += array[y][x + 1] % 2;
	if (x != 0)
		neighbours += array[y][x - 1] % 2;
	return (neighbours);
}

void	copy_array(int **src, int **dst)
{
	int i = 0, j;

	while (i < NB_CELLS)
	{
		j = 0;
		while (j < NB_CELLS)
		{
			dst[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}

void	game_of_life(int **array, int **renderer_tab)
{
	int i = 0, j = 0;
	int neighbours;

	copy_array(renderer_tab, array);
	while (i < NB_CELLS)
	{
		j = 0;
		while (j < NB_CELLS)
		{
			neighbours = nb_neighbours(renderer_tab, i, j);
			if (renderer_tab[i][j] % 2)
			{
				if (neighbours < 2 || neighbours > 3)
					array[i][j]++;
			}
			else
			{
				if (neighbours == 3)
					array[i][j]++;
			}
			j++;
		}
		i++;
	}
	copy_array(array, renderer_tab);
}

void	fill_with(int **cells, int thing)
{
	int i, j;

	i = 0;
	while (i < NB_CELLS)
	{
		j = 0;
		while (j < NB_CELLS)
		{
			switch (thing)
			{
				case RAND :
					cells[i][j] = rand() % 2;
					break;
				case CLEAR :
					cells[i][j] = 0;
					break;
			}
			j++;
		}
		i++;
	}
}
