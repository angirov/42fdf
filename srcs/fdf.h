/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:05:05 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/28 22:03:59 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* for strerror */
# include <string.h>
# include <errno.h>

/* for perror */
# include <stdio.h> 

# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>

# define _USE_MATH_DEFINES
# include <math.h>
# define SHIFT_VAL 100
# define ANGLE_DIV 36

// window
# define WIDTH 1600
# define HEIGHT 800
# define TITLE "Fdf"

// colors
# define WHITE 0xffffff
# define RED 0xe80c0c

# include "mlx_api.h"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_fpoint
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_fpoint;

typedef struct s_fdf
{
	t_graphics	*graphics;
	int			width;
	int			height;
	t_point		**matrix;
	int			zoom;
	int			z_scale;
	int			proj;
	int			color;
	float		angle;
	int			pivot_x;
	int			pivot_y;
	int			offset_x;
	int			offset_y;
	int			shift_x;
	int			shift_y;
	float		alpha;
	float		beta;
	float		gamma;

}	t_fdf;

# define WHITE 0xffffff
# define RED 0xe80c0c

// make_data
void	ft_check_input(int argc, char **argv);
void	api_init_graphics(t_fdf *data);
t_fdf	*ft_make_data(char *map_file_name);

// read_map.c
int		get_height(const char *map_file_name);
int		get_width(const char *map_file_name);
void	ft_init_point(t_point *p, int x, int y, int z);
void	fill_matrix(const char *map_file_name, \
					t_fdf *data, int height, int width);
void	read_map(const char *map_file_name, t_fdf *data);

// key_hooks.c
int		deal_key(int key, t_fdf *data);
void	ft_proj_isometric(t_fdf *data);
void	ft_proj_parallel(t_fdf *data);

// ploting.c
void	ft_plot_map(t_fdf *data);
t_point	ft_set_point(t_point p, t_fdf *data);
void	ft_plot_line(t_point p0, t_point p1, t_fdf *data);
int		ft_line_color(t_fpoint p0, t_fpoint p1);
void	ft_put_pixel(t_fdf *data, int x, int y, int color);

// read_map.c
void	read_map(const char *map_file_name, t_fdf *data);
int		get_height(const char *map_file_name);
int		get_width(const char *file_name);
int		ft_set_color(int z);
void	ft_init_point(t_point *p, int x, int y, int z);
void	fill_matrix(const char *map_file_name, \
					t_fdf *data, int height, int width);

/* rotation.c */
void	x_rotate(int *y, int *z, float alpha);
void	y_rotate(int *x, int *z, float beta);
void	z_rotate(int *x, int *y, float gamma);
void	ft_scale_point(t_point *p, t_fdf *data);
void	ft_shift_point(t_point *p, t_fdf *data);

/* projection.c */
void	ft_reset_angles(t_fdf *data);
void	ft_isometric(int *x, int *y, int *z);
void	ft_cabinet(int *x, int *y, int *z);
float	ft_abs(float a);
float	ft_max(float a, float b);

// exit.c
void	ft_error(t_fdf *data, char *message);
void	ft_escape(t_fdf *data);
void	ft_free_data(t_fdf *data);
int		ft_destroy(t_fdf *data);

#endif
