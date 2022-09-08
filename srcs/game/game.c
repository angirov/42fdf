#include "game.h"

void	player_set_location(t_player *player, int x, int y)
{
	player->loc.x = x;
	player->loc.y = y;
}

void	player_move_N(t_player *player)
{
	player->loc.y -= player->speed;
}
void	player_move_S(t_player *player)
{
	player->loc.y += player->speed;
}
void	player_move_E(t_player *player)
{
	player->loc.x += player->speed;
}
void	player_move_W(t_player *player)
{
	player->loc.x -= player->speed;
}

void	player_turn_right(t_player *player)
{
	player->direction -= player->rotation_rate;
}

void	player_turn_left(t_player *player)
{
	player->direction += player->rotation_rate;
}


void	map_set_sizes(t_map *map, int width, int heigth)
{
	map->width = width;
	map->height = heigth;
}