#include "fractol.h"

void	draw_burning_ship(t_vars *vars)
{
	vars->x = vars->c_re;
	vars->y = vars->c_im;
	vars->iter = 0;
	while ((pow(vars->x, 2.0) + pow(vars->y, 2.0) <= 4) \
	&& vars->iter < vars->max)
	{
		vars->x_new = pow(vars->x, 2.0) - pow(vars->y, 2.0) + vars->c_re;
		vars->y = -2.0 * fabs(vars->x * vars->y) + vars->c_im;
		vars->x = vars->x_new;
		vars->iter++;
	}
	paint_fractal(vars);
}

void	draw_julia(t_vars *vars)
{
	vars->x = vars->c_re;
	vars->y = vars->c_im;
	vars->iter = 0;
	while ((pow(vars->x, 2.0) + pow(vars->y, 2.0) <= 4) \
	&& vars->iter < vars->max)
	{
		vars->x_new = pow(vars->x, 2.0) - pow(vars->y, 2.0) + JU_RE;
		vars->y = 2.0 * vars->x * vars->y + JU_IM;
		vars->x = vars->x_new;
		vars->iter++;
	}
	paint_fractal(vars);
}

void	draw_mandelbrot(t_vars *vars)
{
	vars->x = 0;
	vars->y = 0;
	vars->iter = 0;
	while ((pow(vars->x, 2.0) + pow(vars->y, 2.0) <= 4) \
	&& vars->iter < vars->max)
	{
		vars->x_new = pow(vars->x, 2.0) - pow(vars->y, 2.0) + vars->c_re;
		vars->y = 2 * vars->x * vars->y + vars->c_im;
		vars->x = vars->x_new;
		vars->iter++;
	}
	paint_fractal(vars);
}
