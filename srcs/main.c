/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/05 15:42:20 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



void fill_sqare(t_graphics *data, int x, int y, int side, int color)
{
	int corner_x;
	int corner_y;

	corner_x = x - side / 2;
	corner_y = y - side / 2;
	
	for (int i = 0; i < side; i++)
		for (int j = 0; j < side; j++)
			api_put_pixel(data, corner_x + i, corner_y + j, color);
}

float	rtd(float radians)
{
	return (radians * 180 / M_PI);
}

float	dtr(float degrees)
{
	return (degrees / 180 * M_PI);
}

t_loc	rotate_aroud(t_loc center, float radius, float angle)
{
	t_loc	new;

	new.x = center.x + cos(angle) * radius;
	new.y = center.y + sin(angle) * radius;
	return (new);
}

void	draw_line(t_loc l0, t_loc l1, t_graphics *graphics);

void	draw_dir(t_player *player)
{
	int	len = 200;
	
	t_loc center = player->loc;
	t_loc tip = rotate_aroud(center, len, player->direction);
	draw_line(center, tip, player->map->game->graphics);
}

void draw_player(t_player *player)
{
	// printf("x: %d, y: %d\n", player->loc.x, player->loc.y);
	fill_sqare(player->map->game->graphics, player->loc.x, player->loc.y, 10, RED);
	draw_dir(player);
}

void	draw_all(t_game *game)
{
	draw_player(game->map->player);
	mlx_put_image_to_window(game->graphics->mlx_ptr, game->graphics->win_ptr,
		game->graphics->img_prt, 0, 0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(game));
	game->graphics = api_init_graphics(WIDTH, HEIGHT, TITLE);
	game->map = (t_map *)malloc(sizeof(t_map));
	game->map->game = game;
	map_set_sizes(game->map, WIDTH, HEIGHT);
	game->map->player = (t_player *)malloc(sizeof(t_player));
	game->map->player->map = game->map;
	player_set_location(game->map->player, WIDTH / 2, HEIGHT / 2);
	game->map->player->speed = 10;
	game->map->player->direction = 90;
	game->map->player->rotation_rate = dtr(15);
	api_put_pixel(game->graphics, game->map->player->loc.x, game->map->player->loc.y, RED);


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
