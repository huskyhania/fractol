/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:22:37 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/08 21:31:46 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "math.h"

static void	hsv_to_rgb(double h, double s, double v, int *r, int *g, int *b)
{
	double	c = v * s;
	double	x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
	double	m = v - c;
	double	r_prime, g_prime, b_prime;

	if (h >= 0 && h < 60)
		r_prime = c, g_prime = x, b_prime = 0;
	else if (h >= 60 && h < 120)
		r_prime = x, g_prime = c, b_prime = 0;
	else if (h >= 120 && h < 180)
		r_prime = 0, g_prime = c, b_prime = x;
	else if (h >= 180 && h < 240)
		r_prime = 0, g_prime = x, b_prime = c;
	else if (h >= 240 && h < 300)
		r_prime = x, g_prime = 0, b_prime = c;
	else
		r_prime = c, g_prime = 0, b_prime = x;

	*r = (int)((r_prime + m) * 255);
	*g = (int)((g_prime + m) * 255);
	*b = (int)((b_prime + m) * 255);
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	color_generator(int i, t_fractol *f)
{
	double	t;
	int		r, g, b;
	double	h, s, v;

	// t is a ratio of how far we are in the iteration range
	t = (double)i / MAX_ITER;
	
	// Set HSV parameters
	h = 360.0 * t; // Full rainbow effect, hue varies from 0 to 360
	s = 1.0;       // Full saturation for vivid colors
	v = 1.0;       // Full value for brightness
	
	// Convert HSV to RGB
	hsv_to_rgb(h, s, v, &r, &g, &b);

	// Return the color as an integer
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
	r = (int)(f->r * t * 200) % 255;
	g = (int)(f->g * t * 150) % 255;
	b = (int)(f->b * t * 255) % 255;
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
			return (0x0038A8FF);
	}
}
