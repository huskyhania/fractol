/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:27:32 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/08/29 21:01:55 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

typedef struct	s_complex
{
	// x
	double	real;
	// y
	double	imagi;
}	t_complex;
/*
int	main(void)
{
	t_complex	z;
	t_complex	c;
	double	tmp_real;
	z.real = 0;
	z.imagi = 0;
	c.real = 0.25;
	c.imagi = 0.4;
	for (int i = 0; i < 42; ++i)
	{
		//general formula: z = z^2 + c 
		tmp_real = (z.real * z.real) - (z.imagi * z.imagi);
		z.imagi = 2 * z.real * z.imagi;
		z.real = tmp_real;
		//adding the c point
		z.real += c.real;
		z.imagi += c.imagi;
		printf("iteration no %d : real %f imaginary %f\n", i, z.real, z.imagi);
	}
	return (0);
}
*/

static void	input_error(void)
{
	ft_printf("Choose the fracral you want\n");
	ft_printf("Write <Mandelbrot> for Mandelbrot fractal\n");
	ft_printf("Write <Julia> and provide 2 numbers for Julia fractal\n");
	ft_printf("Numbers should be between 2 and -2\n");
	ft_printf("If you want to see the bonus one, make bonus and write ???\n");
}

static int	julia_check(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] != '.' && arg[i] != ',' && arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	if ((arg[i] == '.' || arg[i] == ',') && i != 0)
		i++;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

static double	str_to_double(const char *arg)
{
	double	result;
	double	fraction;
	int	sign;
	int	after_decimal;

	result = 0.0;
	fraction = 1.0;
	sign = 1;
	after_decimal = 0;
	if (*arg == '-' || *arg == '+')
	{
		if (*arg == '-')
			sign = -1;
		arg++;
	}
	while (*arg != '\0')
	{
		if (*arg == '.' || *arg == ',')
			after_decimal = 1;
		else if (ft_isdigit(*arg))
		{
			if (after_decimal)
			{
				fraction /= 10.0;
				result += (*arg - '0') * fraction;
			}
			else
				result = result * 10.0 + (*arg - '0');
		}
		arg++;
	}
	return (sign * result);
}

int	main(int argc, char **argv)
{
	t_fractol	fractal;

	if ((argc == 2) && !ft_strncmp(argv[1], "Mandelbrot", 11))
	{
		fractal.mlx_ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Mandelbrot fractal", false);
		if (!fractal.mlx_ptr)
		{	
			ft_printf("Failed to initialize MLX\n");
			return (1);
		}
		fractal.img_ptr = mlx_new_image(fractal.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
		if (!fractal.img_ptr)
		{
			ft_printf("Failed to create image\n");
			mlx_terminate(fractal.mlx_ptr);
			return (1);
		}
		ft_printf("Choosing %s fractal\n", argv[1]);
		draw_mandelbrot(&fractal);
		//fractal.img_instance = mlx_image_to_window(fractal.mlx_ptr, fractal.img_ptr, 0, 0);
		mlx_loop(fractal.mlx_ptr);
		mlx_delete_image(fractal.mlx_ptr, fractal.img_ptr);
		mlx_terminate(fractal.mlx_ptr);
	}
	else if ((argc == 4) && !ft_strncmp(argv[1], "Julia", 6))
	{
		if (julia_check(argv[2]) || julia_check(argv[3]))
		{
			input_error();
			return (1);
		}
		ft_printf("Choosing %s fractal\n", argv[1]);
		double	i = str_to_double(argv[2]);
		double	j = str_to_double(argv[3]);
		printf("my doubles are %f and %f\n", i, j);
	}
	else
	{
		input_error();
		return (1);
	}
	return (0);
}
