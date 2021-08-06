#include "fractol.h"

// int *colours(void)
// {
// 	int *colours;

// 	colours = malloc(sizeof(int) * 12);
// 	colours[0] = 0xd16ba5;
// 	colours[1] = 0xc777b9;
// 	colours[2] = 0xba83ca;
// 	colours[3] = 0xaa8fd8;
// 	colours[4] = 0x9a9ae1;
// 	colours[5] = 0x8aa7ec; 
// 	colours[6] = 0x79b3f4;
// 	colours[7] = 0x69bff8;
// 	colours[8] = 0x52cffe;
// 	colours[9] = 0x41dfff;
// 	colours[10] = 0x46eefa;
// 	colours[11] = 0x5ffbf1;
// 	return (colours);
// }

// int	choose_colour(int iter)
// {
// 	int colour;

// 	colour = 0;

// 	// if (iter > 5)
// 	// 	colour = 0xD66853;
// 	// else 
// 	// 	colour = 0xDA7663;
// 	// if (iter < 5)
// 	// 	colour = 0x00FFFFFF;
// 	// else
// 	// 	colour = 0xFF5A4857;	

// 	if (iter > 40)
// 		colour = 0x212D40;
// 	else if (iter > 20)
// 		colour = 0x364156;
// 	else if (iter > 10)
// 		colour = 0x5A4857;
// 	else if (iter > 5)
// 		colour = 0xD66853;
// 	else if (iter > 3)
// 		colour = 0xDA7663;
// 	else 
// 		colour = 0xdd8271;		
// 	return (colour);	
// }

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	paint_fractal(t_vars *vars)
{
	// // int *colour;
	// // int m;
	// int col;

	// col = 0;

	// // m = vars->iter - log(log(vars->iter)) / log(2.0);
	// // if (vars->iter == MAX)
	// // 	pixel_put(vars, vars->line, vars->column, 0x00000000);
	// if (vars->iter < vars->max)
	// {
	// 	// colour = colours();
	// 	col = choose_colour(vars->iter);
	// 	// pixel_put(vars, vars->line, vars->column, colour[vars->iter]);
	// 	pixel_put(vars, vars->line, vars->column, col);

	// }
 
	double t = (double)vars->iter / (double)vars->max;
	// printf("%f\n", t);
	int r = (int)(10*(1-t)*t*t*t*255);
 	int g = (int)(30*(1-t)*(1-t)*t*t*255);
 	int b =  (int)(8*(1-t)*(1-t)*(1-t)*t*255);
	// printf("%d\n", r); 
	// printf("%d\n", g); 
	// printf("%d\n", b); 
	pixel_put(vars, vars->line, vars->column, create_rgb(r, g, b));
}

void	draw_burning_ship(t_vars *vars)
{
	vars->x = vars->c_re;
	vars->y = vars->c_im;
	vars->iter = 0;
	while ((pow(vars->x, 2.0) + pow(vars->y, 2.0) <= 4) && vars->iter < vars->max)
	{
		vars->x_new = pow(vars->x, 2.0) - pow(vars->y, 2.0) + vars->c_re;
		vars->y = -2.0 * fabs(vars->x * vars->y) + vars->c_im;
		vars->x = vars->x_new;
		vars->iter++;
	}
	// printf("%d\n", vars->iter);
	paint_fractal(vars);
}

void	draw_julia(t_vars *vars)
{
	vars->x = vars->c_re;
	vars->y = vars->c_im;
	vars->iter = 0;
	while ((pow(vars->x, 2.0) + pow(vars->y, 2.0) <= 4) && vars->iter < vars->max)
	{
		vars->x_new = pow(vars->x, 2.0) - pow(vars->y, 2.0) + JU_RE;
		vars->y = 2.0 * vars->x * vars->y + JU_IM;
		vars->x = vars->x_new;
		vars->iter++;
	}
	// printf("%d\n", vars->iter);
	paint_fractal(vars);
}

// void	draw_mandelbrot(t_vars *vars)
// {
// 	vars->x = 0;
// 	vars->y = 0;
// 	vars->iter = 0;
// 	while ((pow(vars->x, 2.0) + pow(vars->y, 2.0) <= (1 << 16) && vars->iter < vars->max))
// 	{
// 		vars->x_new = pow(vars->x, 2.0) - pow(vars->y, 2.0) + vars->c_re;
// 		vars->y = 2 * vars->x * vars->y + vars->c_im;
// 		vars->x = vars->x_new;
// 		vars->iter++;
// 	}
// 	if (vars->iter < vars->max)
// 	{
// 		vars->log_zn = log(pow(vars->x, 2.0) + pow(vars->y, 2.0)) / 2;
// 		vars->nu = log(vars->log_zn / log(2)) / log(2);
// 		// vars->iter = vars->iter + 1 - vars->nu;
// 	}
// 	// printf("%f\n", vars->iter);
// 	paint_fractal(vars);
// }

