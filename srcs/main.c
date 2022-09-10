/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/10 17:29:12 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	vec_len(t_loc vec)
{
	return (sqrt((vec.x * vec.x) + (vec.y * vec.y)));
}

t_loc	norm_vec(t_loc vec)
{
	double len;
	
	len = vec_len(vec);
	return ((t_loc){ vec.x / len, vec.y / len });
}

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

void fill_sqare(t_game *g, t_loc corner, int side, int color)
{
	int corner_x;
	int corner_y;

	corner_x = corner.x * g->grid.scale;
	corner_y = corner.y * g->grid.scale;
	
	for (int i = 0; i < side*g->grid.scale; i++)
		for (int j = 0; j < side*g->grid.scale; j++)
			api_put_pixel(g->graphics, corner_x + i, corner_y + j, color);
}

void fill_rect(t_game *g, t_loc corner, int x, int y, int color)
{
	int corner_x;
	int corner_y;

	corner_x = corner.x * g->grid.scale;
	corner_y = corner.y * g->grid.scale;
	
	for (int i = 0; i < y*g->grid.scale; i++)
		for (int j = 0; j < x*g->grid.scale; j++)
			api_put_pixel(g->graphics, corner_x + i, corner_y + j, color);
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
	int		screen = p->game->graphics->screen_width;	//px
	// int		fov = 90;		// degrees
	
	t_loc	dir_vec = dir2vec(p->direction);
	// t_loc	center = add_vecs(p->loc, dir_vec);
	t_loc	plane_vec = dir2vec(p->direction + dtr(90));
	
	p->game->distances = malloc(sizeof(double) * screen);
	p->game->sides = malloc(sizeof(int) * screen);
	p->game->ray_dirs = malloc(sizeof(t_loc) * screen);

	for(int x = 0; x < screen; x++)
	{
		printf(">>> Ray %2d ", x);
		t_loc	rayDir;
		double	cameraX;

		//calculate ray position and direction
		cameraX = 2 * x / (double)screen - 1; //x-coordinate in camera space
		rayDir = add_vecs(dir_vec, sc_mult(plane_vec, cameraX));
		p->game->ray_dirs[x] = rayDir;
		printf("rD.x: %lf ", rayDir.x);
		printf("rD.y: %lf\t", rayDir.y);
		// draw_line(p->loc, add_vecs(p->loc, norm_vec(rayDir)), p->game->grid.scale, WHITE, p->game->graphics);
	
		double	deltaDistX = sqrt(1 + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x));
		double	deltaDistY = sqrt(1 + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y));
		// double deltaDistX = (rayDir.x == 0) ? 1e30 : ft_abs(1 / rayDir.x);
		// double deltaDistY = (rayDir.y == 0) ? 1e30 : ft_abs(1 / rayDir.y);
		printf("dX: %lf ", deltaDistX);
		printf("dY: %lf ", deltaDistY);
		//which box of the map we're in
		int mapX = (int)p->loc.x;
		int mapY = (int)p->loc.y;
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		//length of ray from one x or y-side to next x or y-side
		// double perpWallDist;//////////////////////////////////////
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDir.x < 0)
		{
			stepX = -1;
			sideDistX = (p->loc.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - p->loc.x) * deltaDistX;
		}
		if (rayDir.y < 0)
		{
			stepY = -1;
			sideDistY = (p->loc.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - p->loc.y) * deltaDistY;
		}
		// perform DDA
		printf("StepX: %d SDX: %lf ", stepX, sideDistX);
		printf("StepY: %d SDY: %lf ", stepY, sideDistY);
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (p->game->map[mapY*24 + mapX] > 0)
				hit = 1;
		}
		printf("side: %d", side);
		printf("SideDistX: %lf ", sideDistX);
		printf("SideDistY: %lf\n", sideDistY);
		if(side == 0)
			sideDistX = (sideDistX - deltaDistX);
		else
			sideDistY = (sideDistY - deltaDistY);
		// t_loc	hit_point;
		if (sideDistX < sideDistY)
		{
			// hit_point = sc_mult(norm_vec(rayDir), sideDistX);
			p->game->distances[x] = sideDistX;
		}
		else
		{
			// hit_point = sc_mult(norm_vec(rayDir), sideDistY);
			p->game->distances[x] = sideDistY;
		}
		p->game->sides[x] = side;
		// draw_line(p->loc, add_vecs(p->loc, hit_point), p->game->grid.scale, RED, p->game->graphics);
	}
	for(int x = 0; x < screen; x++)
		// printf("%2d: %lf\n", x, p->game->distances[x]);
	{
		int h = p->game->graphics->screen_height;
		int lineHeight = (int)(h / p->game->distances[x]);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)drawEnd = h - 1;
		int color = RED;
		if (p->game->sides[x] == 1) {color = color / 2;}
		draw_line((t_loc){x, drawStart}, (t_loc){x, drawEnd}, 1, color, p->game->graphics);
	}
}

