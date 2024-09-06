/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:12:06 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/06 20:37:05 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(t_fractol *data)
{
	t_complex	z;
	double real_tmp;
	int i;

	z.real = 0;
	z.imagi = 0;
	i = 0;
	while (i < MAX_ITER)
	{
		real_tmp = z.real * z.real - z.imagi * z.imagi + data->c.real;
		z.imagi = 2 * z.real * z.imagi + data->c.imagi;
		z.real = real_tmp;
		if (z.real * z.real + z.imagi * z.imagi > 4.0)
			return (i);
		i++;
	}
	return (i);
}

void	draw_mandelbrot(t_fractol *data)
{
	int x;
	int y;
	uint32_t color;
	int iteration;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			data->c.real = data->real_min * data->zoom + data->offset_x
				+ (data->real_max * data->zoom - data->real_min * data->zoom) * x / (WIN_WIDTH - 1);
			data->c.imagi = data->imagi_min * data->zoom + data->offset_y
				+ (data->imagi_max * data->zoom - data->imagi_min * data->zoom) * y / (WIN_HEIGHT - 1);
			iteration = mandelbrot(data);
			if (iteration < MAX_ITER)
				color = color_generator(iteration, data);
			else
				color = 0xFF00FFFF;
			mlx_put_pixel(data->img_ptr, x, y, color);
			x++;
		}
		y++;
	}
}

int	initialize_mandelbrot(void)
{
	t_fractol	fractal;

	fractal.real_min = -2.0;
	fractal.real_max = 2.0;
	fractal.imagi_min = -2.0;
	fractal.imagi_max = 2.0;
	fractal.zoom = 1.0;
	fractal.offset_x = 0.0;
	fractal.offset_y = 0.0;
	fractal.r = 5;
	fractal.g = 0;
	fractal.b = 12;
	fractal.a = 255;
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
	draw_mandelbrot(&fractal);
	fractal.img_instance = mlx_image_to_window(fractal.mlx_ptr, fractal.img_ptr, 0, 0);
	mlx_scroll_hook(fractal.mlx_ptr, mouse_scroll, &fractal);
	mlx_cursor_hook(fractal.mlx_ptr, cursor_move, &fractal);
	mlx_key_hook(fractal.mlx_ptr, key_press, &fractal);
	mlx_loop(fractal.mlx_ptr);
	mlx_delete_image(fractal.mlx_ptr, fractal.img_ptr);
	mlx_terminate(fractal.mlx_ptr);
	return (0);
}
