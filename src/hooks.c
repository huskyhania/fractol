/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:50:17 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/03 22:33:21 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//void	mouse_scroll

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
		fractal->offset_y += 0.05 / fractal->zoom;
		draw_mandelbrot(fractal);
	}
}
