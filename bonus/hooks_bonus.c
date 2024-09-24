/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:43:45 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/22 16:24:25 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	mouse_scroll(double xdelta, double ydelta, void *param)
{
	t_fractol	*f;
	double		mouse_real;
	double		mouse_imagi;
	double		zoom_factor;

	(void)xdelta;
	zoom_factor = 1;
	f = (t_fractol *)param;
	mlx_get_mouse_pos(f->mlx_ptr, &f->mouse_x, &f->mouse_y);
	mouse_real = f->real_min + (f->real_max - f->real_min)
		* f->mouse_x / (WIDTH - 1);
	mouse_imagi = f->imagi_min + (f->imagi_max - f->imagi_min)
		* f->mouse_y / (HEIGHT - 1);
	if (ydelta > 0)
		zoom_factor = 0.9;
	else if (ydelta < 0)
		zoom_factor = 1.1;
	f->zoom *= zoom_factor;
	f->offset_x = mouse_real - (mouse_real - f->offset_x) * zoom_factor;
	f->offset_y = mouse_imagi - (mouse_imagi - f->offset_y) * zoom_factor;
	draw_fractal(f);
}

void	cursor_move(double xpos, double ypos, void *param)
{
	t_fractol	*fractal;

	fractal = (t_fractol *)param;
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

void	keyboard_move(mlx_key_data_t k_data, t_fractol *fractal)
{
	if (k_data.key == MLX_KEY_UP && k_data.action == MLX_PRESS)
	{
		fractal->offset_y -= 0.05 * fractal->zoom;
		draw_fractal(fractal);
	}
	else if (k_data.key == MLX_KEY_DOWN && k_data.action == MLX_PRESS)
	{
		fractal->offset_y += 0.05 * fractal->zoom;
		draw_fractal(fractal);
	}
	else if (k_data.key == MLX_KEY_LEFT && k_data.action == MLX_PRESS)
	{
		fractal->offset_x -= 0.05 * fractal->zoom;
		draw_fractal(fractal);
	}
	else if (k_data.key == MLX_KEY_RIGHT && k_data.action == MLX_PRESS)
	{
		fractal->offset_x += 0.05 * fractal->zoom;
		draw_fractal(fractal);
	}
}

void	key_press(mlx_key_data_t k_data, void *param)
{
	t_fractol	*fractal;

	fractal = (t_fractol *)param;
	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
		window_close(fractal);
	else if (k_data.key == MLX_KEY_I && k_data.action == MLX_PRESS)
	{
		fractal->zoom *= 0.9;
		draw_fractal(fractal);
	}
	else if (k_data.key == MLX_KEY_O && k_data.action == MLX_PRESS)
	{
		fractal->zoom *= 1.1;
		draw_fractal(fractal);
	}
	else if (k_data.key == MLX_KEY_R && k_data.action == MLX_PRESS)
	{
		init_values(fractal);
		draw_fractal(fractal);
	}
	keyboard_move(k_data, fractal);
	color_mode(k_data, fractal);
	color_shifts(k_data, fractal);
}
