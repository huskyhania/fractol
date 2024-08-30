/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:12:06 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/08/29 20:19:56 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(double x, double y)
{
	double real;
	double imagi;
	double real_tmp;
	int i;

	real = 0;
	imagi = 0;
	i = 0;
	while (i < MAX_ITER)
	{
		real_tmp = real * real - imagi * imagi + x;
		imagi = 2 * real * imagi + y;
		real = real_tmp;

		if (real * real + imagi * imagi > 4.0)
			return (i);
		i++;
	}
	return (i);
}

void	draw_mandelbrot(t_fractol *data)
{
	int x;
	int y;
	double real;
	double imagi;
	uint32_t color;
	int iteration;
	double real_min = -2.5;
	double real_max = 1.0;
	double imagi_min = -1.0;
	double imagi_max = 1.0;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			real = real_min + (real_max - real_min) * x / WIN_WIDTH;
			imagi = imagi_min + (imagi_max - imagi_min) * y / WIN_HEIGHT;
			iteration = mandelbrot(real, imagi);
			if (iteration < MAX_ITER)
				color = 0x00FF00;
			else
				color = 0x000000;
			mlx_put_pixel(data->img_ptr, x, y, color);
			x++;
		}
		y++;
	}
}
