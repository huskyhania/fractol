/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:22:37 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/23 18:15:06 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	color_generator(int i, t_fractol *f)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)i / MAX_ITER;
	r = (int)(f->r * t * 128) % 256;
	g = (int)(f->g * t * 64) % 256;
	b = (int)(f->b * t * 255) % 256;
	return (ft_pixel(r, g, b, f->a));
}

uint32_t	grayscale_generator(int i, t_fractol *f)
{
	double	t;
	int		gray;
	int		r;
	int		g;
	int		b;

	t = (double)i / MAX_ITER;
	r = (int)(f->r * t * 200) % 256;
	g = (int)(f->g * t * 150) % 256;
	b = (int)(f->b * t * 255) % 256;
	gray = (int)(0.299 * r + 0.587 * g + 0.114 * b);
	return (ft_pixel(gray, gray, gray, 255));
}

uint32_t	get_pixel_color(int iteration, t_fractol *f)
{
	if (iteration < MAX_ITER)
	{
		if (f->bw_mode == 1)
			return (grayscale_generator(iteration, f));
		else
			return (color_generator(iteration, f));
	}
	else
	{
		if (f->bw_mode == 1)
			return (0xFFFFFFFF);
		else
			return (0xFF00FFFF);
	}
}

void	color_mode(mlx_key_data_t k_data, t_fractol *fractal)
{
	if (k_data.key == MLX_KEY_B && k_data.action == MLX_PRESS)
	{
		if (fractal->bw_mode == 1)
			fractal->bw_mode = 0;
		else
			fractal->bw_mode = 1;
		draw_fractal(fractal);
	}
}
