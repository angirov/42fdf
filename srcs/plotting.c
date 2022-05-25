/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plotting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 10:04:57 by vangirov          #+#    #+#             */
/*   Updated: 2022/05/18 13:28:18 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#define ABS(a) ((a < 0) ? -a : a)
#define MAX(a, b) ((a > b) ? a : b)
#define WHITE 0xffffff
#define RED 0xe80c0c

void	plot_line(float x, float y, float x1, float y1, t_fdf *data)
{
	float	dx;
	float	dy;
	float max;
	int	z;
	int	z1;

	z = data->z_matrix[(int)y][(int)x];
	z1 = data->z_matrix[(int)y1][(int)x1];

	isometric(&x, &y, z, data);
	isometric(&x1, &y1, z1, data);
	

	
	x *= data->zoom;
	x1 *= data->zoom;
	y *= data->zoom;
	y1 *= data->zoom;
	
	x += data->shift_x;
	y += data->shift_y;
	x1 += data->shift_x;
	y1 += data->shift_y;
	data->color = (z || z1) ? RED : WHITE;
	// data->color = WHITE;
	

	dx = x1 - x;
	dy = y1 - y;
	max = MAX(ABS(dx), ABS(dy));
	dx /= max;
	dy /= max;

	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->color);
		x += dx;
		y += dy;
	}
}

void	plot_map(t_fdf *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{

			if (x < data->width - 1)
				plot_line(x, y, x + 1, y, data);
			if (y < data->height -1)
				plot_line(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}

// void	isometric(float *x, float *y, int z, t_fdf *data)
// {
// 	*x = (*x - *y) * cos(data->angle);
// 	*y = (*x + *y) * sin(data->angle) - z;
// }

void	isometric(float *x, float *y, int z, t_fdf *data)
{
	*x = *x * cos(data->angle) - *y * sin(data->angle);
	*y = *x * sin(data->angle) + *y * cos(data->angle) - z;
}