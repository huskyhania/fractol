/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:03:22 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/07 14:26:00 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_values(t_fractol *fractal)
{
	fractal->real_min = -2.0;
	fractal->real_max = 2.0;
	fractal->imagi_min = -2.0;
	fractal->imagi_max = 2.0;
	fractal->zoom = 1.0;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->r = 5;
	fractal->g = 0;
	fractal->b = 12;
	fractal->a = 255;
	fractal->bw_mode = 0;
}
