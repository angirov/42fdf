/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/10 10:02:13 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_loc	dir2vec(double radians)
{
	t_loc	res;

	res.x = cos(radians);
	res.y = sin(radians);
	return (res);
}

t_loc	add_vecs(t_loc vec1, t_loc vec2)
{
	t_loc	res;

	res.x = vec1.x + vec2.x;
	res.y = vec1.y + vec2.y;
	return (res);
}

t_loc	sc_mult(t_loc vec, double scalar)
{
	t_loc	res;

	res.x = vec.x * scalar;
	res.y = vec.y * scalar;
	return (res);
}

double	rtd(double radians)
{
	return (radians * 180 / M_PI);
}

double	dtr(double degrees)
{
	return (degrees / 180 * M_PI);
}

double ft_abs(double num)
{
	if (num >= 0)
		return (num);
	else
		return (-num);
}

void fill_sqare(t_graphics *data, t_player *p, int side, int color)
{
	int corner_x;
	int corner_y;

	corner_x = p->loc.x * p->game->grid.scale - side / 2;
	corner_y = p->loc.y * p->game->grid.scale - side / 2;
	
	for (int i = 0; i < side; i++)
		for (int j = 0; j < side; j++)
			api_put_pixel(data, corner_x + i, corner_y + j, color);
}

t_loc	rotate_aroud(t_loc center, double radius, double radians)
{
	t_loc	new;

	new.x = center.x + cos(radians) * radius;
	new.y = center.y + sin(radians) * radius;
	return (new);
}

void	draw_line(t_loc l0, t_loc l1, int scale, int color, t_graphics *graphics);



void cast_rays(t_player	*p)
{
	int		screen = 100;	//px
	// int		fov = 90;		// degrees
	
	// double	posX = p->loc.x;
	// double	posY = p->loc.y;  //x and y start position
	
	// double	dirX = -1, dirY = 0; //initial direction vector W?
	t_loc	dir_vec = dir2vec(p->direction);
	t_loc	center = add_vecs(p->loc, dir_vec);
	t_loc	plane_vec = dir2vec(p->direction + dtr(90));
	printf(">>>>> TEST3\n");

	draw_line(p->loc, center, p->game->grid.scale, RED, p->game->game->graphics);
	draw_line(center, add_vecs(center, plane_vec), p->game->grid.scale, WHITE, p->game->game->graphics);
	draw_line(center, add_vecs(center, sc_mult(plane_vec, -1)), p->game->grid.scale, WHITE, p->game->game->graphics);
	// double	planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	printf(">>>>> TEST33\n");

	for(int x = 0; x < screen; x++)
	{
		
		t_loc	rayDir;
		double	cameraX;
		//calculate ray position and direction
		cameraX = 2 * x / (double)screen - 1; //x-coordinate in camera space
		rayDir = add_vecs(center, sc_mult(plane_vec, cameraX));
		draw_line(p->loc, rayDir, p->game->grid.scale, RED, p->game->game->graphics);
	}
	// 	double	deltaDistX = sqrt(1 + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x));
	// 	double	deltaDistY = sqrt(1 + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y));

	// 	//which box of the map we're in
	// 	int mapX = (int)p->loc.x;
	// 	int mapY = (int)p->loc.y;
	// 	//length of ray from current position to next x or y-side
	// 	double sideDistX;
	// 	double sideDistY;
	// 	//length of ray from one x or y-side to next x or y-side
	// 	// double deltaDistX = (rayDir.x == 0) ? 1e30 : ft_abs(1 / rayDir.x);
	// 	// double deltaDistY = (rayDir.y == 0) ? 1e30 : ft_abs(1 / rayDir.y);
	// 	// double perpWallDist;//////////////////////////////////////
	// 	//what direction to step in x or y-direction (either +1 or -1)
	// 	int stepX;
	// 	int stepY;
	// 	int hit = 0; //was there a wall hit?
	// 	int side; //was a NS or a EW wall hit?

		// //calculate step and initial sideDist
		// if (rayDir.x < 0)
		// {
		// 	stepX = -1;
		// 	sideDistX = (p->loc.x - mapX) * deltaDistX;
		// }
		// else
		// {
		// 	stepX = 1;
		// 	sideDistX = (mapX + 1.0 - p->loc.x) * deltaDistX;
		// }
		// if (rayDir.y < 0)
		// {
		// 	stepY = -1;
		// 	sideDistY = (p->loc.y - mapY) * deltaDistY;
		// }
		// else
		// {
		// 	stepY = 1;
		// 	sideDistY = (mapY + 1.0 - p->loc.y) * deltaDistY;
		// }
		// // perform DDA
		// while (hit == 0)
		// {
		// 	//jump to next map square, either in x-direction, or in y-direction
		// 	if (sideDistX < sideDistY)
		// 	{
		// 		sideDistX += deltaDistX;
		// 		mapX += stepX;
		// 		side = 0;
		// 	}
		// 	else
		// 	{
		// 		sideDistY += deltaDistY;
		// 		mapY += stepY;
		// 		side = 1;
		// 	}
		// 	//Check if ray has hit a wall
		// 	if (p->game->map[mapX*24 + mapY] > 0)
		// 		hit = 1;
		// }
		// printf("side: %d\n", side);
	// }
}

