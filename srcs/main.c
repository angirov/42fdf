/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/05/25 14:46:50 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define _USE_MATH_DEFINES
#include <math.h>
#define KEY_ESC 65307
#define KEY_L 65361
#define KEY_U 65362
#define KEY_R 65363
#define KEY_D 65364
#define KEY_A 97
#define KEY_S 115
#define SHIFT_VAL 100
#define ANGLE_VAL M_PI/16

///////////////////////////////////////////////////////////////////////////////////
#include <stdio.h> /////////////////////////////////////////////////
void	print_matrix(t_fdf *data) //////////////////////////////////
{
	printf("start printing matrix\n");
	int	j = 0;
	int	i = 0;

	while (j < data->height)
	{
		while (i < data->width)
			printf("%3d", data->matrix[j][i++].z);
		i = 0;
		j++;
		printf("\n");
	}
	printf("finish printing matrix\n");
}


// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }
///////////////////////////////////////////////////////////////////////////////////

void ft_escape(t_fdf *data)
{
	int i = 0; 
	while (i < data->height)
		free(data->matrix[i++]);
	free(data->matrix);
	free(data);
	exit(1);
}
int	deal_key(int key, t_fdf *data)
{
	ft_printf("%d\n", key);
	
	if (key == KEY_ESC)
		ft_escape(data);
	if (key == KEY_L)
		data->shift_x -= SHIFT_VAL;
	if (key == KEY_U)
		data->shift_y -= SHIFT_VAL;
	if (key == KEY_R)
		data->shift_x += SHIFT_VAL;
	if (key == KEY_D)
		data->shift_y += SHIFT_VAL;
	if (key == KEY_A)
		data->angle += ANGLE_VAL;
	if (key == KEY_S)
		data->angle -= ANGLE_VAL;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	plot_map(data);
	return(0);
}

int	bad_input(int argc, char **argv)
{
	if (argc != 2 || !argv[0][0])
		return (1);
	return (0);
}

int	main(int argc, char **argv) //int argc, char **argv
{
	t_fdf	*data;
	char	*map_file_name;

	if (bad_input(argc, argv))
		ft_printf("!!! BAD INPUT !!!\n");
	data = (t_fdf *)malloc(sizeof(t_fdf));
	map_file_name = argv[1];
	read_map(map_file_name, data);
	data->zoom = 20;
	data->angle = 0;
	// /////  TEST  /////
	print_matrix(data); /////////////////////////////////////////////////

	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");
	
	// mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->color);
	
	
	
	// plot_line(1, 1, 2, 2, data);
	// plot_line(500, 200, 50, 900, data);
	
	plot_map(data);
	mlx_key_hook(data->win_ptr, deal_key, data);
	mlx_loop(data->mlx_ptr);

	// /// Free data ///
	// int i = 0; 
	// while (i < data->height)
	// 	free(data->matrix[i++]);
	// free(data->matrix);
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