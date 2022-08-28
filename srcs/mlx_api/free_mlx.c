#include "mlx_api.h"

void	api_free_graphics_linux(void *mlx_ptr, void *win_ptr, void *img_prt)
{
	mlx_destroy_image(mlx_ptr, img_prt);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
}

void	api_free_graphics_macos(void *mlx_ptr, void *win_ptr, void *img_prt)
{
	mlx_destroy_image(mlx_ptr, img_prt);
	mlx_destroy_window(mlx_ptr, win_ptr);
}

///////////////////////////////////////////////////////////


void	api_put_pixel(t_graphics *api_data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < api_data->width && y >= 0 && y < api_data->height)
	{
		dst = api_data->img_addr
			+ (y * api_data->line_length + x * (api_data->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}
