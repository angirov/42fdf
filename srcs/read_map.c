/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:11 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/12 22:00:26 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_map(const char *map_file_name, t_fdf *data)
{
	int	j;

	data->height = get_height(map_file_name);
	data->width = get_width(map_file_name);
	data->matrix = (t_point **)malloc(data->height * sizeof(t_point *));
	j = 0;
	while (j < data->height)
		(data->matrix)[j++] = (t_point *)malloc(data->width * sizeof(t_point));
	fill_matrix(map_file_name, data, data->height, data->width);
}

int	ft_set_color(int z)
{
	if (z > 0)
		return (RED);
	else
		return (WHITE);
}

void	ft_init_point(t_point *p, int x, int y, int z)
{
	p->x = x;
	p->y = y;
	p->z = z;
	p->color = ft_set_color(z);
}

void	fill_matrix(const char *map_file_name, \
					t_fdf *data, int height, int width)
{
	size_t	fd;
	char	*line;
	char	**array;
	int		j;
	int		i;

	fd = open(map_file_name, O_RDONLY);
	j = 0;
	while (j < height)
	{
		array = ft_split(get_next_line(fd, &line), ' ');
		i = 0;
		while (i < width)
		{
			ft_init_point(&data->matrix[j][i], i, j, ft_atoi(array[i]));
			free(array[i]);
			i++;
		}
		free(array);
		free(line);
		j++;
	}
	close(fd);
}
