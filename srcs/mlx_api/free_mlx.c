#include "mlx_api.h"

void	ft_free_mlx_linux(void *mlx_ptr, void *win_ptr, void *img_prt)
{
	mlx_destroy_image(mlx_ptr, img_prt);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
}

void	ft_free_mlx_macos(void *mlx_ptr, void *win_ptr, void *img_prt)
{
	mlx_destroy_image(mlx_ptr, img_prt);
	mlx_destroy_window(mlx_ptr, win_ptr);
}
