/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:11 by vangirov          #+#    #+#             */
/*   Updated: 2022/05/07 14:24:08 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(const char *map_file_name)
{
	char	*line;
	size_t	fd;
	int		height;

	fd = open(map_file_name, O_RDONLY); // protection???
	height = 0;
	while (get_next_line(fd, &line))
	{
		height++;
		free(line);
	}
	close(fd);
	return height;
}

int	ft_toknum(const char *str, char c)
{
	int	num;
	int	intoken;

	num = 0;
	intoken = 0;
	while (*str)
	{
		if (*str != c && intoken == 0)
		{
			num++;
			intoken = 1;
		}
		else if (*str == c && intoken == 1)
			intoken = 0;
		str++;
	}
	return (num);
}

int	get_width(const char *map_file_name)
{
	size_t	fd;
	char	*line;
	int		width;

	fd = open(map_file_name, O_RDONLY); // protection???
	get_next_line(fd, &line); // protection???
	width = ft_toknum(line, ' ');
	// while (get_next_line(fd, &line))
	// {
	// 	ft_printf("%s", line);
	// }
	free(line);
	close(fd);
	return (width);
}

void	fill_matrix(const char *map_file_name, t_fdf *data, int height, int width)
{
	size_t	fd;
	char	*line;
	char	**array;
	int		j;
	int		i;

	fd = open(map_file_name, O_RDONLY); // protection???
	j = 0;
	while (j < height)
	{
		array = ft_split(get_next_line(fd, &line), ' ');
		ft_printf("working with line [%d]: %s\n", j, line); //////////////////////
		i = 0;
		while (i < width)
		{
			data->z_matrix[j][i] = ft_atoi(array[i]);
			free(array[i]);
			ft_printf("free_array[%d][%d]\n", j, i); /////////////////////////////
			i++;
		}
		// free(array[i]);
		free(array);
		free(line);
		j++;
	}
	close(fd);
	ft_printf("TEST\n"); //////////////////////
}

void	read_map(const char *map_file_name, t_fdf *data)
{
	int	j;

	data->height = get_height(map_file_name);
	data->width = get_width(map_file_name);
	data->z_matrix = (int **)malloc(data->height * sizeof(int *));

	j = 0;
	while (j < data->height)
		(data->z_matrix)[j++] = (int *)malloc(data->width * sizeof(int));
	fill_matrix(map_file_name, data, data->height, data->width);
}

// #include <stdio.h>
// int	main()
// {
// 	char	str[] ="_11__22__33_";
// 	char	c = '_';
// 	char	**arr;
// 	int		toknum;

// 	toknum = ft_toknum(str, c);
// 	arr = ft_split(str, c);
// 	for (int i = 0; i <= toknum; i++)
// 		printf(">>> %s\n", arr[i]);
// }
