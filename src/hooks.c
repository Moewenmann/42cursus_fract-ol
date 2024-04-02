/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuhlber <jmuhlber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:18:27 by jmuhlber          #+#    #+#             */
/*   Updated: 2024/04/02 16:13:17 by jmuhlber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	runfrct(t_fractol *frct);

/**
 * Handles keyboard input for fractal navigation and scaling.
 * 
 * @param keydata Keyboard data containing the pressed key.
 * @param params void pointer to the fractol struct.
 */
void	keyaction(mlx_key_data_t keydata, void *params)
{
	t_fractol	*frct;

	frct = (t_fractol *)params;
	if (keydata.key == MLX_KEY_ESCAPE)
		frct_quit(frct, FQ_OK);
	else if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		return (frct->shift_y -= 0.05, runfrct(frct));
	else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		return (frct->shift_y += 0.05, runfrct(frct));
	else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
		return (frct->shift_x -= 0.05, runfrct(frct));
	else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
		return (frct->shift_x += 0.05, runfrct(frct));
	else if (keydata.key == MLX_KEY_KP_ADD)
		return (frct->scale *= 0.8, runfrct(frct));
	else if (keydata.key == MLX_KEY_KP_SUBTRACT)
		return (frct->scale *= 1.2, runfrct(frct));
	else
		return ;
}

/**
 * Handles mouse actions for fractal zooming.
 * 
 * @param a unused.
 * @param b Mouse scroll direction (zoom in, zoom out).
 * @param params void pointer to the fractol struct.
 */
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
	frct->shift_x += ((double)mx - frct->width / 1.95) * delta / frct->width;
	frct->shift_y += ((double)my - frct->height / 1.95) * delta / frct->height;
	runfrct(frct);
}

/**
 * Resizes the fractal window and adjusts image dimensions accordingly.
 * 
 * @param a New width of the window.
 * @param b New height of the window.
 * @param params void pointer to the fractol struct.
 */
void	resizeaction(int a, int b, void *params)
{
	t_fractol	*frct;
	double		ratio;
	double		img_ratio;

	frct = (t_fractol *)params;
	frct->width = a;
	frct->height = b;
	img_ratio = frct->width / frct->height;
	ratio = (double)a / (double)b;
	if (ratio > img_ratio)
		frct->width = b * img_ratio;
	else
		frct->height = a / img_ratio;
	mlx_resize_image(frct->img, frct->width, frct->height);
	runfrct(frct);
}

/**
 * Frees and exits the program properly with no errors.
 * 
 * @param (void)*params void pointer to the fractol struct.
 */
void	quitaction(void *params)
{
	t_fractol	*frct;

	frct = (t_fractol *)params;
	frct_quit(frct, FQ_OK);
}

/**
 * Runs the selected fractal calculation.
 * 
 * @param frct The fractal data struct.
 
 */
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
