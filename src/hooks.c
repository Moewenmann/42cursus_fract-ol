/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:18:27 by jmuhlber          #+#    #+#             */
/*   Updated: 2024/03/30 10:30:01 by julian           ###   ########.fr       */
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
	else if (keydata.key == MLX_KEY_KP_ADD && keydata.action == MLX_PRESS)
		return (frct->scale *= 1.1, runfrct(frct));
	else if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
		return (frct->scale /= 1.1, runfrct(frct));
	else
		return ;
}

void	mouseaction(double a, double b, void *params)
{
	t_fractol	*frct;
	double		f;
	int32_t	mx;
	int32_t	my;

	(void)a;
	frct = (t_fractol *)params;
	mlx_get_mouse_pos(frct->mlx, &mx, &my);
	if (b > 0)
		f = 0.8;
	else
		f = 1.2;
	frct->scale *= f;
	runfrct(frct);
}

void	resizeaction(int a, int b, void *params)
{
	t_fractol	*frct;
	double		ratio;
	double		new_ratio;

	frct = (t_fractol *)params;
	frct->width = a;
	frct->height = b;
	ratio = (double)frct->width / (double)frct->height;
	new_ratio = (double)a / (double)b;
	if (ratio < new_ratio)
	{
		frct->width = a;
		frct->height = a / ratio;
	}
	else
	{
		frct->width = b * ratio;
		frct->height = b;
	}
	mlx_resize_image(frct->img, frct->width, frct->height);
	runfrct(frct);
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
