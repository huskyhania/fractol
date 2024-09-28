/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:22:37 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/28 14:47:58 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

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
		if (f->rainbow_mode == 1)
			return (rainbow_generator(iteration, f));
		else if (f->bw_mode == 1)
			return (grayscale_generator(iteration, f));
		else
			return (color_generator(iteration, f));
	}
	else
	{
		if (f->bw_mode == 1 || f->gradual_shift == 1)
			return (0xFFFFFFFF);
		else if (f->rainbow_mode == 1)
			return (0x006AFFFF);
		else if (f->random_mode == 1 || f->shift == 1)
			return (f->base_color);
		else
			return (0xFF00FFFF);
	}
}

void	display_info(void)
{
	ft_printf("Press P to see rainbow colors\n");
	ft_printf("Press D to draw a new random color set\n");
	ft_printf("Press S to see colors shift randomly, press again to freeze\n");
	ft_printf("Press G to see gradual color shift, press again to freeze\n");
	ft_printf("Press R to reset color/zoom settings\n");
}
