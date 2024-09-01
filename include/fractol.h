/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:05:13 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/01 16:19:53 by hskrzypi         ###   ########.fr       */
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

#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000
#define MAX_ITER 100

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
	int	mono_color;
	t_complex	c;
	int	r;
	int	g;
	int	b;
	int	a;
}	t_fractol;

int	initialize_mandelbrot(void);
int	mandelbrot(t_fractol *data);
void	draw_mandelbrot(t_fractol *data);

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
uint32_t        color_generator(int i, t_fractol *f);

void	key_press(struct mlx_key_data k_data, void *param);

#endif
