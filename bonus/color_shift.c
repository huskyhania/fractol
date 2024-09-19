/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:45:18 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/19 21:47:45 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void color_shift_generator(t_fractol *f)
{
	static double previous_time = 0;
	double current_time;
	double elapsed_time;
	double shift_speed = 0.1;  // You can adjust the speed of color shifting

	// Get the current time (in seconds)
	current_time = mlx_get_time();  // Use mlx_get_time() or clock() if using standard C

	// Calculate the time elapsed since the last call
	elapsed_time = current_time - previous_time;

	// Update the colors based on the elapsed time and the shift speed
	if (elapsed_time > shift_speed)  // Shift colors only after certain time passes
	{
		f->r = (f->r + (int)(elapsed_time * 20)) % 256;
		f->g = (f->g + (int)(elapsed_time * 30)) % 256;
		f->b = (f->b + (int)(elapsed_time * 40)) % 256;

		//f->base_color = ((f->r << 24) | (f->g << 16) | (f->b << 8) | f->a);
		// Update the previous time
		previous_time = current_time;
	}
}
