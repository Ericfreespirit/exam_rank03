#include <stdio.h>
#include <unistd.h>
#include <string.h>
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

int	launch_board(t_board *board, FILE *file, char **arr)
{
		if (fscanf(file, "%d %d %c\n", &board->width, &board->height, &board->color) == 3)
		{
			if (board->width > 0 && board->width <= 300 
			&& board->height > 0 && board->height <= 300)
			{
				*arr = malloc(sizeof(char *) * ((board->width * board->height) + 1));
				if (arr == NULL)
					return (1);
				strcpy(**arr, "hello");
				return (0);
			}
		}
	return (1);
}

int launch_rect(t_rectangle *rect, FILE *file)
{
	if (rect->width > 0.0 && rect->height > 0.0 && (rect->id == 'r' || rect->id == 'R'))
		return (0);
	return (1);
}

int launch(t_board *board, t_rectangle *rect, FILE *file)
{
	int ret;
	char *arr;

	if (launch_board(board, file, &arr))
		return (1);
	printf("%s\n", arr);
	ret = fscanf(file, "%c %f %f %f %f %c\n", &rect->id, &rect->x, &rect->y, &rect->width, &rect->height, &rect->color);
	while (ret == 6)
	{
		if (launch_rect(rect, file))
			return (1);
		ret = fscanf(file, "%c %f %f %f %f %c\n", &rect->id, &rect->x, &rect->y, &rect->width, &rect->height, &rect->color);
	}
	if (ret == -1)
		return (0);
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