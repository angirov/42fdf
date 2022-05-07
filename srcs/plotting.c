/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plotting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:04 by vangirov          #+#    #+#             */
/*   Updated: 2022/05/07 18:19:19 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define ABS(a) ((a < 0) ? -a : a)
#define SLOPE(x0 ,x1) ((x0 < x1) ? 1 : -1)
#define COLOR 0xffffff

void	plot_line(int x0, int y0, int x1, int y1, t_fdf *data)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	// int	err2;

	dx = ABS(x1 - x0);
	dy = -ABS(y1 - y0);
	sx = SLOPE(x0, x1);
	sy = SLOPE(y0, y1);
	err = dx + dy;

	mlx_pixel_put(data->mlx_ptr, data->win_ptr, x0, y0, COLOR);
	while (!(x0 == x1 && y0 == y1))
	{
		// err2 = 2 * err;
		if (err*2 > dy)
		{
			err += dy;
			x0 += sx;
		}
		if (err*2 < dx)
		{
			err += dx;
			y0 +=sy;
		}
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x0, y0, COLOR);
	}
}

// plotLine(x0, y0, x1, y1)
//     dx = x1 - x0
//     dy = y1 - y0
//     D = 2*dy - dx
//     y = y0

//     for x from x0 to x1
//         plot(x,y)
//         if D > 0
//             y = y + 1
//             D = D - 2*dx
//         end if
//         D = D + 2*dy