void	draw_mandelbrot(t_vars *vars)
{
	vars->x = 0;
	vars->y = 0;
	vars->iter = 0;
	while ((pow(vars->x, 2.0) + pow(vars->y, 2.0) <= 4) && vars->iter < vars->max)
	{
		vars->x_new = pow(vars->x, 2.0) - pow(vars->y, 2.0) + vars->c_re;
		vars->y = 2 * vars->x * vars->y + vars->c_im;
		vars->x = vars->x_new;
		vars->iter++;
	}
	// printf("%f\n", vars->iter);
	paint_fractal(vars);
}

void	draw_fractal(t_vars *vars)
{
	// const float b = 256.0;
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length,
								&vars->endian);
	vars->column = 0;
	while (vars->column < HEIGHT)
	{
		vars->line = 0;
		while (vars->line < WIDTH)
		{
			vars->c_re = (vars->line - WIDTH  / 2.0) * 4.0  / WIDTH * vars->zoom + vars->move_x;
			vars->c_im = (vars->column - HEIGHT/ 2.0) * 4.0 / WIDTH * vars->zoom + vars->move_y;
			// vars->c_re = vars->line / vars->zoom + vars->move_x;
			// vars->c_im = vars->column / vars->zoom + vars->move_y;
			choose_fractol(vars);
			vars->line++;
		}
		vars->column++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

void	choose_fractol(t_vars *vars)
{
	if (!ft_strncmp(vars->arg, "Julia", 6) || !ft_strncmp(vars->arg, "2", 5) || !ft_strncmp(vars->arg, "julia", 6))
		draw_julia(vars);
	else if (!ft_strncmp(vars->arg, "1", 5) || !ft_strncmp(vars->arg, "Mandelbrot", 15) || !ft_strncmp(vars->arg, "mandelbrot", 15))
		draw_mandelbrot(vars);
	else if (!ft_strncmp(vars->arg, "3", 5) || !ft_strncmp(vars->arg, "Burning_ship", 15) || !ft_strncmp(vars->arg, "burning_ship", 15))
		draw_burning_ship(vars);
}

int	key_hook(int key, t_vars *vars)
{
	if (key == UP)
		vars->move_y += 30 / STEP;
	else if (key == DOWN)
		vars->move_y -= 30 / STEP;
	else if (key == LEFT)
		vars->move_x += 30 / STEP;
	else if (key == RIGHT)
		vars->move_x -= 30 / STEP;
	// if (key == UP)
	// 	vars->move_y -= 0.003 * STEP / vars->zoom;
	// else if (key == DOWN)
	// 	vars->move_y += 0.003 * STEP / vars->zoom;
	// else if (key == LEFT)
	// 	vars->move_x -= 0.003 * STEP / vars->zoom;
	// else if (key == RIGHT)
	// 	vars->move_x += 0.003 * STEP / vars->zoom;	
		// printf("x=%f, y=%f\n", vars->move_x, vars->move_y);
	// if (key == UP || key == DOWN || key == RIGHT || key == LEFT)
	// 	move(key, vars);
	// keycode = 1; 
	// (void)vars->win;
	if (key == ESC)
		exit (1);
	if (key == UP_PREC)
		vars->max += 50;
	if (key == DOWN_PREC)
		vars->max -= 50;
	// printf("iter=%f\n", vars->iter);	
	draw_fractal(vars);
	// draw_image4(vars);
	// if (key == SCROLL_IN)
		// exit (3);
	// printf("Hello from key_hook!\n");
	return (0);
}

void	zoom_in(int x, int y, t_vars *vars)
{
	int a = x + y;
	a++;
	// x = 0;
	// y = 0;
	// vars->move_x = (x / vars->zoom + vars->x) - (x / (vars->zoom));
	// vars->move_y = (y / vars->zoom + vars->y) - (y / (vars->zoom));
	vars->zoom *= 1.3;
	// vars->max++;
}

void	zoom_out(int x, int y, t_vars *vars)
{
	// x = 0;
	// y = 0;
	int a = x + y;
	a++;
	// vars->move_x = (x / vars->zoom + vars->x)  - (x / (vars->zoom));
	// vars->move_y = (y / vars->zoom + vars->y) - (y / (vars->zoom));
	vars->zoom /= 1.3;
	// vars->max--;
}

int	zoom_mouse(int button, int x, int y, t_vars *vars)
{
	// x = 0;
	// y = 0;
	if (button == SCROLL_IN)
		zoom_in(x, y, vars);
		// exit (2);
		// vars->zoom *= STEP_Z;
	else if (button == SCROLL_OUT)
		zoom_out(x, y, vars);
		// vars->zoom /= STEP_Z;
	// printf("%f\n", vars->zoom);	
	draw_fractal(vars);
	// draw_image2(vars);
	return (0);
}

void	init_data(t_vars *vars)
{
	vars->zoom = 1;
	vars->move_x = 0;
	vars->move_y = 0;
	vars->max = 50;
}

int main(int argc, char **argv)
{
	t_vars vars;

	check_args(argc, argv, &vars);
	init_data(&vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Fractol");
	draw_fractal(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, zoom_mouse, &vars);
	mlx_loop(vars.mlx);
	return (0);
}