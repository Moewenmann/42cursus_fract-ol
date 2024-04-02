/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuhlber <jmuhlber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:18:29 by jmuhlber          #+#    #+#             */
/*   Updated: 2024/04/02 15:42:06 by jmuhlber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	itermandelbrot(t_fractol *frct, t_calc_data *data);
static int	color_mandel(t_fcol *c, int i);

/**
 * Sets up parameters and invokes the Mandelbrot fractal calculation.
 * 
 * @param frct Pointer to the fractol struct.
 * @param argc Number of arguments.
 * @param argv Array of argument strings.
 */
void	mandelbrot_p(t_fractol *frct, int argc, char **argv)
{
	(void)argv;
	frct->scale -= 0.5;
	frct->shift_x = 0.73;
	frct->shift_y = 0.5;
	if (argc == 2)
		return (frct->param1 = 0, frct->param2 = 0, mandelbrot(frct));
	eval_params(frct, argc, argv);
	if (argc == 3)
		return (frct->param2 = 0, mandelbrot(frct));
	if (argc == 4)
		return (mandelbrot(frct));
}

void	mandelbrot(t_fractol *frct)
{
	t_calc_data	*data;
	t_fcol		*col;
	int			i;

	data = malloc(sizeof(t_calc_data));
	col = malloc(sizeof(t_fcol));
	if (!data || !col)
		return (ft_printf("%s\n", MEM_FAIL), frct_quit(frct, FQ_ERR));
	data->y = 0;
	while (data->y < frct->height)
	{
		data->x = 0;
		while (data->x < frct->width)
		{
			data->x += 1;
			data->xp = ((double)data->x / frct->width - frct->shift_x)
				* frct->scale;
			data->yp = ((double)data->y / frct->height - frct->shift_y)
				* frct->scale;
			i = itermandelbrot(frct, data);
			mlx_put_pixel(frct->img, data->x, data->y, color_mandel(col, i));
		}
		data->y += 1;
	}
	return (free(data), free(col));
}

static int	itermandelbrot(t_fractol *frct, t_calc_data *data)
{
	int	i;

	data->xc = data->xp;
	data->yc = data->yp;
	i = 0;
	while (i < ITER_LIM)
	{
		data->square_x = data->xp * data->xp;
		data->square_y = data->yp * data->yp;
		data->xpyp = data->xp * data->yp * 2;
		data->square_xy = data->square_x - data->square_y;
		data->xp = data->square_xy + data->xc + frct->param1;
		data->yp = data->xpyp + data->yc + frct->param2;
		if (data->square_x + data->square_y > 10)
			return (i);
		i += 1;
	}
	return (i);
}

/**
 * Generates color for the Mandelbrot set based on the iteration count.
 * 
 * @param c Pointer to the struct holding color parameters.
 * @param i Iteration count.
 * @return Combined RGBA color value as an integer.
 */
static int	color_mandel(t_fcol *c, int i)
{
	double	theta;

	if (i > (ITER_LIM - 90))
	{
		theta = (i - 4) * M_PI / 10.0;
		c->red = (int)(128.0 + 124.0 * sin(theta + 3.0 * M_PI / 31.0));
		c->green = (int)(128.0 + 124.0 * sin(theta + 4.0 * M_PI / 14.0));
		c->blue = (int)(128.0 + 124 * sin(theta + 4.0 * M_PI / 3.0));
		return (get_rgba(c->red, c->green, c->blue, 255));
	}
	else if (i > (ITER_LIM - 89))
	{
		c->shade = i * 255 / ITER_LIM;
		return (get_rgba(c->shade, c->shade, c->shade, 255));
	}
	else
	{
		c->shade = (i + 10) * 255 / ITER_LIM;
		return (get_rgba(c->shade, c->shade, c->shade, 255));
	}
}
