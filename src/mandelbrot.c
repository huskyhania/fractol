/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:12:06 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/07 14:11:29 by hskrzypi         ###   ########.fr       */
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

void	draw_mandelbrot(t_fractol *f)
{
	int x;
	int y;
	uint32_t color;
	int iteration;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			f->c.real = f->real_min * f->zoom + f->offset_x
				+ (f->real_max * f->zoom - f->real_min * f->zoom) * x / (WIDTH - 1);
			f->c.imagi = f->imagi_min * f->zoom + f->offset_y
				+ (f->imagi_max * f->zoom - f->imagi_min * f->zoom) * y / (HEIGHT - 1);
			iteration = mandelbrot(f);
			if (iteration < MAX_ITER)
			{
				if (f->bw_mode == 1)
					color = 0x000000FF;
				else
					color = color_generator(iteration, f);
			}
			else
			{
				if (f->bw_mode == 1)
					color = 0xFFFFFFFF;
				else
					color = 0xFF00FFFF;
			}
			mlx_put_pixel(f->img_ptr, x, y, color);
			x++;
		}
		y++;
	}
}

int	initialize_mandelbrot(void)
{
	t_fractol	fractal;

	init_values(&fractal);
	fractal.mlx_ptr = mlx_init(WIDTH, HEIGHT, "Mandelbrot fractal", false);
	if (!fractal.mlx_ptr)
	{
		ft_printf("Failed to initialize MLX\n");
		return (1);
	}
	fractal.img_ptr = mlx_new_image(fractal.mlx_ptr, WIDTH, HEIGHT);
	if (!fractal.img_ptr)
	{
		ft_printf("Failed to create image\n");
		mlx_close_window(fractal.mlx_ptr);
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
