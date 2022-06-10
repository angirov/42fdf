/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plotting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 10:04:57 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/10 15:04:35 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
				// printf("%3d:%3d", y, x);
				plot_line(
					ft_set_point(data->matrix[y][x], data),
					ft_set_point(data->matrix[y][x+1], data), data); //(x, y, x + 1, y, data);
			if (y < data->height -1)
				// printf("%3d:%3d", y, x);
				plot_line(
					ft_set_point(data->matrix[y][x], data), 
					ft_set_point(data->matrix[y+1][x], data), data); //(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}

t_point	ft_set_point(t_point p, t_fdf *data)
{
	ft_scale_point(&p, data);
	
	x_rotate(&p.y, &p.z, data->alpha);
	y_rotate(&p.x, &p.z, data->beta);
	z_rotate(&p.x, &p.y, data->gamma);

	ft_shift_point(&p, data);
	return (p);
}

void	plot_line(t_point p0, t_point p1, t_fdf *data)
{
	float	x0 = p0.x;
	float	x1 = p1.x;
	float	y0 = p0.y;
	float	y1 = p1.y;
	float	dx;
	float	dy;
	float	max;

	dx = x1 - x0;
	dy = y1 - y0;
	max = MAX(ABS(dx), ABS(dy));
	dx /= max;
	dy /= max;

	while ((int)(x0 - x1) || (int)(y0 - y1))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x0, y0, ft_line_color(p0, p1));
		x0 += dx;
		y0 += dy;
	}
}

int	ft_line_color(t_point p0, t_point p1)
{
	// if (p0.z || p1.z)
	// 	return (RED);
	// else
	// 	return (WHITE);
	return ((p0.color + p1.color) / 2);
}
