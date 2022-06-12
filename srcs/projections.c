/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:22:12 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/12 20:25:41 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void	ft_reset_angles(t_fdf *data)
{
	data->alpha = 0;
	data->beta = 0;
	data->gamma = 0;
	data->proj = 0;
}

void	ft_isometric(int *x, int *y, int *z)
{
	int	tmp_x = *x;
	int	tmp_y = *y;

	*x = tmp_x - tmp_y;
	*y = (tmp_x + tmp_y) /2 - *z;
}

void	ft_cabinet(int *x, int *y, int *z)
{
	int	tmp_x = *x;
	int	tmp_y = *y;

	*x = tmp_x - 0.5 * tmp_y;
	*y = tmp_y * 0.5 - *z;
}
