/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:40:36 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/14 19:14:24 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

# include <unistd.h>
# include "../libft/complete_Libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

#define WIDTH 1000
#define HEIGHT 1000
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
	double	zoom;
	double	offset_x;
	double	offset_y;
	int32_t	mouse_x;
	int32_t	mouse_y;
	int	mono_color;
	t_complex	c;
	t_complex	z;
	int	r;
	int	g;
	int	b;
	int	a;
	double	t;
	int	bw_mode;
	int	rainbow_mode;
	int	fractal_type;
}	t_fractol;

typedef struct s_color
{
	double	h;
	double	s;
	double	v;
	int	r;
	int	g;
	int	b;
}	t_color;

long double  str_to_double(const char *arg);
void	init_values(t_fractol *fractal);
void	input_error(void);
int	initialize_fractal(t_fractol *f);
int	fractal_iteration(t_fractol *fractal);
void	draw_fractal(t_fractol *f);
void	pixel_comlex(t_fractol *f, int x, int y);

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
uint32_t        color_generator(int i, t_fractol *f);
uint32_t	get_pixel_color(int iteration, t_fractol *f);
uint32_t	grayscale_generator(int i,t_fractol *f);

void	key_press(struct mlx_key_data k_data, void *param);
void	window_close(t_fractol *fractal);
void	cursor_move(double xpos, double ypos, void *param);
void	mouse_scroll(double xdelta, double ydelta, void *param);

#endif
