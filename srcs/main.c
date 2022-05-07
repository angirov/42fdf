/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/05/07 18:20:38 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	main(int argc, char **argv) //int argc, char **argv
{
	t_fdf	*data;
	char	*map_file_name;

	data = (t_fdf *)malloc(sizeof(t_fdf));
	map_file_name = argv[1];
	read_map(map_file_name, data);

	/////  TEST  /////
	print_z_matrix(data); /////////////////////////////////////////////////

	// /// Free data ///
	// int i = 0; 
	// while (i < data->height)
	// 	free(data->z_matrix[i++]);
	// free(data->z_matrix);
	// free(data);

	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");

	plot_line(100, 200, 900, 400, data);
	
	// mlx_pixel_put(data->mlx_ptr, data->win_ptr, 5, 5, 0xffffff);
	// mlx_pixel_put(data->mlx_ptr, data->win_ptr, 6, 5, 0xffffff);
	// mlx_pixel_put(data->mlx_ptr, data->win_ptr, 7, 5, 0xffffff);
	// mlx_pixel_put(data->mlx_ptr, data->win_ptr, 8, 5, 0xffffff);
	mlx_loop(data->mlx_ptr);
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