/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:57:53 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/12 20:33:27 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	rtg(float rad)
{
	return(rad * 180 / M_PI);
}

void	ft_clear_image(t_fdf *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_put_pixel(data, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

int	deal_key(int key, t_fdf *data)
{
	ft_printf("%d\n", key);
	
	// if (key == 112)
	// 	print_matrix(data);////////////////////////////////////////////////////////
	if (key == KEY_ESC)
		ft_escape(data);
	if (key == KEY_LEFT)
		data->shift_x -= data->zoom;
	if (key == KEY_UP)
		data->shift_y -= data->zoom;
	if (key == KEY_RIGHT)
		data->shift_x += data->zoom;
	if (key == KEY_DOWN)
		data->shift_y += data->zoom;
		
	if (key == KEY_Q)
		data->alpha += ANGLE_VAL;
	if (key == KEY_W)
		data->alpha -= ANGLE_VAL;
	if (key == KEY_A)
		data->beta += ANGLE_VAL;
	if (key == KEY_S)
		data->beta -= ANGLE_VAL;
	if (key == KEY_Z)
		data->gamma += ANGLE_VAL;
	if (key == KEY_X)
		data->gamma -= ANGLE_VAL;

	if (key == KEY_1 && data->zoom > 1)
		data->zoom -= 1;
	if (key == KEY_2)
		data->zoom += 1;

	if (key == KEY_P)
		ft_reset_angles(data);
	if (key == KEY_I)
		data->proj = 1;
	if (key == KEY_C)
		data->proj = 2;
	
	ft_printf("%f, %f, %f\n", \
		(int)rtg(data->alpha), (int)rtg(data->beta), (int)rtg(data->gamma));
	ft_clear_image(data);

	ft_plot_map(data);
	return(0);
}

// float	gtr(float grad)
// {
// 	return(grad * M_PI / 180);
// }
