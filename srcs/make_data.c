/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:03:50 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/10 19:07:59 by vangirov         ###   ########.fr       */
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
	data->addr = mlx_get_data_addr(data->img_prt,
			&data->bits_per_pixel, &data->line_length,
			&data->endian);
}

t_fdf	*ft_make_data(char *map_file_name)
{
	t_fdf	*data;

	data = (t_fdf *)malloc(sizeof(t_fdf));
	if (!data)
		ft_error(data, "data malloc failed");
	ft_init_mlx(data);
	read_map(map_file_name, data);
	data->zoom = WIDTH / 3 / data->width;
	data->angle = 0;
	data->pivot_x = data->width * data->zoom / 2;
	data->pivot_y = data->height * data->zoom / 2;
	data->shift_x = 0;
	data->shift_y = 0;
	data->offset_x = WIDTH / 2 - data->pivot_x;
	data->offset_y = HEIGHT / 2 - data->pivot_y;
	ft_proj_isometric(data);
	return data;
}
