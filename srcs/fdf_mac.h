/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mac.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:05:05 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/10 20:15:20 by vangirov         ###   ########.fr       */
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

// # include <mlx.h>
// # include "../libs/minilibx_macos/mlx.h"
# include "../libs/minilibx_mms_20191025_beta/mlx.h"

# include "../libs/libft/libft.h"
# include "../libs/libft_printf/ft_printf.h"

// window
# define WIDTH 1600
# define HEIGHT 800
# define TITLE "Fdf"

// colors
# define WHITE 0xffffff
# define RED 0xe80c0c

// keys
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
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
	int		pivot_x;
	int		pivot_y;
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
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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
void	ft_proj_isometric(t_fdf *data);
void	ft_proj_parallel(t_fdf *data);

// ploting.c
void	plot_map(t_fdf *data);
t_point	ft_set_point(t_point p, t_fdf *data);
void	plot_line(t_point p0, t_point p1, t_fdf *data);
int		ft_line_color(t_point p0, t_point p1);
void	ft_put_pixel(t_fdf *data, int x, int y, int color);

// read_map.c
void	read_map(const char *map_file_name, t_fdf *data);
int		get_height(const char *map_file_name);
int		get_width(const char *file_name);
int		ft_set_color(int z);
void	ft_init_point(t_point *p, int x, int y, int z);
void	fill_matrix(const char *map_file_name, t_fdf *data, int height, int width);

/* rotation.c */
void	x_rotate(int *y, int *z, float alpha);
void	y_rotate(int *x, int *z, float beta);
void	z_rotate(int *x, int *y, float gamma);
void	ft_scale_point(t_point *p, t_fdf *data);
void	ft_shift_point(t_point *p, t_fdf *data);
void	ft_isometric(int *x, int *y, int *z);

// exit.c
void	ft_error(t_fdf *data, char *message);
void	ft_escape(t_fdf *data);
void	ft_free_data(t_fdf *data);
int		ft_destroy(t_fdf *data);

void	print_matrix(t_fdf *data); //////////////////////////////////

#endif