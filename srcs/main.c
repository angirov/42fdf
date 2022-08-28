/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/28 22:23:33 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*data;

	ft_check_input(argc, argv);
	data = ft_make_data(argv[1]);
	printf("TEST\n");
	ft_plot_map(data);
	mlx_hook(data->graphics->win_ptr, 17, 0, ft_destroy, data);
	mlx_key_hook(data->graphics->win_ptr, deal_key, data);
	mlx_loop(data->graphics->mlx_ptr);
	return (argc);
}

// void	ft_put_pixel(t_fdf *data, int x, int y, int color)
// {
// 	api_put_pixel(data->graphics, x, y, color);
// }

void	ft_put_pixel(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->graphics->img_addr
			+ (y * data->graphics->line_length + x * (data->graphics->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

t_fdf	*ft_make_data(char *map_file_name)
{
	t_fdf	*data;

	data = (t_fdf *)malloc(sizeof(t_fdf));
	if (!data)
		ft_error(data, "data malloc failed");



	data->graphics = (t_graphics *)malloc(sizeof(t_graphics));
	api_init_graphics(data);


	read_map(map_file_name, data);
	ft_reset_angles(data);
	data->proj = 1;
	data->zoom = WIDTH / 3 / data->width;
	data->z_scale = 1;
	data->angle = 0;
	data->pivot_x = data->width * data->zoom / 2;
	data->pivot_y = data->height * data->zoom / 2;
	data->shift_x = 0;
	data->shift_y = 0;
	data->offset_x = WIDTH / 2 - data->pivot_x;
	data->offset_y = HEIGHT / 2 - data->pivot_y;
	return (data);
}

// // https://en.wikipedia.org/wiki/3D_projection
// void	print_matrix(t_fdf *data) //////////////////////////////////
// {
// 	printf("start printing matrix\n");
// 	int	j = 0;
// 	int	i = 0;

// 	while (j < data->height)
// 	{
// 		while (i < data->width)
// 		{
// 			printf("%2d/", data->matrix[j][i].x);
// 			printf("%2d/", data->matrix[j][i].y);
// 			printf("%2d ", data->matrix[j][i].z);
// 			i++;
// 		}
// 		i = 0;
// 		j++;
// 		printf("\n");
// 	}
// 	printf("finish printing matrix\n");
// }
