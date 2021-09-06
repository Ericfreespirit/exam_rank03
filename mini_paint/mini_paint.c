#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_board
{
	int	width;
	int height;
	char color;
}	t_board;

typedef struct s_circle
{
	char id;
	float x;
	float y;
	float radius;
	char color;
} t_circle;

int ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_error(char *str, int ret)
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


int	is_in_circle(float i, float j, t_circle *circle, t_board *board)
{
	float ori_to_rad;
	float distance;
	float ret1;
	float ret2;

	ret1 = (circle->x - 0) * (circle->x - 0);
	ret2 = (circle->y - 0) * (circle->y - 0);

	ori_to_rad = ret1 + ret2;
	distance = ori_to_rad - circle->radius;
	return (0);
}

int ft_circle(t_circle *circle, char *arr, t_board *board)
{
	int	i;
	int	j;
	int ret;

	i = 0;
	if (circle->radius <= 0.0 || (circle->id != 'c' && circle->id != 'C'))
		return (1);
	while(i < board->width)
	{
		j = 0;
		while (j < board->height)
		{
			ret = is_in_circle((float)i, (float)j, circle, board);
			if ((ret == 2 && circle->id == 'C') || ret == 1)
				arr[j * board->width + i] = circle->color;
			j++;
		}
		i++;
	}
	return (0);
}

int launch(t_board *board, t_circle *circle, FILE *file)
{
	int ret;
	char *arr;

	if (ft_board(board, file, &arr))
		return (1);
	ret = fscanf(file, "%c %f %f %f %c\n", &circle->id, &circle->x, &circle->y, &circle->radius, &circle->color);
	while (ret == 6)
	{
		if (ft_circle(circle, arr, board))
			return (1);
		ret = fscanf(file, "%c %f %f %f %c\n", &circle->id, &circle->x, &circle->y, &circle->radius, &circle->color);
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
	t_board board;
	t_circle circle;

	if (ac != 2)
		return (str_error(("Error: argument\n"), 1));
	if ((file = fopen(av[1], "r")) == 0)
		return (str_error("Error: Operation file corrupted\n", 1));
	if ((launch(&board, &circle, file)) == 1)
		return (str_error("Error: Operation file corrupted\n", 1));
	return (0);
}