
#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "parsing.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>


typedef struct s_player_parser
{
	t_pos			pos;
}					t_player_parser;

typedef struct s_map
{
	char			**grid;
	t_pos			size;
}					t_map;

typedef struct s_game_parser
{
	t_player_parser		player;
	t_map			map;
	t_components	*components;
	int				ceiling_color;
	int				floor_color;
}					t_game_parser;

int					get_length(char *array[]);

#endif
