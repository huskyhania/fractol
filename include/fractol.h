/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:05:13 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/08/31 19:28:46 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include "../libft/complete_Libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <errno.h>
# include <stdio.h>
# include <string.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 800
#define MAX_ITER 100
//#define COLOR_CHOICE(r, g, b, a) ((r << 24) | (g  << 16) | (b << 8) | a)

typedef struct	s_complex
{
	double	real;
	double	imagi;
}	t_complex;

typedef struct	s_fractol
{
	mlx_t	*mlx_ptr;
	mlx_image_t	*img_ptr;
	int32_t	img_instance;
	double	real_min;
	double	real_max;
	double	imagi_min;
	double	imagi_max;
	t_complex	c;
}	t_fractol;

int	initialize_mandelbrot(void);
int	mandelbrot(t_fractol *data);
void	draw_mandelbrot(t_fractol *data);

#endif
