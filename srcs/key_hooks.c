/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:57:53 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/09 14:09:19 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	ft_clear_image(t_graphics *graphics)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_put_pixel(graphics, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void draw_player(t_player *player);
void	draw_all(t_game *game);

int	deal_key(int key, t_game *game)
{
	if (key == KEY_LEFT)
	{
		player_move_W(game->player);
		printf("move W\n");
	}
	if (key == KEY_UP)
	{
		player_move_N(game->player);
		printf("move N\n");
	}
	if (key == KEY_RIGHT)
	{
		player_move_E(game->player);
		printf("move E\n");
	}
	if (key == KEY_DOWN)
	{
		player_move_S(game->player);
		printf("move S\n");
	}

	if (key == KEY_Q)
		player_turn_left(game->player);
	if (key == KEY_W)
		player_turn_right(game->player);

	printf("loc: %lf : %lf\n",	game->player->loc.x,
								game->player->loc.y);
	// printf("squ: %d : %d\n",	(int)game->player->loc.x,
	// 							(int)game->player->loc.y);
	printf("dir: %lf\n", rtd(game->player->direction));
	
	ft_clear_image(game->graphics);
	draw_all(game);

	return (0);
}

// void	deal_key2(int key, t_fdf *data)
// {
// 	float	angle_shift;

// 	angle_shift = M_PI / ANGLE_DIV;
// 	if (key == KEY_ESC)
// 		ft_escape(data);
// 	if (key == KEY_LEFT)
// 		data->shift_x -= data->zoom;
// 	if (key == KEY_UP)
// 		data->shift_y -= data->zoom;
// 	if (key == KEY_RIGHT)
// 		data->shift_x += data->zoom;
// 	if (key == KEY_DOWN)
// 		data->shift_y += data->zoom;
// 	if (key == KEY_Q)
// 		data->alpha += angle_shift;
// 	if (key == KEY_W)
// 		data->alpha -= angle_shift;
// 	if (key == KEY_A)
// 		data->beta += angle_shift;
// 	if (key == KEY_S)
// 		data->beta -= angle_shift;
// 	if (key == KEY_Z)
// 		data->gamma += angle_shift;
// 	if (key == KEY_X)
// 		data->gamma -= angle_shift;
// }

// int	deal_key(int key, t_fdf *data)
// {
// 	deal_key2(key, data);
// 	if (key == KEY_1 && data->zoom > 1)
// 		data->zoom -= 1;
// 	if (key == KEY_2)
// 		data->zoom += 1;
// 	if (key == KEY_3 && data->z_scale > 1)
// 		data->z_scale -= 1;
// 	if (key == KEY_4)
// 		data->z_scale += 1;
// 	if (key == KEY_P)
// 		ft_reset_angles(data);
// 	if (key == KEY_I)
// 		data->proj = 1;
// 	if (key == KEY_C)
// 		data->proj = 2;
// 	ft_clear_image(data);
// 	ft_plot_map(data);
// 	return (0);
// }

// float	gtr(float grad)
// {
// 	return(grad * M_PI / 180);
// }
