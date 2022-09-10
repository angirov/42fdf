/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/10 10:15:48 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



void fill_sqare(t_graphics *data, t_player *p, int side, int color)
{
	int corner_x;
	int corner_y;

	corner_x = p->loc.x * p->map->grid.scale - side / 2;
	corner_y = p->loc.y * p->map->grid.scale - side / 2;
	
	for (int i = 0; i < side; i++)
		for (int j = 0; j < side; j++)
			api_put_pixel(data, corner_x + i, corner_y + j, color);
}

t_loc	rotate_aroud(t_loc center, double radius, float angle)
{
	t_loc	new;

	new.x = center.x + cos(angle) * radius;
	new.y = center.y + sin(angle) * radius;
	return (new);
}

void	draw_line(t_loc l0, t_loc l1, int scale, int color, t_graphics *graphics);

void	draw_dir(t_player *p)
{
	double	len = p->map->grid.width * 3;
	int s = p->map->grid.scale;
	
	t_loc center = p->loc;
	t_loc tip = rotate_aroud(center, len, p->direction);
	draw_line(center, tip, s, RED, p->map->game->graphics);
}

void draw_player(t_player *player)
{
	// printf("x: %d, y: %d\n", player->loc.x, player->loc.y);
	fill_sqare(player->map->game->graphics, player, 10, RED);
	draw_dir(player);
}

void	draw_grid(t_game *g)
{
	int	x;
	int	y;
	int	s;

	s = g->map->grid.scale;
	y = 0;
	while (y <= g->map->grid.heigth)
	{
		x = 0;
		while (x <= g->map->grid.width)
		{
			if (x < g->map->grid.width)
				draw_line((t_loc){x, y}, (t_loc){x + s, y}, s, WHITE, g->graphics);
			if (y <= g->map->grid.heigth)
				draw_line((t_loc){x, y}, (t_loc){x, y + s}, s, WHITE, g->graphics);
			x++;
		}
		y++;
	}
}

void	draw_all(t_game *game)
{
	draw_grid(game);
	draw_player(game->map->player);
	mlx_put_image_to_window(game->graphics->mlx_ptr, game->graphics->win_ptr,
		game->graphics->img_prt, 0, 0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(game));
	game->map = (t_map *)malloc(sizeof(t_map));
	map_set_sizes(game->map, 20, 20, 40);
	game->map->game = game;
	game->map->player = (t_player *)malloc(sizeof(t_player));
	game->map->player->map = game->map;
	player_set_location(game->map->player, (t_loc){3.593465, 4.772435});
	game->map->player->speed = 0.355678;
	game->map->player->direction = 90;
	game->map->player->rotation_rate = dtr(15);

	game->graphics = api_init_graphics(game->map->px_width + 1, game->map->px_heigth + 1, TITLE);

	draw_all(game);
	// mlx_hook(data->graphics->win_ptr, 17, 0, ft_destroy, data);
	mlx_key_hook(game->graphics->win_ptr, deal_key, game);
	mlx_loop(game->graphics->mlx_ptr);
	return (argc);
}

void	ft_put_pixel(t_graphics *graphics, int x, int y, int color)
{
	api_put_pixel(graphics, x, y, color);
}

// void	ft_put_pixel(t_fdf *data, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
// 	{
// 		dst = data->graphics->img_addr
// 			+ (y * data->graphics->line_length + x * (data->graphics->bits_per_pixel / 8));
// 		*(unsigned int *) dst = color;
// 	}
// }

t_fdf	*ft_make_data(char *map_file_name)
{
	t_fdf	*data;

	data = (t_fdf *)malloc(sizeof(t_fdf));
	if (!data)
		ft_error(data, "data malloc failed");


	ft_reset_angles(data);
	data->proj = 1;
	data->zoom = WIDTH / 3 / data->width;
	data->z_scale = 1;
	data->angle = 0;
	data->pivot_x = data->width * data->zoom / 2;
	data->pivot_y = data->height * data->zoom / 2;
	data->shift_x = 0;
	data->shift_y = 0;
	data->offset_x = WIDTH / 2 - data->pivot_x;
	data->offset_y = HEIGHT / 2 - data->pivot_y;
	return (data);
}

// // https://en.wikipedia.org/wiki/3D_projection
// void	print_matrix(t_fdf *data) //////////////////////////////////
// {
// 	printf("start printing matrix\n");
// 	int	j = 0;
// 	int	i = 0;

// 	while (j < data->height)
// 	{
// 		while (i < data->width)
// 		{
// 			printf("%2d/", data->matrix[j][i].x);
// 			printf("%2d/", data->matrix[j][i].y);
// 			printf("%2d ", data->matrix[j][i].z);
// 			i++;
// 		}
// 		i = 0;
// 		j++;
// 		printf("\n");
// 	}
// 	printf("finish printing matrix\n");
// }
