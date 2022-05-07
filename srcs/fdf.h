/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:05:05 by vangirov          #+#    #+#             */
/*   Updated: 2022/05/07 18:46:03 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>

#include <mlx.h>
# include "libft.h"
# include "ft_printf.h"

typedef	struct s_fdf
{
	int	width;
	int	height;
	int	**z_matrix;

	void	*mlx_ptr;
	void	*win_ptr;
}	t_fdf;


void	read_map(const char *map_file_name, t_fdf *data);
int		get_width(const char *file_name);
void	plot_line(int x0, int x1, int y0, int y1, t_fdf *data);

#endif