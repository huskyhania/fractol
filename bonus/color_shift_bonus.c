/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_shift_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:45:18 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/23 18:11:30 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	color_shift_generator(t_fractol *f)
{
	static double	previous_time = 0;
	double			current_time;
	double			elapsed_time;
	double			shift_speed;

	shift_speed = 0.1;
	current_time = mlx_get_time();
	elapsed_time = current_time - previous_time;
	if (elapsed_time > shift_speed)
	{
		f->r = (f->r + (int)(elapsed_time * 10)) % 256;
		f->g = (f->g + (int)(elapsed_time * 20)) % 256;
		f->b = (f->b + (int)(elapsed_time * 25)) % 256;
		previous_time = current_time;
	}
}

void	randomize_base(t_fractol *f)
{
	int	r;
	int	g;
	int	b;

	if (!f->color_flag)
	{
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
		f->base_color = ((r << 24) | (g << 16) | (b << 8) | f->a);
		f->color_flag = 1;
	}
}

void	randomize_colors(t_fractol *f)
{
	f->r = rand() % 256;
	f->g = rand() % 256;
	f->b = rand() % 256;
}

void	set_color_values(double t, t_color *c)
{
	if (t < 0.1)
	{
		c->r = (int)(255 * (1 - t / 0.1) + 237 * (t / 0.1));
		c->g = (int)(61 * (1 - t / 0.1) + 168 * (t / 0.1));
		c->b = (int)(74 * (1 - t / 0.1));
	}
	else if (t < 0.25)
	{
		c->r = (int)(237 * (1 - t / 0.25) + 224 * (t / 0.25));
		c->g = (int)(168 * (1 - t / 0.25) + 232 * (t / 0.25));
		c->b = 0;
	}
	else if (t < 0.35)
	{
		c->r = (int)(224 * (1 - (t - 0.25) / 0.10) + 135 * ((t - 0.25) / 0.10));
		c->g = (int)(232 * (1 - (t - 0.25) / 0.10) + 227 * ((t - 0.25) / 0.10));
		c->b = 0;
	}
	else
	{
		c->r = 135;
		c->g = 227;
		c->b = 0;
	}
}

uint32_t	rainbow_generator(int i, t_fractol *f)
{
	t_color	color;
	double	t;

	t = (double)i / MAX_ITER;
	set_color_values(t, &color);
	return (ft_pixel(color.r, color.g, color.b, f->a));
}
