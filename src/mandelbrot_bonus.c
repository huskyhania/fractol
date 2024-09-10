/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:26:16 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/10 21:43:24 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

int	fractal_iteration(t_fractol *f)
{
	t_complex	z;
	double		real_tmp;
	int			i;

	if (f->fractal_type == 1 || f->fractal_type == 3)
	{
		f->c.real = f->z.real;
		f->c.imagi = f->z.imagi;
		z.real = 0;
		z.imagi = 0;
	}
	else if (f->fractal_type == 2)
	{
		z.real = f->z.real;
		z.imagi = f->z.imagi;
	}
	i = 0;
	while (i < MAX_ITER)
	{
		if (f->fractal_type == 3)
		{
			z.real = fabs(z.real);
			z.imagi = fabs(z.imagi);
		}
		real_tmp = z.real * z.real - z.imagi * z.imagi + f->c.real;
		z.imagi = 2 * z.real * z.imagi + f->c.imagi;
		z.real = real_tmp;
		if (z.real * z.real + z.imagi * z.imagi > 4.0)
			return (i);
		i++;
	}
	return (i);
}

void	pixel_complex(t_fractol *f, int x, int y)
{
	f->z.real = f->real_min * f->zoom + f->offset_x
		+ (f->real_max * f->zoom - f->real_min * f->zoom) * x / (WIDTH - 1);
	if (f->fractal_type == 1 || f->fractal_type == 3)
	{
		f->z.imagi = f->imagi_min * f->zoom + f->offset_y
			+ (f->imagi_max * f->zoom - f->imagi_min * f->zoom) * y / (HEIGHT - 1);
	}
	else if (f->fractal_type == 2)
	{
		f->z.imagi = f->imagi_max * f->zoom + f->offset_y
			- (f->imagi_max * f->zoom - f->imagi_min * f->zoom) * y / (HEIGHT - 1);
	}
}

void	draw_fractal(t_fractol *f)
{
	int			x;
	int			y;
	int			iteration;
	uint32_t	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_complex(f, x, y);
			iteration = fractal_iteration(f);
			color = get_pixel_color(iteration, f);
			mlx_put_pixel(f->img_ptr, x, y, color);
			x++;
		}
		y++;
	}
}

int	initialize_fractal(t_fractol *fractal)
{
	fractal->mlx_ptr = mlx_init(WIDTH, HEIGHT, "Fractal explorer", false);
	if (!fractal->mlx_ptr)
	{
		ft_printf("Failed to initialize MLX\n");
		return (1);
	}
	fractal->img_ptr = mlx_new_image(fractal->mlx_ptr, WIDTH, HEIGHT);
	if (!fractal->img_ptr)
	{
		ft_printf("Failed to create image\n");
		mlx_close_window(fractal->mlx_ptr);
		mlx_terminate(fractal->mlx_ptr);
		return (1);
	}
	draw_fractal(fractal);
	fractal->img_instance = mlx_image_to_window(fractal->mlx_ptr,
			fractal->img_ptr, 0, 0);
	mlx_scroll_hook(fractal->mlx_ptr, mouse_scroll, fractal);
	mlx_cursor_hook(fractal->mlx_ptr, cursor_move, fractal);
	mlx_key_hook(fractal->mlx_ptr, key_press, fractal);
	mlx_loop(fractal->mlx_ptr);
	mlx_delete_image(fractal->mlx_ptr, fractal->img_ptr);
	mlx_terminate(fractal->mlx_ptr);
	return (0);
}
