/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:03:50 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/12 22:46:25 by vangirov         ###   ########.fr       */
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

int	get_width(const char *map_file_name)
{
	int		fd;
	char	*line;
	int		width;

	fd = open(map_file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_fdprintf(2, "Error: %s: %s\n", strerror(errno), map_file_name);
		exit(1);
	}
	get_next_line(fd, &line);
	width = ft_toknum(line, ' ');
	free(line);
	close(fd);
	return (width);
}

int	get_height(const char *map_file_name)
{
	int		fd;
	char	*line;
	int		height;

	fd = open(map_file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_fdprintf(2, "Error: %s: %s\n", strerror(errno), map_file_name);
		exit(1);
	}
	height = 0;
	while (get_next_line(fd, &line))
	{
		height++;
		free(line);
	}
	close(fd);
	return (height);
}
