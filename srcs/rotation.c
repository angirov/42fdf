/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:22:57 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/10 19:03:24 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	*x = tmp_x * cos(beta) - tmp_z * sin(beta);
	*z = tmp_x * sin(beta) + tmp_z * cos(beta);
}

void	z_rotate(int *x, int *y, float gamma)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = tmp_x * cos(gamma) + tmp_y * sin(gamma);
	*y = -tmp_x * sin(gamma) + tmp_y * cos(gamma);
}

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

void	ft_isometric(int *x, int *y, int *z)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = (tmp_x - tmp_y) + cos(0.8);
	*y = (tmp_x + tmp_y) + sin(0.8) -*z;
}