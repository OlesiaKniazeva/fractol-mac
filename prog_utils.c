#include "fractol.h"

void	check_args(int argc, char **argv, t_vars *vars)
{
	if (argc != 2 || (ft_strncmp(argv[1], "Julia", 6) && ft_strncmp(argv[1], "1", 5)\
	 && ft_strncmp(argv[1], "2", 5) && ft_strncmp(argv[1], "3", 5)\
	  && ft_strncmp(argv[1], "Mandelbrot", 15) && \
	  ft_strncmp(argv[1], "Burning_ship", 15) && ft_strncmp(argv[1], "mandelbrot", 15) \
	  && ft_strncmp(argv[1], "julia", 6) && ft_strncmp(argv[1], "burning_ship", 15)))
	{
		printf("%s\n", "\nChoose which fractal to show, write number of fractal or its name as argument to see it:\n1 - Mandelbrot\n 2 - Julia\n 3 - Burning_ship\n");
		exit (1);
	}
	vars->arg = argv[1];
}

// void	choose_fractol(t_vars *vars)
// {
// 	if (!ft_strncmp(vars->arg, "Julia", 6) || !ft_strncmp(vars->arg, "2", 5) || !ft_strncmp(argv[1], "julia", 6))
// 		draw_julia2(vars);
// 	else if (!ft_strncmp(vars->arg, "1", 5) || !ft_strncmp(vars->arg, "Mandelbrot", 15) || !ft_strncmp(vars->arg, "mandelbrot", 15))
// 		draw_mandelbrot2(vars);
// 	else if (!ft_strncmp(vars->arg, "3", 5) || !ft_strncmp(vars->arg, "Burning_ship", 15) || !ft_strncmp(vars->arg, "burning_ship", 15))
// 		draw_burning_ship2(vars);
// }

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n && (*str1 == *str2) && (*str1 != '\0' || *str2 != '\0'))
	{
		str1++;
		str2++;
		n--;
	}
	if (n > 0)
		return (*str1 - *str2);
	else
		return (*(str1 - 1) - *(str2 - 1));
}