/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/05/25 22:19:51 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



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
		{
			printf("%2d/", data->matrix[j][i].x);
			printf("%2d/", data->matrix[j][i].y);
			printf("%2d ", data->matrix[j][i].z);
			i++;
		}
		i = 0;
		j++;
		printf("\n");
	}
	printf("finish printing matrix\n");
}
///////////////////////////////////////////////////////////////////////////////////

t_fdf *ft_init_data(char *map_file_name)
{
	t_fdf	*data;

	data = (t_fdf *)malloc(sizeof(t_fdf));
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

void	ft_check_input(int argc, char **argv)
{
	if (argc != 2 || !argv[0][0])
	{
		perror("bad input");
		exit(1);
	}
	else
		return;
}

int	main(int argc, char **argv)
{
	t_fdf	*data;

	ft_check_input(argc, argv);
	data = ft_init_data(argv[1]);

	// /////  TEST  /////
	print_matrix(data); /////////////////////////////////////////////////

	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_error(data, "mlx_init failed");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, TITLE);
	if (!data->mlx_ptr)
		ft_error(data, "mlx_new_window failed");
	data->img_prt = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img_prt)
		ft_error(data, "mlx_new_image failed");

	plot_map(data);
	mlx_key_hook(data->win_ptr, deal_key, data);
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