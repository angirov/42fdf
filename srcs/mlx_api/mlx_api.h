#ifndef MLX_API_H
# define MLX_API_H

# if defined(__linux__)
#  include "libft.h"
#  include "ft_printf.h"
#  include <mlx.h>
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_UP 65362
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
#  define KEY_Q 113
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_Z 122
#  define KEY_X 120
#  define KEY_1 49
#  define KEY_2 50
#  define KEY_3 51
#  define KEY_4 52
#  define KEY_P 112
#  define KEY_I 105
#  define KEY_C 99

# elif defined(__APPLE__)
#  include "../libs/minilibx_macos/mlx.h"
#  include "../libs/libft/libft.h"
#  include "../libs/libft_printf/ft_printf.h"

#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_UP 126
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_Q 12
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_Z 6
#  define KEY_X 7
#  define KEY_1 18
#  define KEY_2 19
#  define KEY_3 20
#  define KEY_4 21
#  define KEY_P 35
#  define KEY_I 34
#  define KEY_C 8

# endif

void	ft_free_mlx_linux(void *mlx_ptr, void *win_ptr, void *img_prt);
void	ft_free_mlx_macos(void *mlx_ptr, void *win_ptr, void *img_prt);

#endif