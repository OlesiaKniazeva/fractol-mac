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
	vars->arg = argv[1];
	vars->zoom = 1;
	vars->move_x = 0;
	vars->move_y = 0;
	vars->iter = 50;

	vars->minre = -2.0;
	vars->maxre = 2.0;
	vars->minim = -2.0;
	// vars->maxim = vars->minim + (vars->maxre - vars->minre) * HEIGHT / WIDTH;
	// vars->fact_re = (vars->maxre - vars->minre) / (WIDTH - 1);
	// vars->fact_im = (vars->maxim - vars->minim) / (HEIGHT - 1);
}

t_comp	init_complex(double re, double im)
{
	t_comp	comp;

	comp.re = re;
	comp.im = im;
	return (comp);
}

static void	move(int key, t_vars *vars)
{
	t_comp	move;
	double	diff1;
	double	diff2;

	diff1 = vars->maxre - vars->minre;
	diff2 = vars->maxim - vars->minim;
	if (diff1 < 0)
		diff1 = -diff1;
	if (diff2 < 0)	
		diff2 = -diff2;
	move = init_complex(diff1, diff2);
	if (key == LEFT)
	{
	vars->minre -= move.re * 0.05;
		vars->maxre -= move.re * 0.05;
	}
	else if (key == RIGHT)
	{
		vars->minre += move.re * 0.05;
		vars->maxre += move.re * 0.05;
	}
	else if (key == UP)
	{
		vars->minim += move.im * 0.05;
		vars->maxim += move.im * 0.05;
	}
	else if (key == DOWN)
	{
		vars->minim -= move.im * 0.05;
		vars->maxim -= move.im * 0.05;
	}
	draw_image4(vars);
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

void	pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_burning_ship2(t_vars *vars)
{
	t_comp	z;
	int		i;

	i = 0;
	z = init_complex(vars->pix.re, vars->pix.im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && i < vars->iter)
	{
  	  z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + vars->pix.re, -2.0 * fabs(z.re * z.im) + vars->pix.im);
    	i++;
	}
	paint2(vars, i);
}

// void	draw_burning_ship(t_ps *co, t_comp *pix, t_vars *vars)
// {
// 	t_comp	z;
// 	int		i;

// 	i = 0;
// 	z = init_complex(pix->re, pix->im);
// 	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && i < vars->iter)
// 	{
//   	  z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + pix->re, -2.0 * fabs(z.re * z.im) + pix->im);
//     	i++;
// 	}
// 	paint(vars, co, i); 
// }



// void	draw_mandelbrot(t_ps *co, t_comp *pix, t_vars *vars)
// {
// 	int i;
// 	t_comp	z;

// 	z = init_complex(pix->re, pix->im);
// 	i = 0;
// 	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && i < vars->iter)
// 	{
// 		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + pix->re, 2.0 * z.re * z.im + pix->im);
// 		i++;
// 	}
// 	paint(vars, co, i); 
// }

// void	draw_julia(t_ps *co, t_comp *pix, t_vars *vars)
// {
// 	int		i;
// 	t_comp	z;

// 	z = init_complex(pix->re, pix->im);
// 	i = 0;
// 	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && i < vars->iter)
// 	{
// 		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + JU_RE,
//         2.0 * z.re * z.im + JU_IM);
// 		i++;
// 	}
// 		paint(vars, co, i);
// }



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

void	draw_mandelbrot2(t_vars *vars)
{
	int i;
	t_comp	z;

	z = init_complex(vars->pix.re, vars->pix.im);
	i = 0;
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && i < vars->iter)
	{
		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + vars->pix.re, 2.0 * z.re * z.im + vars->pix.im);
		i++;
	}
	paint2(vars, i); 
}

void	draw_julia2(t_vars *vars)
{
	int		i;
	t_comp	z;

	z = init_complex(vars->pix.re, vars->pix.im);
	i = 0;
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && i < vars->iter)
	{
		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + JU_RE,
        2.0 * z.re * z.im + JU_IM);
		i++;
	}
	printf("%d\n", i);
		paint2(vars, i);
}

// void	init_data(t_ps *co)
// {
// 	co->minre = -2.0;
// 	co->maxre = 2.0;
// 	co->minim = -2.0;
// 	co->maxim = co->minim + (co->maxre - co->minre) * HEIGHT / WIDTH;
// 	co->fact_re = (co->maxre - co->minre) / (WIDTH - 1);
// 	co->fact_im = (co->maxim - co->minim) / (HEIGHT - 1);
// }


int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

// void	paint(t_vars *vars, t_ps *co, int i)
// {
// 	double	t;

// 	t = (double)i / (double)vars->iter;
// 	if (i < vars->iter)
// 		pixel_put(vars, co->x, co->y, create_rgb(
// 				(int)(10 * (1 - t) * pow(t, 3) * 255),
// 				(int)(20 * pow((1 - t), 2) * pow(t, 2) * 255),
// 				(int)(2 * pow((1 - t), 3) * t * 255)));
// 		// pixel_put(vars, co->x, co->y, 0x00FFFFFF);
// 	// else 
// 	// 	pixel_put(vars, co->x, co->y, 0x00000000);
// }

// void	choose_fractol(t_ps *co, t_comp *pix, t_vars *vars)
// {
// 	if (!ft_strncmp(vars->arg, "Julia", 6) || !ft_strncmp(vars->arg, "2", 5))
// 		draw_julia(co, pix, vars);
// 	else if (!ft_strncmp(vars->arg, "1", 5) || !ft_strncmp(vars->arg, "Mandelbrot", 15))
// 		draw_mandelbrot(co, pix, vars);
// 	else if (!ft_strncmp(vars->arg, "3", 5) || !ft_strncmp(vars->arg, "Burning_ship", 15))
// 		draw_burning_ship(co, pix, vars);
// }

