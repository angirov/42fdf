#include "fdf.h"

void cast_rays(t_player	*p)
{
	int		screen = 100;	//px
	// int		fov = 90;		// degrees
	
	// double	posX = p->loc.x;
	// double	posY = p->loc.y;  //x and y start position
	
	// double	dirX = -1, dirY = 0; //initial direction vector W?
	t_loc	dir_vec = dir2vec(p->direction);
	t_loc	center = add_vecs(p->loc, dir_vec);
	t_loc	plane_vec = dir2vec(p->direction + dtr(90));
	printf(">>>>> TEST3\n");

	draw_line(p->loc, center, p->game->grid.scale, RED, p->game->game->graphics);
	draw_line(center, add_vecs(center, plane_vec), p->game->grid.scale, WHITE, p->game->game->graphics);
	draw_line(center, add_vecs(center, sc_mult(plane_vec, -1)), p->game->grid.scale, WHITE, p->game->game->graphics);
	// double	planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	printf(">>>>> TEST33\n");

	for(int x = 0; x < screen; x++)
	{
		
		t_loc	rayDir;
		double	cameraX;
		//calculate ray position and direction
		cameraX = 2 * x / (double)screen - 1; //x-coordinate in camera space
		rayDir = add_vecs(center, sc_mult(plane_vec, cameraX));
		draw_line(p->loc, rayDir, p->game->grid.scale, RED, p->game->game->graphics);
	}
	// 	double	deltaDistX = sqrt(1 + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x));
	// 	double	deltaDistY = sqrt(1 + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y));

	// 	//which box of the map we're in
	// 	int mapX = (int)p->loc.x;
	// 	int mapY = (int)p->loc.y;
	// 	//length of ray from current position to next x or y-side
	// 	double sideDistX;
	// 	double sideDistY;
	// 	//length of ray from one x or y-side to next x or y-side
	// 	// double deltaDistX = (rayDir.x == 0) ? 1e30 : ft_abs(1 / rayDir.x);
	// 	// double deltaDistY = (rayDir.y == 0) ? 1e30 : ft_abs(1 / rayDir.y);
	// 	// double perpWallDist;//////////////////////////////////////
	// 	//what direction to step in x or y-direction (either +1 or -1)
	// 	int stepX;
	// 	int stepY;
	// 	int hit = 0; //was there a wall hit?
	// 	int side; //was a NS or a EW wall hit?

		// //calculate step and initial sideDist
		// if (rayDir.x < 0)
		// {
		// 	stepX = -1;
		// 	sideDistX = (p->loc.x - mapX) * deltaDistX;
		// }
		// else
		// {
		// 	stepX = 1;
		// 	sideDistX = (mapX + 1.0 - p->loc.x) * deltaDistX;
		// }
		// if (rayDir.y < 0)
		// {
		// 	stepY = -1;
		// 	sideDistY = (p->loc.y - mapY) * deltaDistY;
		// }
		// else
		// {
		// 	stepY = 1;
		// 	sideDistY = (mapY + 1.0 - p->loc.y) * deltaDistY;
		// }
		// // perform DDA
		// while (hit == 0)
		// {
		// 	//jump to next map square, either in x-direction, or in y-direction
		// 	if (sideDistX < sideDistY)
		// 	{
		// 		sideDistX += deltaDistX;
		// 		mapX += stepX;
		// 		side = 0;
		// 	}
		// 	else
		// 	{
		// 		sideDistY += deltaDistY;
		// 		mapY += stepY;
		// 		side = 1;
		// 	}
		// 	//Check if ray has hit a wall
		// 	if (p->game->map[mapX*24 + mapY] > 0)
		// 		hit = 1;
		// }
		// printf("side: %d\n", side);
	// }
}
