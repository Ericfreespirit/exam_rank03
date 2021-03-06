#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
typedef struct s_board
{
	int	width;
	int height;
	char color;
}	t_board;

typedef struct s_rectangle
{
	char id;
	float x;
	float y;
	float width;
	float height;
	char color;
} t_rectangle;


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

int str_error(char *str, int ret)
{
	write(1, str, ft_strlen(str));
	return (ret);
}

void draw(char *arr, t_board *board)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(j < board->height)
	{
		i = 0;
		while (i < board->width)
		{
			write(1, &arr[j * board->width + i], 1);
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
}

int	ft_board(t_board *board, FILE *file, char **arr)
{
	int	len;

	if (fscanf(file, "%d %d %c\n", &board->width, &board->height, &board->color) == 3)
	{
		if (board->width > 0 && board->width <= 300 
		&& board->height > 0 && board->height <= 300)
		{
			len = board->width * board->height;
			*arr = malloc(sizeof(char *) * (len + 1));
			if (arr == NULL)
				return (1);
			memset(*arr, board->color, len);
			(*arr)[len] = '\0';
			return (0);
		}
	}
	return (1);
}

int is_in_rect(float i, float j, t_rectangle *rect, t_board *board)
{

	if (i < rect->x || i > rect->x + rect->width || j < rect->y || j > rect->y + rect->height)
		return (0);
	//Border
	if ((i - rect->x <  1.00000000 || (rect->width + rect->x) - i <  1.00000000
			|| j - rect->y <  1.00000000 || (rect->height + rect->y) - j <  1.00000000))
		return (1);
	//Inside
	return (2);
}

int ft_rect(t_rectangle *rect, char *arr, t_board *board)
{
	int	i;
	int	j;
	int ret;

	i = 0;
	if (rect->width <= 0.0 || rect->height <= 0.0 || (rect->id != 'r' && rect->id != 'R'))
		return (1);
	while(i < board->width)
	{
		j = 0;
		while (j < board->height)
		{
			ret = is_in_rect((float)i, (float)j, rect, board);
			if ((ret == 2 && rect->id == 'R') || ret == 1)
				arr[j * board->width + i] = rect->color;
			j++;
		}
		i++;
	}
	return (0);
}

int launch(t_board *board, t_rectangle *rect, FILE *file)
{
	int ret;
	char *arr;

	if (ft_board(board, file, &arr))
		return (1);
	ret = fscanf(file, "%c %f %f %f %f %c\n", &rect->id, &rect->x, &rect->y, &rect->width, &rect->height, &rect->color);
	while (ret == 6)
	{
		if (ft_rect(rect, arr, board))
			return (1);
		ret = fscanf(file, "%c %f %f %f %f %c\n", &rect->id, &rect->x, &rect->y, &rect->width, &rect->height, &rect->color);
	}
	if (ret == -1)
	{
		draw(arr, board);
		return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
	FILE *file;
	t_board	board;
	t_rectangle rect;

	if (ac != 2)
		return (str_error(("Error: argument\n"), 1));
	if ((file = fopen(av[1], "r")) == 0)
		return (str_error("Error: Operation file corrupted\n", 1));
	if ((launch(&board, &rect, file)) == 1)
		return (str_error("Error: Operation file corrupted\n", 1));
	return (0);
}