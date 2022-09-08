#include "game.h"

void	player_set_location(t_player *player, t_loc loc)
{
	player->loc.x = loc.x;
	player->loc.y = loc.y;
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


void	map_set_sizes(t_map *map, int grid_width, int grid_heigth, int scale)
{
	map->grid.width = grid_width;
	map->grid.heigth = grid_heigth;
	map->grid.scale = scale;
	map->px_width = map->grid.width * map->grid.scale;
	map->px_heigth = map->grid.heigth * map->grid.scale;
}