/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:05:05 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/10 15:37:26 by vangirov         ###   ########.fr       */
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

# include <mlx.h>
# include "libft.h"
# include "ft_printf.h"

// window
# define WIDTH 1920
# define HEIGHT 1080
# define TITLE "Fdf"

// colors
# define WHITE 0xffffff
# define RED 0xe80c0c

// keys
# define KEY_ESC 65307
# define KEY_L 65361
# define KEY_U 65362
# define KEY_R 65363
# define KEY_D 65364
# define KEY_Q 113
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_Z 122
# define KEY_X 120
# define KEY_1 49
# define KEY_2 50
# define KEY_P 112
# define KEY_I 105

# define SHIFT_VAL 100
# define ANGLE_VAL M_PI/36

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_fdf
{
	int		width;
	int		height;
	t_point	**matrix;
	int		zoom;
	int		color;
	float	angle;
	int		offset_x;
	int		offset_y;
	int		shift_x;
	int		shift_y;
	float	alpha;
	float	beta;
	float	gamma;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_prt;
}	t_fdf;

#define ABS(a) ((a < 0) ? -a : a)
#define MAX(a, b) ((a > b) ? a : b)
#define WHITE 0xffffff
#define RED 0xe80c0c

// make_fdf
void	ft_check_input(int argc, char **argv);
void	ft_init_mlx(t_fdf *data);
t_fdf	*ft_make_data(char *map_file_name);

// read_map.c
int		get_height(const char *map_file_name);
int		get_width(const char *map_file_name);
void	ft_init_point(t_point *p, int x, int y, int z);
void	fill_matrix(const char *map_file_name, t_fdf *data, int height, int width);
void	read_map(const char *map_file_name, t_fdf *data);

// key_hooks.c
int	deal_key(int key, t_fdf *data);


// ploting.c
void	plot_map(t_fdf *data);
t_point	ft_set_point(t_point p, t_fdf *data);
void	plot_line(t_point p0, t_point p1, t_fdf *data);
int		ft_line_color(t_point p0, t_point p1);

// read_map.c
void	read_map(const char *map_file_name, t_fdf *data);
int		get_height(const char *map_file_name);
int		get_width(const char *file_name);
int		ft_set_color(int z);
void	ft_init_point(t_point *p, int x, int y, int z);
void	fill_matrix(const char *map_file_name, t_fdf *data, int height, int width);

// void	isometric(float *x, float *y, float z, t_fdf *data);

/* rotation.c */
void	x_rotate(int *y, int *z, float alpha);
void	y_rotate(int *x, int *z, float beta);
void	z_rotate(int *x, int *y, float gamma);
void	ft_scale_point(t_point *p, t_fdf *data);
void	ft_shift_point(t_point *p, t_fdf *data);

// exit.c
void	ft_error(t_fdf *data, char *message);
void	ft_escape(t_fdf *data);
void	ft_free_data(t_fdf *data);

void	print_matrix(t_fdf *data); //////////////////////////////////

#endif