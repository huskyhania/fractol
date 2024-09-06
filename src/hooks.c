/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:50:17 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/06 20:56:20 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mouse_scroll(double xdelta, double ydelta, void *param)
{
	(void)xdelta;
	t_fractol *fractal = (t_fractol *)param;
	double mouse_real;
	double mouse_imagi;
	double zoom_factor = 1.0;
	int32_t mouse_x;
	int32_t mouse_y;

	mlx_get_mouse_pos(fractal->mlx_ptr, &mouse_x, &mouse_y);
	mouse_real = fractal->real_min + (fractal->real_max - fractal->real_min) * mouse_x / (WIN_WIDTH - 1);
	mouse_imagi = fractal->imagi_min + (fractal->imagi_max - fractal->imagi_min) * mouse_y / (WIN_HEIGHT - 1);
	if (ydelta > 0)
		zoom_factor = 0.9;
	else if (ydelta < 0)
		zoom_factor = 1.1;
	fractal->zoom *= zoom_factor;
	fractal->offset_x = mouse_real - (mouse_real - fractal->offset_x) * zoom_factor;
	fractal->offset_y = mouse_imagi - (mouse_imagi - fractal->offset_y) * zoom_factor;
	draw_mandelbrot(fractal);
}

void	cursor_move(double xpos, double ypos, void *param)
{
	t_fractol *fractal = (t_fractol *)param;
	fractal->mouse_x = xpos;
	fractal->mouse_y = ypos;
}

void	window_close(t_fractol *fractal)
{
	if (fractal->img_ptr)
		mlx_delete_image(fractal->mlx_ptr, fractal->img_ptr);
	if (fractal->mlx_ptr)
	{
		mlx_close_window(fractal->mlx_ptr);
		mlx_terminate(fractal->mlx_ptr);
	}
	exit (0);
}

void	key_press(struct mlx_key_data k_data, void *param)
{
	t_fractol *fractal = (t_fractol *)param;
	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
		window_close(fractal);
	else if (k_data.key == MLX_KEY_I && k_data.action == MLX_PRESS)
	{
		fractal->zoom *= 0.9;
		draw_mandelbrot(fractal);
	}
	else if (k_data.key == MLX_KEY_O && k_data.action == MLX_PRESS)
	{
		fractal->zoom *= 1.1;
		draw_mandelbrot(fractal);
	}
	else if (k_data.key == MLX_KEY_UP && k_data.action == MLX_PRESS)
	{
		fractal->offset_y -= 0.05 / fractal->zoom;
		draw_mandelbrot(fractal);
	}
	else if (k_data.key == MLX_KEY_DOWN && k_data.action == MLX_PRESS)
	{
		fractal->offset_y += 0.05 / fractal->zoom;
		draw_mandelbrot(fractal);
	}
	else if (k_data.key == MLX_KEY_LEFT && k_data.action == MLX_PRESS)
	{
		fractal->offset_x -= 0.05 / fractal->zoom;
		draw_mandelbrot(fractal);
	}
	else if (k_data.key == MLX_KEY_RIGHT && k_data.action == MLX_PRESS)
	{
		fractal->offset_x += 0.05 / fractal->zoom;
		draw_mandelbrot(fractal);
	}
}
