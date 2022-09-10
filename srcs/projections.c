/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:22:12 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/10 08:30:39 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_reset_angles(t_fdf *data)
{
	data->alpha = 0;
	data->beta = 0;
	data->gamma = 0;
	data->proj = 0;
}

void	ft_isometric(int *x, int *y, int *z)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = tmp_x - tmp_y;
	*y = (tmp_x + tmp_y) / 2 - *z;
}

void	ft_cabinet(int *x, int *y, int *z)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = tmp_x - 0.5 * tmp_y;
	*y = tmp_y * 0.5 - *z;
}

// double	ft_abs(double a)
// {
// 	if (a >= 0)
// 		return (a);
// 	return (a * -1);
// }

float	ft_max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}
