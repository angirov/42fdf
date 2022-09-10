#include "fdf.h"

t_loc	dir2vec(double radians)
{
	t_loc	res;

	res.x = cos(radians);
	res.y = sin(radians);
	return (res);
}

t_loc	add_vecs(t_loc vec1, t_loc vec2)
{
	t_loc	res;

	res.x = vec1.x + vec2.x;
	res.y = vec1.y + vec2.y;
	return (res);
}

t_loc	sc_mult(t_loc vec, double scalar)
{
	t_loc	res;

	res.x = vec.x * scalar;
	res.y = vec.y * scalar;
	return (res);
}

double	rtd(double radians)
{
	return (radians * 180 / M_PI);
}

double	dtr(double degrees)
{
	return (degrees / 180 * M_PI);
}

double ft_abs(double num)
{
	if (num >= 0)
		return (num);
	else
		return (-num);
}
