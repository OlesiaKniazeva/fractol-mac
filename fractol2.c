#include "fractol.h"


void	check_args(int argc, char **argv, t_vars *vars)
{
	if (argc != 2 || (ft_strncmp(argv[1], "Julia", 6) && ft_strncmp(argv[1], "1", 5)\
	 && ft_strncmp(argv[1], "2", 5) && ft_strncmp(argv[1], "3", 5)\
	  && ft_strncmp(argv[1], "Mandelbrot", 15) && ft_strncmp(argv[1], "Burning_ship", 15)))
	{
		printf("%s\n", "\nChoose which fractal to show, write number of fractal or its name as argument to see it:\n1 - Mandelbrot\n 2 - Julia\n 3 - Burning_ship\n");
		exit (1);
	}
}

int	key_hook(int key, t_vars *vars)
{
	// if (key == UP)
	// 	vars->move_y -= 0.003 * STEP / vars->zoom;
	// else if (key == DOWN)
	// 	vars->move_y += 0.003 * STEP / vars->zoom;
	// else if (key == LEFT)
	// 	vars->move_x -= 0.003 * STEP / vars->zoom;
	// else if (key == RIGHT)
	// 	vars->move_x += 0.003 * STEP / vars->zoom;
	if (key == UP || key == DOWN || key == RIGHT || key == LEFT)
		move(key, vars);
	// keycode = 1; 
	(void)vars->win;
	if (key == ESC)
		exit (1);
	if (key == UP_PREC)
		vars->iter++;
	if (key == DOWN_PREC)
		vars->iter--;
	// draw_image2(vars);
	draw_image4(vars);
	// if (key == SCROLL_IN)
		// exit (3);
	// printf("Hello from key_hook!\n");
	return (0);
}
void	choose_fractol2(t_vars *vars)
{
	if (!ft_strncmp(vars->arg, "Julia", 6) || !ft_strncmp(vars->arg, "2", 5))
		draw_julia2(vars);
	else if (!ft_strncmp(vars->arg, "1", 5) || !ft_strncmp(vars->arg, "Mandelbrot", 15))
		draw_mandelbrot2(vars);
	else if (!ft_strncmp(vars->arg, "3", 5) || !ft_strncmp(vars->arg, "Burning_ship", 15))
		draw_burning_ship2(vars);
}

int	zoom_mouse2(int button, int x, int y, t_vars *vars)
{
	x = 0;
	y = 0;
	if (button == SCROLL_IN)
		vars->zoom *= pow(1.001, STEP);
	else if (button == SCROLL_OUT)
		vars->zoom /= pow(1.001, STEP);
	// draw_image2(vars);
	draw_image4(vars);
	return (0);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	paint2(t_vars *vars, int i)
{
	double	t;

	t = (double)i / (double)vars->iter;
	if (i < vars->iter)
		pixel_put(vars, vars->x, vars->y, create_rgb(
				(int)(10 * (1 - t) * pow(t, 3) * 255),
				(int)(20 * pow((1 - t), 2) * pow(t, 2) * 255),
				(int)(2 * pow((1 - t), 3) * t * 255)));
		// pixel_put(vars, co->x, co->y, 0x00FFFFFF);
	// else 
	// 	pixel_put(vars, co->x, co->y, 0x00000000);
}


void	pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_image4(t_vars *vars)
{
	
}

int main(int argc, char **argv)
{
	t_vars vars;

	check_args(argc, argv, &vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Fractol")
	draw_image4(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, zoom_mouse2, &vars);
	mlx_loop(vars.mlx);
	return (0);
}