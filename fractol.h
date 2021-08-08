#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
	char	*addr;
	void	*img;
	int		endian;
	int		bits_per_pixel;
	int		line_length;
	int		column;
	int		line;
	double	c_re;
	double	c_im;
	double	x;
	double	y;
	double	iter;
	double	x_new;
	char	*arg;
	double	zoom;
	double	move_x;
	double	move_y;
	int		max;
}				t_vars;


# define WIDTH 500
# define HEIGHT 500
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124 
# define ESC 53
# define SCROLL_IN 5
# define SCROLL_OUT 4
# define STEP 700
# define STEP_Z 0.5
# define UP_PREC 0
# define DOWN_PREC 2


// # define JU_RE 0.285
// # define JU_IM 0.01

# define JU_RE -0.70176 
# define JU_IM -0.384

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	check_args(int argc, char **argv, t_vars *vars);
int		key_hook(int key, t_vars *vars);
void	pixel_put(t_vars *vars, int x, int y, int color);
void	draw_mandelbrot(t_vars *vars);
void	draw_burning_ship(t_vars *vars);
void	draw_julia(t_vars *vars);
void	init_data(t_vars *vars);
int		create_rgb(int r, int g, int b);
int		zoom_mouse(int button, int x, int y, t_vars *vars);
void	draw_fractal(t_vars *vars);
void	choose_fractol(t_vars *vars);
void	paint_fractal(t_vars *vars);

#endif
