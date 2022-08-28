/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:03:50 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/28 22:03:59 by vangirov         ###   ########.fr       */
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

void	api_init_graphics(t_fdf *data)
{
	data->graphics->mlx_ptr = mlx_init();
	if (!data->graphics->mlx_ptr)
		ft_error(data, "mlx_init failed");
	data->graphics->win_ptr = mlx_new_window(data->graphics->mlx_ptr, WIDTH, HEIGHT, TITLE);
	if (!data->graphics->mlx_ptr)
		ft_error(data, "mlx_new_window failed");
	data->graphics->img_prt = mlx_new_image(data->graphics->mlx_ptr, WIDTH, HEIGHT);
	if (!data->graphics->img_prt)
		ft_error(data, "mlx_new_image failed");
	data->graphics->img_addr = mlx_get_data_addr(data->graphics->img_prt,
			&data->graphics->bits_per_pixel, &data->graphics->line_length,
			&data->graphics->endian);
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
