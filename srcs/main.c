/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/05/08 11:37:19 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define KEY_L 65361
#define KEY_U 65362
#define KEY_R 65363
#define KEY_D 65364
#define SHIFT_VAL 10
///////////////////////////////////////////////////////////////////////////////////
#include <stdio.h> /////////////////////////////////////////////////
void	print_z_matrix(t_fdf *data) //////////////////////////////////
{
	int	j = 0;
	int	i = 0;

	while (j < data->height)
	{
		while (i < data->width)
			printf("%3d", data->z_matrix[j][i++]);
		i = 0;
		j++;
		printf("\n");
	}
}
// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }
///////////////////////////////////////////////////////////////////////////////////

int	deal_key(int key, t_fdf *data)
{
	ft_printf("%d\n", key);
	
	if (key == KEY_L)
		data->shift_x -= SHIFT_VAL;
	if (key == KEY_U)
		data->shift_y -= SHIFT_VAL;
	if (key == KEY_R)
		data->shift_x += SHIFT_VAL;
	if (key == KEY_D)
		data->shift_y += SHIFT_VAL;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	plot_map(data);
	return(0);
}

int	main(int argc, char **argv) //int argc, char **argv
{
	t_fdf	*data;
	char	*map_file_name;

	data = (t_fdf *)malloc(sizeof(t_fdf));
	map_file_name = argv[1];
	read_map(map_file_name, data);
	data->zoom = 30;
	
	// /////  TEST  /////
	print_z_matrix(data); /////////////////////////////////////////////////

	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");
	// plot_line(1, 1, 2, 2, data);
	// plot_line(500, 200, 50, 900, data);
	
	plot_map(data);
	mlx_key_hook(data->win_ptr, deal_key, data);
	mlx_loop(data->mlx_ptr);

	// /// Free data ///
	// int i = 0; 
	// while (i < data->height)
	// 	free(data->z_matrix[i++]);
	// free(data->z_matrix);
	// free(data);
	return (argc);
}

// // Test GNL

// int	main()
// {
// 	size_t	fd;
// 	char *s;

// 	fd = open("test.txt", O_RDONLY); // protection???
// 	get_next_line(fd, &s);
// 	printf("%s\n", s);
// 	close(fd);
// }