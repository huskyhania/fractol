/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:50:17 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/01 16:12:29 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//void	mouse_scroll

//void	window_close

void	key_press(struct mlx_key_data k_data, void *param)
{
	t_fractol *fractal = (t_fractol *)param;
	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
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
}
