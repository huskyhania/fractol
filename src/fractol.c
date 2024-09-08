/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:27:32 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/08 20:33:54 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

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

double	str_to_double(const char *arg)
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

static  int     validity_check(int argc, char **argv)
 {
 	if ((argc == 2) && !ft_strncmp(argv[1], "Mandelbrot", 10))
	{
 		ft_printf("Choice: Mandelbrot");
		return (0);
	}
	else if (argc == 4 && !ft_strncmp(argv[1], "Julia", 5) && !julia_check(argv[2]) && !julia_check(argv[3]))
	{
		ft_printf("Choice: Julia");
		double i = str_to_double(argv[2]);
		double j = str_to_double(argv[3]);
 		printf("my doubles are %f and %f\n", i, j);
		return (0);
	}
	else
		return (1);
 }

int	main(int argc, char **argv)
{
	t_fractol	fractal;
	if (validity_check(argc, argv) == 0)
	{
		init_values(&fractal);
		if (argc == 2)
			fractal.fractal_type = 1;
		else if (argc == 4)
		{
			fractal.fractal_type = 2;
			fractal.c.real = str_to_double(argv[2]);
			fractal.c.imagi = str_to_double(argv[3]);
		}
		initialize_fractal(&fractal);
	}
	else if (validity_check(argc, argv) != 0)
	{
		input_error();
		return (1);
	}
	return (0);
}
