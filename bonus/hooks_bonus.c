/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:43:45 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/20 19:34:13 by hskrzypi         ###   ########.fr       */
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
/*
void	update_colors(void *param)
{
	t_fractol *f = (t_fractol *)param;
	if (f->shift == 1)
	{
		randomize_colors(f);
		f->color_flag = 0;
		randomize_base(f);
		draw_fractal(f);
	}
	else if (f->gradual_shift == 1)
	{
		color_shift_generator(f);
		f->color_flag = 0;
		randomize_base(f);
		draw_fractal(f);
	}
}*/

/*void	color_mode(mlx_key_data_t k_data, t_fractol *fractal)
{
	if (k_data.key == MLX_KEY_B && k_data.action == MLX_PRESS)
	{
		fractal->rainbow_mode = 0;
		if (fractal->bw_mode == 1)
			fractal->bw_mode = 0;
		else
			fractal->bw_mode = 1;
		draw_fractal(fractal);
	}
	if (k_data.key == MLX_KEY_P && k_data.action == MLX_PRESS)
	{
		fractal->bw_mode = 0;
		if (fractal->rainbow_mode == 1)
			fractal->rainbow_mode = 0;
		else
			fractal->rainbow_mode = 1;
		draw_fractal(fractal);
	}
	if (k_data.key == MLX_KEY_D && k_data.action == MLX_PRESS)
	{
		fractal->random_mode = 1;
		randomize_colors(fractal);
		randomize_base(fractal);
		draw_fractal(fractal);
		fractal->color_flag = 0;
	}
	if (k_data.key == MLX_KEY_S && k_data.action == MLX_PRESS)
	{
		fractal->shift = !fractal->shift;
		if (fractal->shift)
			mlx_loop_hook(fractal->mlx_ptr, update_colors, fractal);
	//	else
	//	{
	//		mlx_loop_hook(fractal->mlx_ptr, NULL, NULL);
	//		draw_fractal(fractal);
	//	}
	}
	if (k_data.key == MLX_KEY_G && k_data.action == MLX_PRESS)
	{
		fractal->gradual_shift = !fractal->gradual_shift;
		if (fractal->gradual_shift)
			mlx_loop_hook(fractal->mlx_ptr, update_colors, fractal);
	}
}*/

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
