/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:05:05 by vangirov          #+#    #+#             */
/*   Updated: 2022/05/19 10:50:26 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>

# include <mlx.h>
# include "libft.h"
# include "ft_printf.h"

typedef	struct s_fdf
{
	int	width;
	int	height;
	int	**z_matrix;
	int	zoom;
	int	color;
	float	angle;
	int	shift_x;
	int	shift_y;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_fdf;


void	read_map(const char *map_file_name, t_fdf *data);
int		get_width(const char *file_name);
void	plot_line(float x, float y, float x1, float y1, t_fdf *data);
void	plot_map(t_fdf *data);
void	isometric(float *x, float *y, int z, t_fdf *data);

#endif