void	draw_rays(t_game *g)
{
	t_loc	hit_point;
	int		screen = g->graphics->screen_width;	//px

	for(int x = 0; x < screen; x += screen / 50)
	{
		hit_point = sc_mult(norm_vec(g->ray_dirs[x]), g->distances[x]);
		draw_line(g->player->loc, add_vecs(g->player->loc, hit_point), g->grid.scale, YELLOW, g->graphics);
	}
}

void	draw_dir(t_player *p)
{
	double	len = p->game->grid.width * 3;
	int s = p->game->grid.scale;
	
	t_loc center = p->loc;
	t_loc tip = rotate_aroud(center, len, p->direction);
	draw_line(center, tip, s, RED, p->game->graphics);
}

// void draw_player(t_player *p)
// {
// 	// int s = p->game->grid.scale;
// 	// printf("x: %d, y: %d\n", p->loc.x, p->loc.y);
// 	// fill_sqare(p->game, (t_loc){p->loc.x - 5/s, p->loc.y - 5/s}, 10/s, RED);
// 	// draw_dir(p);
// }

int map_value(t_game *g, int x, int y)
{
	return (g->map[y * g->grid.width + x]);
}

void fill_grid(t_game *g, int x, int y, int scale)
{
	// int s = g->grid.scale;
	if (map_value(g, x, y) > 0)
		// printf("%d", g->map[y * g->grid.width + x]);
		fill_sqare(g, (t_loc){x, y}, 1, GRAY);
}

void map_background(t_game *g)
{
	fill_rect(g, (t_loc){0, 0}, g->grid.width, g->grid.heigth, L_GRAY);
}

void	draw_grid(t_game *g)
{
	int	x;
	int	y;
	int	s;

	printf("Hello scale: \n");
	s = g->grid.scale;
	y = 0;
	while (y < g->grid.heigth)
	{
		x = 0;
		while (x < g->grid.width)
		{
			if (x < g->grid.width)
			{
				draw_line((t_loc){x, y}, (t_loc){x + 1, y}, s, GRAY, g->graphics);
			}
			if (y <= g->grid.heigth)
				draw_line((t_loc){x, y}, (t_loc){x, y + 1}, s, GRAY, g->graphics);
			fill_grid(g, x, y, s);
			x++;
		}
		y++;
	}
}

void	draw_all(t_game *game)
{
	cast_rays(game->player);
	map_background(game);
	draw_grid(game);
	draw_rays(game);
	mlx_put_image_to_window(game->graphics->mlx_ptr, game->graphics->win_ptr,
		game->graphics->img_prt, 0, 0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	int	map_w = 24;
	int	map_h = 24;
	int	worldMap[24][24]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	game = (t_game *)malloc(sizeof(t_game));
	game->map = (int *)worldMap;
	set_sizes(game, map_w, map_h, 20);
	game->player = (t_player *)malloc(sizeof(t_player));
	game->player->game = game;
	player_set_location(game->player, (t_loc){3.593465, 4.772435});

	game->player->speed = 0.355678;
	game->player->direction = dtr(90 + 180);
	game->player->rotation_rate = dtr(15);

	game->graphics = api_init_graphics(1600, 800, TITLE);

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
