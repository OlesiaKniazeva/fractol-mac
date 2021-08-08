#include "fractol.h"

int	key_hook(int key, t_vars *vars)
{
	printf("%f\n", vars->zoom);
	if (key == DOWN)
		vars->move_y += 0.3 * vars->zoom;
	else if (key == UP)
		vars->move_y -= 0.3 * vars->zoom;
	else if (key == RIGHT)
		vars->move_x += 0.3 * vars->zoom;
	else if (key == LEFT)
		vars->move_x -= 0.3 * vars->zoom;
	if (key == ESC)
		exit (1);
	if (key == UP_PREC)
		vars->max += 50;
	if (key == DOWN_PREC)
		vars->max -= 50;
	draw_fractal(vars);
	return (0);
}

int	zoom_mouse(int button, int x, int y, t_vars *vars)
{
	x = 0;
	y = 0;
	if (button == SCROLL_IN)
		vars->zoom *= 1.3;
	else if (button == SCROLL_OUT)
		vars->zoom /= 1.3;
	draw_fractal(vars);
	return (0);
}
