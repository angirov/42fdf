/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/10 13:21:12 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*data;

	ft_check_input(argc, argv);
	data = ft_make_data(argv[1]);
	plot_map(data);
	mlx_key_hook(data->win_ptr, deal_key, data);
	mlx_loop(data->mlx_ptr);

	return (argc);
}

///////////////////////////////////////////////////////////////////////////////////
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
