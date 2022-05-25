/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plotting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 10:04:57 by vangirov          #+#    #+#             */
/*   Updated: 2022/05/25 23:09:37 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#define ABS(a) ((a < 0) ? -a : a)
#define MAX(a, b) ((a > b) ? a : b)
#define WHITE 0xffffff
#define RED 0xe80c0c

void	x_rotate(int *y, int *z, float alpha)
{
	int	tmp_y;
	int	tmp_z;

	tmp_y = *y;
	tmp_z = *z;
	*y = tmp_y * cos(alpha) + tmp_z * sin(alpha);
	*z = -tmp_y * sin(alpha) + tmp_z * cos(alpha);
}

void	y_rotate(int *x, int *z, float beta)
{
	int	tmp_x;
	int	tmp_z;

	tmp_x = *x;
	tmp_z = *z;
	*x = tmp_x * cos(beta) + tmp_z * sin(beta);
	*z = -tmp_x * sin(beta) + tmp_z * cos(beta);
}

void	z_rotate(int *x, int *y, float gamma)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = tmp_x * cos(gamma) - tmp_y * sin(gamma);
	*y = tmp_x * sin(gamma) + tmp_y * cos(gamma);
}


////////////////////////////////////////////////////////////////////////////////////


void	ft_scale_point(t_point *p, t_fdf *data)
{
	p->x *= data->zoom;
	p->y *= data->zoom;
	p->z *= data->zoom;
}

void	ft_shift_point(t_point *p, t_fdf *data)
{
	p->x += data->shift_x + data->offset_x;
	p->y += data->shift_y + data->offset_y;
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

int	ft_line_color(t_point p0, t_point p1)
{
	// if (p0.z || p1.z)
	// 	return (RED);
	// else
	// 	return (WHITE);
	return ((p0.color + p1.color) / 2);
}

void	plot_line(t_point p0, t_point p1, t_fdf *data)
{
	float	x0 = p0.x;
	float	x1 = p1.x;
	float	y0 = p0.y - p0.z;
	float	y1 = p1.y - p1.z;
	float	dx;
	float	dy;
	float	max;

	// float	z0 = p0.z;
	// float	z1 = p1.z;
	// isometric(&x0, &y0, z0, data);
	// isometric(&x1, &y1, z1, data);

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

// void	isometric(float *x, float *y, int z, t_fdf *data)
// {
// 	*x = (*x - *y) * cos(data->angle);
// 	*y = (*x + *y) * sin(data->angle) - z;
// }

// void	isometric(float *x, float *y, int z, t_fdf *data)
// {
// 	float	tmp_x;
// 	float	tmp_y;

// 	tmp_x = *x;
// 	tmp_y = *y;
// 	*x = tmp_x * cos(data->angle) - tmp_y * sin(data->angle);
// 	*y = tmp_x * sin(data->angle) + tmp_y * cos(data->angle) - z;
// }

void	isometric(float *x, float *y, float z, t_fdf *data)
{
	float	tmp_x;
	float	tmp_y;

	tmp_x = *x;
	tmp_y = *y;

	*x = tmp_x * cos(data->angle) - tmp_y * sin(data->angle);
	*y = tmp_x * sin(data->angle) + tmp_y * cos(data->angle) - z + z;
}