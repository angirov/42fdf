/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:57:53 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/10 17:49:12 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	gtr(float grad)
{
	return(grad * M_PI / 180);
}

void	ft_proj_parallel(t_fdf *data)
{
	data->alpha = gtr(0);
	data->beta = gtr(0);
	data->gamma = gtr(0);
}

void	ft_proj_isometric(t_fdf *data)
{
	data->alpha = gtr(-15);
	data->beta = gtr(15);
	data->gamma = gtr(-45);
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

	if (key == KEY_1)
		data->zoom -= 1;
	if (key == KEY_2)
		data->zoom += 1;

	if (key == KEY_P)
		ft_proj_parallel(data);
	if (key == KEY_I)
		ft_proj_isometric(data);
	
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	plot_map(data);
	return(0);
}
