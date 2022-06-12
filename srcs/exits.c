/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:00:36 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/12 14:17:24 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(t_fdf *data, char *message)
{
	ft_destroy(data);
	perror(message);
	exit(1);
}

void	ft_escape(t_fdf *data)
{
	ft_destroy(data);
	exit(0);
}

void	ft_free_data(t_fdf *data)
{
	int i;

	i = 0;
	while (i < data->height)
		free(data->matrix[i++]);
	free(data->matrix);
	free(data);
}

int	ft_destroy(t_fdf *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_prt);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	// mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	ft_free_data(data);
	exit(1);
}