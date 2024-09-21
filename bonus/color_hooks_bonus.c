/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_hooks_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:18:59 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/21 19:40:43 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	update_colors(void *param)
{
	t_fractol	*f;

	f = (t_fractol *)param;
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
		draw_fractal(f);
	}
}

void	color_shifts(mlx_key_data_t k_data, t_fractol *fractal)
{
	if (k_data.key == MLX_KEY_D && k_data.action == MLX_PRESS)
	{
		fractal->random_mode = 1;
		randomize_colors(fractal);
		randomize_base(fractal);
		draw_fractal(fractal);
		fractal->color_flag = 0;
	}
	if ((k_data.key == MLX_KEY_S || k_data.key == MLX_KEY_G)
		&& k_data.action == MLX_PRESS)
	{
		if (k_data.key == MLX_KEY_S)
			fractal->shift = !fractal->shift;
		if (k_data.key == MLX_KEY_G)
			fractal->gradual_shift = !fractal->gradual_shift;
		if (fractal->shift || fractal->gradual_shift)
		{
			if (!mlx_loop_hook(fractal->mlx_ptr, update_colors, fractal))
				ft_printf("MLX loop hook error\n");
		}
	}
}

void	color_mode(mlx_key_data_t k_data, t_fractol *fractal)
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
}
