/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:57:53 by vangirov          #+#    #+#             */
/*   Updated: 2022/05/25 22:20:26 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	deal_key(int key, t_fdf *data)
{
	ft_printf("%d\n", key);
	
	if (key == 112)
		print_matrix(data);////////////////////////////////////////////////////////
	if (key == KEY_ESC)
		ft_escape(data);
	if (key == KEY_L)
		data->shift_x -= SHIFT_VAL;
	if (key == KEY_U)
		data->shift_y -= SHIFT_VAL;
	if (key == KEY_R)
		data->shift_x += SHIFT_VAL;
	if (key == KEY_D)
		data->shift_y += SHIFT_VAL;
		
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

	if (key == 49)
		data->zoom -= 1;
	if (key == 50)
		data->zoom += 1;

	if (key == 96)
	{
		data->alpha = 0;
		data->beta = 0;
		data->gamma = 0;
	}


	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	plot_map(data);
	return(0);
}
