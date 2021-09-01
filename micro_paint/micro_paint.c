#include <stdio.h>
#include <unistd.h>
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

int check_data(t_board *board, t_rectangle *rect, FILE *file)
{
	int check;

	if (fscanf(file, "%d %d %c\n", &board->width, &board->height, &board->color) == 3);
	// if (board->width > 0 && board->width <= 300 
	// 		&& board->height > 0 && board->height <= 300
	// 		&& board->color != NULL)
	printf ("%d %d %c\n", board->width, board->height, board->color);
	return (0);
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
	if ((check_data(&board, &rect, file)) == 1)
		return (str_error("Error: Operation file corrupted\n", 1));

	return (0);
}