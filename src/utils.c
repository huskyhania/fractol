/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:07:43 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/22 16:40:36 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	number_check(t_fractol *fractal)
{
	if (fractal->c.real > INT_MAX || fractal->c.real < INT_MIN
		|| fractal->c.imagi < INT_MIN || fractal->c.imagi > INT_MAX)
		return (1);
	else
		return (0);
}

long long int	fractol_atoi(const char *str)
{
	long long int	number;

	number = 0;
	while (*str >= '0' && *str <= '9')
		number = number * 10 + *str++ - 48;
	return (number);
}

int	error_quit(t_fractol *fractal)
{
	mlx_close_window(fractal->mlx_ptr);
	mlx_terminate(fractal->mlx_ptr);
	return (1);
}

void	init_values(t_fractol *fractal)
{
	fractal->real_min = -2.0;
	fractal->real_max = 2.0;
	fractal->imagi_min = -2.0;
	fractal->imagi_max = 2.0;
	fractal->zoom = 1.0;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->r = 5;
	fractal->g = 0;
	fractal->b = 12;
	fractal->a = 255;
	fractal->bw_mode = 0;
}

void	input_error(void)
{
	ft_printf("Choose the fractal you want\n");
	ft_printf("Write <Mandelbrot> for Mandelbrot fractal\n");
	ft_printf("Write <Julia> and provide 2 numbers for Julia fractal\n");
	ft_printf("Numbers should be between 2 and -2\n");
	ft_printf("If you want to see the bonus one, make bonus and write <ship>\n");
}