void	choose_fractol2(t_vars *vars)
{
	if (!ft_strncmp(vars->arg, "Julia", 6) || !ft_strncmp(vars->arg, "2", 5))
		draw_julia2(vars);
	else if (!ft_strncmp(vars->arg, "1", 5) || !ft_strncmp(vars->arg, "Mandelbrot", 15))
		draw_mandelbrot2(vars);
	else if (!ft_strncmp(vars->arg, "3", 5) || !ft_strncmp(vars->arg, "Burning_ship", 15))
		draw_burning_ship2(vars);
}

// void	draw_image(t_vars *vars)
// {
// 	t_ps	co;
// 	t_comp	pix;

// 	init_data(&co);
// 	co.y = 0;
// 	while (co.y < HEIGHT)
// 	{
// 		pix.im = co.maxim - co.y * co.fact_im + vars->zoom;
// 		co.x = 0;
// 		while (co.x < WIDTH)
// 		{
// 			pix.re = co.minre + co.x * co.fact_re + vars->zoom;
// 			choose_fractol(&co, &pix, vars);
// 			co.x++;
// 		}
// 		co.y++;
// 	}
// }

// void	draw_image2(t_vars *vars)
// {
// 	t_ps	co;
// 	t_comp	pix;

// 	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
// 	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length,
// 								&vars->endian);
// 	init_data(&co);
// 	co.y = 0;
// 	while (co.y < HEIGHT)
// 	{
// 		co.x = 0;
// 		while (co.x < WIDTH)
// 		{
// 			pix.re = (co.x - WIDTH / 2) * 4.0 / (vars->zoom * WIDTH) + co.fact_re;
// 			pix.im = (co.y - HEIGHT / 2) * 4.0 / (vars->zoom * WIDTH) + co.fact_im;
// 			choose_fractol(&co, &pix, vars);
// 			co.x++;
// 		}
// 		co.y++;
// 	}
// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
// }
void	init_data2(t_vars *vars)
{

	vars->maxim = vars->minim + (vars->maxre - vars->minre) * HEIGHT / WIDTH;
	vars->fact_re = (vars->maxre - vars->minre) / (WIDTH - 1);
	vars->fact_im = (vars->maxim - vars->minim) / (HEIGHT - 1);
}

void	draw_image4(t_vars *vars)
{
	// t_ps	co;
	// t_comp	pix;

	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length,
								&vars->endian);
	// init_data(&co);
	init_data2(vars);
	vars->y = 0;
	while (vars->y < HEIGHT)
	{
		vars->x = 0;
		while (vars->x < WIDTH)
		{
			vars->pix.re = (vars->x - WIDTH / 2) * 4.0 / (vars->zoom * WIDTH) + vars->fact_re;
			vars->pix.im = (vars->y - HEIGHT / 2) * 4.0 / (vars->zoom * WIDTH) + vars->fact_im;
			// choose_fractol(&co, &pix, vars);
			choose_fractol2(vars);
			vars->x++;
		}
		vars->y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

// int	zoom_mouse(int button, int x, int y, t_vars *vars)
// {
// 	x = 0;
// 	y = 0;
// 	if (button == SCROLL_IN)
// 		vars->zoom *= pow(1.001, STEP);
// 	else if (button == SCROLL_OUT)
// 		vars->zoom /= pow(1.001, STEP);
// 	draw_image4(vars);
// 	// draw_image2(vars);
// 	return (0);
// }

// int	scroll_mouse(int button, int x, int y, t_vars *vars)
// {
// 	x = 0;
// 	y = 0;
// 	if (button == SCROLL_IN)
// 		vars->zoom++;
// 	draw_image3(vars);	
// 	return (0);
// }


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

// void	draw_image3(t_vars *vars)
// {
// 	int x;
// 	int y;

// 	// vars->zoom = 1;
// 	x = 200;	
// 	y = 200;
// 	while (y < 400)
// 	{
	
// 		pixel_put(vars, x + vars->zoom, y + vars->zoom, 0xFF0000);
// 		x++;
// 	if (x == 400)
// 	{
// 		y++;
// 		x = 200;
// 	}
// 	}
// }

// void	draw_fractal(t_vars *vars)
// {
// 	double 	x;
// 	double 	y;
// 	double	x0;
// 	double	y0;
// 	int		iteration;
// 	int		max_iteration;
// 	double	xtemp;

// 	x0 = 1;
// 	y0 = 1;
// 	x = 0.0;
// 	y = 0.0;
// 	iteration = 0;
// 	max_iteration = 50;
// 	while ((x * x - y * y <= 2 * 2) && iteration < max_iteration)
// 	{
// 		xtemp = x * x - y * y + x0;
// 		y = 2 * x * y + y0;
// 		x = xtemp;
// 		iteration++;
// 		pixel_put(vars, x, y, 0xFF0000);
// 	}

// }

int main(int argc, char **argv)
{
	t_vars vars;

	check_args(argc, argv, &vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Fractol");
	// vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	// vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length,
	//							&vars.endian);
	// draw_image(&vars);
	// draw_image2(&vars);
	draw_image4(&vars);
	// draw_image3(&vars);
	// draw_fractal(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	// mlx_mouse_hook(vars.win, scroll_mouse, &vars);
	mlx_mouse_hook(vars.win, zoom_mouse2, &vars);
	// sleep();
	// mlx_destroy_window(vars.mlx, vars.win);
	// mlx_string_put(vars.mlx, vars.win, 5555, 555, 0x00FF0000, "rerre");
	// mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_loop(vars.mlx);
}