void	draw_dir(t_player *p)
{
	double	len = p->game->grid.width * 3;
	int s = p->game->grid.scale;
	
	t_loc center = p->loc;
	t_loc tip = rotate_aroud(center, len, p->direction);
	draw_line(center, tip, s, RED, p->game->graphics);
}

void draw_player(t_player *player)
{
	// printf("x: %d, y: %d\n", player->loc.x, player->loc.y);
	fill_sqare(player->game->graphics, player, 10, RED);
	// draw_dir(player);
	cast_rays(player);
}

void	draw_grid(t_game *g)
{
	int	x;
	int	y;
	int	s;

	printf("Hello scale: \n");
	s = g->grid.scale;
	y = 0;
	while (y <= g->grid.heigth)
	{
		x = 0;
		while (x <= g->grid.width)
		{
			if (x < g->grid.width)
			{
				printf("Hi\n");
				draw_line((t_loc){x, y}, (t_loc){x + s, y}, s, WHITE, g->graphics);
			}
			if (y <= g->grid.heigth)
				draw_line((t_loc){x, y}, (t_loc){x, y + s}, s, WHITE, g->graphics);
			x++;
		}
		y++;
	}
}

void	draw_all(t_game *game)
{
	// draw_grid(game);
	printf(">>>>> TEST o");
	// draw_player(game->player);
	printf(">>>>> TEST oooo");
	mlx_put_image_to_window(game->graphics->mlx_ptr, game->graphics->win_ptr,
		game->graphics->img_prt, 0, 0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	// int	map_w = 10;
	// int	map_h = 10;
	// int	worldMap[24][24]=
	// {
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	// };
	game = (t_game *)malloc(sizeof(game));
	// game->map = (int *)worldMap;
	set_sizes(game, 10, 10, 100);
	printf(">>>>> TEST2\n");
	game->player = (t_player *)malloc(sizeof(t_player));
	printf(">>>>> TEST22\n");
	game->player->game = game;
	printf(">>>>> TEST222\n");
	player_set_location(game->player, (t_loc){3.593465, 4.772435});

	game->player->speed = 0.355678;
	game->player->direction = dtr(90 + 180);
	game->player->rotation_rate = dtr(15);
	printf(">>>>> TEST2222\n");

	game->graphics = api_init_graphics(game->px_width, game->px_heigth, TITLE);

	printf(">>>>> TEST   22222\n");
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

// t_fdf	*ft_make_data(char *map_file_name)
// {
// 	t_fdf	*data;

// 	data = (t_fdf *)malloc(sizeof(t_fdf));
// 	if (!data)
// 		ft_error(data, "data malloc failed");


// 	ft_reset_angles(data);
// 	data->proj = 1;
// 	data->zoom = WIDTH / 3 / data->width;
// 	data->z_scale = 1;
// 	data->angle = 0;
// 	data->pivot_x = data->width * data->zoom / 2;
// 	data->pivot_y = data->height * data->zoom / 2;
// 	data->shift_x = 0;
// 	data->shift_y = 0;
// 	data->offset_x = WIDTH / 2 - data->pivot_x;
// 	data->offset_y = HEIGHT / 2 - data->pivot_y;
// 	return (data);
// }

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
