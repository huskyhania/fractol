/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 18:33:07 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/07 21:21:46 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(t_fractol *f, double real, double imag)
{
	t_complex	z;
	double	real_tmp;
	int	i;

	z.real = real;
	z.imagi = imag;
	i = 0;
	while (i < MAX_ITER)
	{
		real_tmp = z.real * z.real - z.imagi * z.imagi + f->c.real;
		z.imagi = 2 * z.real * z.imagi + f->c.imagi;
		z.real = real_tmp;
		if (z.real * z.real + z.imagi * z.imagi > 4.0)
			return (i);
		i++;
	}
	return (i);
}

void	pixel_complex_julia(t_fractol *f, int x, int y, double *real, double *imag)
{
	*real = f->real_min + (f->real_max - f->real_min) * x / (WIDTH - 1);
	*imag = f->imagi_max - (f->imagi_max - f->imagi_min) * y / (HEIGHT - 1);
}

void	draw_julia(t_fractol *f, double c_real, double c_imagi)
{
	int	x;
	int	y;
	uint32_t	color;
	int	iteration;
	double	real;
	double	imag;

	f->c.real = c_real;
	f->c.imagi = c_imagi;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_complex_julia(f, x, y, &real, &imag);
			iteration = julia(f, real, imag);
			color = get_pixel_color(iteration, f);
			mlx_put_pixel(f->img_ptr, x, y, color);
			x++;
		}
		y++;
	}
}

int	initialize_julia(double c_real, double c_imagi)
{
	t_fractol fractal;
	init_values(&fractal);
	fractal.mlx_ptr = mlx_init(WIDTH, HEIGHT, "Julia fractal", false);
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
	draw_julia(&fractal, c_real, c_imagi);
	fractal.img_instance = mlx_image_to_window(fractal.mlx_ptr, fractal.img_ptr, 0, 0);
	mlx_scroll_hook(fractal.mlx_ptr, mouse_scroll, &fractal);
	mlx_cursor_hook(fractal.mlx_ptr, cursor_move, &fractal);
	mlx_key_hook(fractal.mlx_ptr, key_press, &fractal);
	mlx_loop(fractal.mlx_ptr);
	mlx_delete_image(fractal.mlx_ptr, fractal.img_ptr);
	mlx_terminate(fractal.mlx_ptr);
	return (0);
}
