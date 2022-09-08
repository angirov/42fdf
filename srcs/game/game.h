#ifndef GAME_H
# define GAME_H

# include "mlx_api.h"
# include <stdio.h>

typedef struct s_map	t_map;
typedef struct s_game	t_game;

typedef struct s_loc
{
	double	x;
	double	y;
} t_loc;

typedef struct s_player
{
	t_map	*map;
	t_loc	loc;
	float	direction;
	float	rotation_rate;
	double		speed;
}	t_player;

typedef struct s_grid
{
	int	heigth;
	int	width;
	int	scale;
}	t_grid;

typedef struct s_map
{
	t_game		*game;
	t_player	*player;
	t_grid		grid;
	int			px_width;
	int			px_heigth;
}	t_map;

typedef struct s_game
{
	t_map		*map;
	t_graphics	*graphics;
}	t_game;

void	map_set_sizes(t_map *map, int width, int heigth, int scale);
void	player_set_location(t_player *player, t_loc loc);

// void	player_move_forward(t_player *player);
// void	player_move_back(t_player *player);
// void	player_move_right(t_player *player);
// void	player_move_left(t_player *player);
// void	player_turn_right(t_player *player);
// void	player_turn_left(t_player *player);

void	player_move_N(t_player *player);
void	player_move_S(t_player *player);
void	player_move_E(t_player *player);
void	player_move_W(t_player *player);

void	player_turn_right(t_player *player);
void	player_turn_left(t_player *player);
#endif