#include "fractol.h"

int	choose_colour(int iter)
{
	int colour;

	if (iter > 40)
		colour = 0x212D40;
	else if (iter > 20)
		colour = 0x364156;
	else if (iter > 10)
		colour = 0x5A4857;
	else if (iter > 5)
		colour = 0xD66853;
	else if (iter > 3)
		colour = 0xDA7663;
	else 
		colour = 0xdd8271;		
	return (colour);	
}

void	paint_fractal(t_vars *vars)
{
	int colour;

	colour = 0;
	if (vars->iter == MAX)
		pixel_put(vars, vars->line, vars->column, 0x11151C);
	// if (vars->iter == MAX)
	else
		colour = choose_colour(vars->iter);
		pixel_put(vars, vars->line, vars->column, colour);

}

void	draw_julia(t_vars *vars)
{
	vars->x = 0;
	vars->y = 0;
	vars->iter = 0;
	while ((pow(vars->x, 2.0) + pow(vars->y, 2.0) <= 4) && vars->iter < MAX)
	{
		vars->x_new = pow(vars->x, 2.0) - pow(vars->y, 2.0) + JU_RE;
		vars->y = 2 * vars->x * vars->y + JU_IM;
		vars->x = vars->x_new;
		vars->iter++;
	}
	printf("%d\n", vars->iter);
	paint_fractal(vars);
}

void	draw_mandelbrot(t_vars *vars)
{
	vars->x = 0;
	vars->y = 0;
	vars->iter = 0;
	while ((pow(vars->x, 2.0) + pow(vars->y, 2.0) <= 4) && vars->iter < MAX)
	{
		vars->x_new = pow(vars->x, 2.0) - pow(vars->y, 2.0) + vars->c_re;
		vars->y = 2 * vars->x * vars->y + vars->c_im;
		vars->x = vars->x_new;
		vars->iter++;
	}
	printf("%d\n", vars->iter);
	paint_fractal(vars);
}

void	draw_fractal(t_vars *vars)
{
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length,
								&vars->endian);
	vars->column = 0;
	while (vars->column < HEIGHT)
	{
		vars->line = 0;
		while (vars->line < WIDTH)
		{
			vars->c_re = (vars->line - WIDTH / 2.0) * 4.0 / WIDTH;
			vars->c_im = (vars->column - HEIGHT / 2.0) * 4.0 / WIDTH;
			// draw_mandelbrot(vars);
			choose_fractol(vars);
			vars->line++;
		}
		vars->column++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

void	choose_fractol(t_vars *vars)
{
	if (!ft_strncmp(vars->arg, "Julia", 6) || !ft_strncmp(vars->arg, "2", 5))
		draw_julia(vars);
	else if (!ft_strncmp(vars->arg, "1", 5) || !ft_strncmp(vars->arg, "Mandelbrot", 15))
		draw_mandelbrot(vars);
	// else if (!ft_strncmp(vars->arg, "3", 5) || !ft_strncmp(vars->arg, "Burning_ship", 15))
	// 	draw_burning_ship(vars);
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
	// if (key == UP || key == DOWN || key == RIGHT || key == LEFT)
	// 	move(key, vars);
	// keycode = 1; 
	(void)vars->win;
	if (key == ESC)
		exit (1);
	if (key == UP_PREC)
		vars->iter++;
	if (key == DOWN_PREC)
		vars->iter--;
	// draw_image2(vars);
	// draw_image4(vars);
	// if (key == SCROLL_IN)
		// exit (3);
	// printf("Hello from key_hook!\n");
	return (0);
}

int main(int argc, char **argv)
{
	t_vars vars;

	check_args(argc, argv, &vars);
	// init_data(vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Fractol");
	draw_fractal(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	// mlx_mouse_hook(vars.win, zoom_mouse, &vars);
	mlx_loop(vars.mlx);
	return (0);
}