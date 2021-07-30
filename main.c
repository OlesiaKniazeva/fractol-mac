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
}

t_comp	init_complex(double re, double im)
{
	t_comp	comp;

	comp.re = re;
	comp.im = im;
	return (comp);
}

int	key_hook(int key, t_vars *vars)
{
	// keycode = 1; 
	(void)vars->win;
	if (key == ESC)
		exit (2);
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

void	draw_burning_ship(t_ps *co, t_comp *pix, t_vars *vars)
{
	t_comp	z;
	int		i;

	i = 0;
	z = init_complex(pix->re, pix->im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && i < co->iter)
	{
  	  z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + pix->re, -2.0 * fabs(z.re * z.im) + pix->im);
    	i++;
	}
	paint(vars, co, i); 
}

void	draw_mandelbrot(t_ps *co, t_comp *pix, t_vars *vars)
{
	int i;
	t_comp	z;

	z = init_complex(pix->re, pix->im);
	i = 0;
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && i < co->iter)
	{
		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + pix->re, 2.0 * z.re * z.im + pix->im);
		i++;
	}
	paint(vars, co, i); 
}

void	draw_julia(t_ps *co, t_comp *pix, t_vars *vars)
{
	int		i;
	t_comp	z;

	z = init_complex(pix->re, pix->im);
	i = 0;
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && i < co->iter)
	{
		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + JU_RE,
        2.0 * z.re * z.im + JU_IM);
		i++;
	}
		paint(vars, co, i);
}

void	init_data(t_ps *co)
{
	co->minre = -2.0;
	co->maxre = 2.0;
	co->minim = -2.0;
	co->maxim = co->minim + (co->maxre - co->minre) * HEIGHT / WIDTH;
	co->fact_re = (co->maxre - co->minre) / (WIDTH - 1);
	co->fact_im = (co->maxim - co->minim) / (HEIGHT - 1);
	co->iter = 50;
}


int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	paint(t_vars *vars, t_ps *co, int i)
{
	double	t;

	t = (double)i / (double)co->iter;
	if (i < co->iter)
		pixel_put(vars, co->x, co->y, create_rgb(
				(int)(10 * (1 - t) * pow(t, 3) * 255),
				(int)(20 * pow((1 - t), 2) * pow(t, 2) * 255),
				(int)(2 * pow((1 - t), 3) * t * 255)));
		// pixel_put(vars, co->x, co->y, 0x00FFFFFF);
	// else 
	// 	pixel_put(vars, co->x, co->y, 0x00000000);
}

void	choose_fractol(t_ps *co, t_comp *pix, t_vars *vars)
{
	if (!ft_strncmp(vars->arg, "Julia", 6) || !ft_strncmp(vars->arg, "2", 5))
		draw_julia(co, pix, vars);
	else if (!ft_strncmp(vars->arg, "1", 5) || !ft_strncmp(vars->arg, "Mandelbrot", 15))
		draw_mandelbrot(co, pix, vars);
	else if (!ft_strncmp(vars->arg, "3", 5) || !ft_strncmp(vars->arg, "Burning_ship", 15))
		draw_burning_ship(co, pix, vars);
}

void	draw_image(t_vars *vars)
{
	t_ps	co;
	t_comp	pix;

	init_data(&co);
	co.y = 0;
	while (co.y < HEIGHT)
	{
		pix.im = co.maxim - co.y * co.fact_im + vars->zoom;
		co.x = 0;
		while (co.x < WIDTH)
		{
			pix.re = co.minre + co.x * co.fact_re + vars->zoom;
			choose_fractol(&co, &pix, vars);
			co.x++;
		}
		co.y++;
	}
}

void	draw_image2(t_vars *vars)
{
	t_ps	co;
	t_comp	pix;

	init_data(&co);
	co.y = 0;
	while (co.y < HEIGHT)
	{
		co.x = 0;
		while (co.x < WIDTH)
		{
			pix.re = (co.x - WIDTH / 2) * 4.0 / (vars->zoom * WIDTH) + co.fact_re;
			pix.im = (co.y - HEIGHT / 2) * 4.0 / (vars->zoom * WIDTH) + co.fact_im;
			choose_fractol(&co, &pix, vars);
			co.x++;
		}
		co.y++;
	}
}

int	zoom_mouse(int button, int x, int y, t_vars *vars)
{
	x = 0;
	y = 0;
	if (button == SCROLL_IN)
		vars->zoom *= pow(1.001, STEP);
	else if (button == SCROLL_OUT)
		vars->zoom /= pow(1.001, STEP);
	draw_image2(vars);
	return (0);
}

int	scroll_mouse(int button, int x, int y, t_vars *vars)
{
	x = 0;
	y = 0;
	if (button == SCROLL_IN)
		vars->zoom++;
	draw_image3(vars);	
	return (0);
}


int	zoom_mouse2(int button, t_vars *vars)
{
	if (button == SCROLL_IN)
		vars->zoom *= pow(1.001, STEP);
	else if (button == SCROLL_OUT)
		vars->zoom /= pow(1.001, STEP);
	draw_image2(vars);
	return (0);
}

void	draw_image3(t_vars *vars)
{
	int x;
	int y;

	// vars->zoom = 1;
	x = 200;	
	y = 200;
	while (y < 400)
	{
	
		pixel_put(vars, x + vars->zoom, y + vars->zoom, 0xFF0000);
		x++;
	if (x == 400)
	{
		y++;
		x = 200;
	}
	}
}


int main(int argc, char **argv)
{
	t_vars vars;

	check_args(argc, argv, &vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Fractol");
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length,
								&vars.endian);
	
	// draw_image(&vars);
	// draw_image2(&vars);
	// draw_image3(&vars);
	

	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, scroll_mouse, &vars);
	// mlx_key_hook(vars.win, zoom_mouse2, &vars);
	// sleep();
	// mlx_destroy_window(vars.mlx, vars.win);
	// mlx_string_put(vars.mlx, vars.win, 5555, 555, 0x00FF0000, "rerre");
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_loop(vars.mlx);
}