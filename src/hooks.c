/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:18:27 by jmuhlber          #+#    #+#             */
/*   Updated: 2024/03/31 06:38:57 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	runfrct(t_fractol *frct);

void	keyaction(mlx_key_data_t keydata, void *params)
{
	t_fractol	*frct;

	frct = (t_fractol *)params;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		frct_quit(frct, FQ_OK);
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		return (frct->shift_y -= 0.05, runfrct(frct));
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		return (frct->shift_y += 0.05, runfrct(frct));
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		return (frct->shift_x -= 0.05, runfrct(frct));
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		return (frct->shift_x += 0.05, runfrct(frct));
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		return (frct->scale *= 1.2, runfrct(frct));
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		return (frct->scale *= 0.8, runfrct(frct));
	else
		return ;
}

void	mouseaction(double a, double b, void *params)
{
	t_fractol	*frct;
	int32_t		mx;
	int32_t		my;
	double		f;
	double		delta;

	(void)a;
	frct = (t_fractol *)params;
	mlx_get_mouse_pos(frct->mlx, &mx, &my);
	mlx_set_mouse_pos(frct->mlx, mx, my);
	if (b > 0)
		f = 0.8;
	else
		f = 1.2;
	frct->scale *= f;
	delta = 4.0 * (f - 1) / frct->scale;
	frct->shift_x += (mx - frct->width / 2) * delta / frct->width;
	frct->shift_y += (my - frct->height / 2) * delta / frct->height;
	runfrct(frct);
}

void	resizeaction(int a, int b, void *params)
{
	t_fractol	*frct;
	double		ratio;
	double		img_ratio;

	frct = (t_fractol *)params;
	frct->width = a;
	frct->height = b;
	img_ratio = (double)frct->width / (double)frct->height;
	ratio = (double)a / (double)b;
	if (ratio > img_ratio)
		frct->width = b * img_ratio;
	else
		frct->height = a / img_ratio;
	mlx_resize_image(frct->img, frct->width, frct->height);
	runfrct(frct);
}

void	quitaction(void *params)
{
	t_fractol	*frct;

	frct = (t_fractol *)params;
	frct_quit(frct, FQ_OK);
}

static void	runfrct(t_fractol *frct)
{
	if (frct->fractal_type == 1)
		mandelbrot(frct);
	else if (frct->fractal_type == 2)
		julia(frct);
	else if (frct->fractal_type == 3)
		burningship(frct);
	return ;
}
