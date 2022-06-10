/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:03:50 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/10 14:52:36 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_check_input(int argc, char **argv)
{
	if (argc != 2 || !argv[0][0])
	{
		ft_fdprintf(2, "Bad input. Usage: %s <map.fdf>\n", argv[0]);
		exit(1);
	}
	else
		return ;
}

void	ft_init_mlx(t_fdf *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_error(data, "mlx_init failed");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, TITLE);
	if (!data->mlx_ptr)
		ft_error(data, "mlx_new_window failed");
	data->img_prt = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img_prt)
		ft_error(data, "mlx_new_image failed");
}

t_fdf	*ft_make_data(char *map_file_name)
{
	t_fdf	*data;

	data = (t_fdf *)malloc(sizeof(t_fdf));
	if (!data)
		ft_error(data, "data malloc failed");
	ft_init_mlx(data);
	read_map(map_file_name, data);
	data->zoom = 20; /////////////////////////////////////////////////
	data->angle = 0; /////////////////////////////////////////////////
	data->shift_x = 0;
	data->offset_y = 100;
	data->offset_x = 100;
	data->alpha = 0;
	data->beta = 0;
	data->gamma = 0;
	return data;
}
