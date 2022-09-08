/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plotting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 10:04:57 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/08 23:25:13 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	ft_plot_map(t_fdf *data)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (y < data->height)
// 	{
// 		x = 0;
// 		while (x < data->width)
// 		{
// 			if (x < data->width - 1)
// 				ft_plot_line(
// 					ft_set_point(data->matrix[y][x], data),
// 					ft_set_point(data->matrix[y][x + 1], data), data);
// 			if (y < data->height - 1)
// 				ft_plot_line(
// 					ft_set_point(data->matrix[y][x], data),
// 					ft_set_point(data->matrix[y + 1][x], data), data);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr,
// 		data->mlx_data->img_prt, 0, 0);
// }

// t_point	ft_set_point(t_point p, t_fdf *data)
// {
// 	ft_scale_point(&p, data);
// 	p.x = p.x - data->pivot_x;
// 	p.y = p.y - data->pivot_y;
// 	x_rotate(&p.y, &p.z, data->alpha);
// 	y_rotate(&p.x, &p.z, data->beta);
// 	z_rotate(&p.x, &p.y, data->gamma);
// 	if (data->proj == 1)
// 		ft_isometric(&p.x, &p.y, &p.z);
// 	if (data->proj == 2)
// 		ft_cabinet(&p.x, &p.y, &p.z);
// 	p.x = p.x + data->pivot_x;
// 	p.y = p.y + data->pivot_y;
// 	ft_shift_point(&p, data);
// 	return (p);
// }

void	ft_plot_f_line(t_fpoint p0, t_fpoint p1, int color, t_graphics *g)
{
	float	dx;
	float	dy;
	float	max;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	max = ft_max(ft_abs(dx), ft_abs(dy));
	dx /= max;
	dy /= max;
	while ((int)(p0.x - p1.x) || (int)(p0.y - p1.y))
	{
		ft_put_pixel(g, p0.x, p0.y, color);
		p0.x += dx;
		p0.y += dy;
	}
}

void	draw_line(t_loc l0, t_loc l1, int scale, int color, t_graphics *g)
{
	t_point	pt_px0;
	t_point	pt_px1;

	pt_px0.x = l0.x * scale;
	pt_px0.y = l0.y * scale;
	pt_px0.color = color;
	pt_px1.x = l1.x * scale;
	pt_px1.y = l1.y * scale;
	pt_px1.color = color;
	ft_plot_line(pt_px0, pt_px1, color, g);
}

void	ft_plot_line(t_point p0, t_point p1, int color, t_graphics *g)
{
	t_fpoint	fpoint0;
	t_fpoint	fpoint1;

	fpoint0.x = p0.x;
	fpoint1.x = p1.x;
	fpoint0.y = p0.y;
	fpoint1.y = p1.y;
	fpoint0.color = p0.color;
	fpoint1.color = p1.color;
	ft_plot_f_line(fpoint0, fpoint1, color, g);
}

int	ft_line_color(t_fpoint p0, t_fpoint p1)
{
	return ((p0.color + p1.color) / 2);
}
