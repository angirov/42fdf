#include "fdf.h"

#include <fcntl.h>

int	get_height(const char *file_name)
{
	char	*line;
	size_t	fd;
	int		height;

	fd = open(file_name, O_RDONLY); // protection???
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

int	get_width(const char *file_name)
{
	size_t	fd;
	char	*line;
	int		width;

	fd = open(file_name, O_RDONLY); // protection???
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

void	read_file(const char *file_name, fdf *data)
{
	data->height = get_height(file_name);

	ft_printf("height: %d\n", data->height); ////////////////////////////////

	data->width = get_width(file_name);

	ft_printf("width: %d\n", data->width); ////////////////////////////////

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
