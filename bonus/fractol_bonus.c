/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:27:32 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/22 20:11:25 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

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

static long double	ft_fraction(const char *arg)
{
	long double	fraction;
	long double	divisor;

	fraction = 0.0;
	divisor = 10.0;
	while (*arg)
	{
		fraction += (*arg - '0') / divisor;
		divisor *= 10.0;
		arg++;
	}
	return (fraction);
}

long double	str_to_double(const char *arg)
{
	long double	result;
	long double	fraction;
	int			sign;

	result = 0.0;
	fraction = 0.0;
	sign = 1;
	if (*arg == '-' || *arg == '+')
	{
		if (*arg == '-')
			sign = -1;
		arg++;
	}
	result = (long double)fractol_atoi(arg);
	while (*arg && ft_isdigit(*arg))
		arg++;
	if (*arg && (*arg == '.' || *arg == ','))
	{
		arg++;
		fraction = ft_fraction(arg);
	}
	return (sign * (result + fraction));
}

static int	validity_check(int argc, char **argv, t_fractol *fractal)
{
	if (argc == 2 && !ft_strncmp(argv[1], "Mandelbrot", 10))
	{
		ft_printf("Choice: Mandelbrot\n");
		fractal->fractal_type = 1;
		return (0);
	}
	else if (argc == 2 && !ft_strncmp(argv[1], "ship", 4))
	{
		ft_printf("Choice: Burning ship\n");
		fractal->fractal_type = 3;
		return (0);
	}
	else if (argc == 4 && !ft_strncmp(argv[1], "Julia", 5)
		&& !julia_check(argv[2]) && !julia_check(argv[3]))
	{
		fractal->c.real = str_to_double(argv[2]);
		fractal->c.imagi = str_to_double(argv[3]);
		if (number_check(fractal))
			return (ft_printf("Choose a valid number\n"));
		ft_printf("Choice: Julia\n");
		fractal->fractal_type = 2;
		return (0);
	}
	else
		return (1);
}

int	main(int argc, char **argv)
{
	t_fractol	fractal;

	if (validity_check(argc, argv, &fractal) == 0)
	{
		init_values(&fractal);
		if (initialize_fractal(&fractal))
			return (ft_printf("Error quit\n"));
	}
	else
	{
		input_error();
		return (1);
	}
	return (0);
}
