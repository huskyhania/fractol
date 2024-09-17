/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:22:37 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/12 19:21:20 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"
/*
static void	hsv_to_rgb(t_color *color)
{
	double	c;
	double	x; 
	double	m;

	c = color->v * color->s;
	x = c * (1 - fabs(fmod(color->h / 60.0, 2) - 1));
	m = color->v - c;
	if (color->h >= 0 && color->h < 60)
		color->r = (int)((c + m) * 255);
		color->g = (int)((x + m) * 255);
		color->b = (int)(m * 255);
	else if (color->h >= 60 && color->h < 120)
		color->r = (int)((x + m) * 255);
		color->g = (int)((c + m) * 255);
		color->b = (int)(m * 255);
	else if (color->h >= 120 && color->h < 180)
		color->r = (int)(m * 255);
		color->g = (int)((c + m) * 255);
		color->b = (int)((x + m) * 255);
	else if (color->h >= 180 && color->h < 240)
		color->r = (int)(m * 255);
		color->g = (int)((x + m) * 255);
		color->b = (int)((c + m) * 255);
	else if (color->h >= 240 && color->h < 300)
		color->r = (int)((x + m) * 255);
		color->g = (int)(m * 255);
		color->b = (int)((c + m) * 255);
	else
		color->r = (int)((c + m) * 255);
		color->g = (int)(m * 255);
		color->b = (int)((x + m) * 255);
}*/

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	set_color_values(double t, t_color *color)
{
	if (t < 0.25)  // First quarter: transition from #ff3d4a (255, 61, 74) to #eda800 (237, 168, 0)
    	{
        	color->r = (int)(255 * (1 - t / 0.25) + 237 * (t / 0.25)); // Red decreases, Orange increases
        	color->g = (int)(61 * (1 - t / 0.25) + 168 * (t / 0.25));  // Green increases
        	color->b = (int)(74 * (1 - t / 0.25));                    // Blue fades out
	}
	else if (t < 0.50)  // Second quarter: transition from #eda800 (237, 168, 0) to #e0e800 (224, 232, 0)
	{
        	color->r = (int)(237 * (1 - (t - 0.25) / 0.25) + 224 * ((t - 0.25) / 0.25)); // Red decreases
        	color->g = (int)(168 * (1 - (t - 0.25) / 0.25) + 232 * ((t - 0.25) / 0.25)); // Green increases
        	color->b = 0;  // No blue
	}
	else if (t < 0.75)  // Third quarter: transition from #e0e800 (224, 232, 0) to #87e300 (135, 227, 0)
	{
        	color->r = (int)(224 * (1 - (t - 0.50) / 0.25) + 135 * ((t - 0.50) / 0.25)); // Red decreases
        	color->g = (int)(232 * (1 - (t - 0.50) / 0.25) + 227 * ((t - 0.50) / 0.25)); // Green slightly decreases
        	color->b = 0;  // No blue
	}
    	else  // Final quarter: keep #87e300 (135, 227, 0) green
    	{
        	color->r = 135;
        	color->g = 227;
        	color->b = 0;
	}
}

uint32_t	rainbow_generator(int i, t_fractol *f)
{
	t_color	color;
	double	t;

	t = (double)i / MAX_ITER;
	set_color_values(t, &color);
	return ft_pixel(color.r, color.g, color.b, f->a);
}

void	randomize_colors(t_fractol *f)
{

	f->r = rand() % 256;
	f->g = rand() % 256;
	f->b = rand() % 256;
}

uint32_t	color_generator(int i, t_fractol *f)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)i / MAX_ITER;
	r = (int)(f->r * t * 128) % 255;
	g = (int)(f->g * t * 64) % 255;
	b = (int)(f->b * t * 255) % 255;
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
		if (f->rainbow_mode == 1)
			return (rainbow_generator(iteration, f));
		else if (f->bw_mode == 1)
			return (grayscale_generator(iteration, f));
		else
			return (color_generator(iteration, f));
	}
	else
	{
		if (f->bw_mode == 1)
			return (0xFFFFFFFF);
		else if (f->rainbow_mode == 1)
			return (0x006AFFFF);
		else
			return (0xFF00FFFF);
	}
}
