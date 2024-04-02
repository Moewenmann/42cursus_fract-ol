/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuhlber <jmuhlber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:18:23 by jmuhlber          #+#    #+#             */
/*   Updated: 2024/04/02 13:13:18 by jmuhlber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	iterjulia(t_fractol *frct, t_calc_data *data);
static int	color_julia(t_fcol *c, int i);

void	julia_p(t_fractol *frct, int argc, char **argv)
{
	frct->shift_x = 0.5;
	frct->shift_y = 0.5;
	if (argc == 2)
		return (frct->param1 = -0.79, frct->param2 = 0.155, julia(frct));
	eval_params(frct, argc, argv);
	if (argc == 3)
		return (frct->param2 = 0.155, julia(frct));
	else if (argc == 4)
		return (julia(frct));
}

void	julia(t_fractol *frct)
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
			data->xp = ((double)data->x / frct->width - frct->shift_x)
				* frct->scale;
			data->yp = ((double)data->y / (frct->height / (frct->height
							/ frct->width)) - frct->shift_y) * frct->scale;
			i = iterjulia(frct, data);
			mlx_put_pixel(frct->img, data->x, data->y, color_julia(col, i));
			data->x += 1;
		}
		data->y += 1;
	}
	return (free(data), free(col));
}

static int	iterjulia(t_fractol *frct, t_calc_data *data)
{
	int		i;

	i = 0;
	while (i < ITER_LIM)
	{
		data->square_x = data->xp * data->xp;
		data->square_y = data->yp * data->yp;
		data->xpyp = data->xp * data->yp * 2;
		data->square_xy = data->square_x - data->square_y;
		data->xp = data->square_xy + frct->param1;
		data->yp = data->xpyp + frct->param2;
		if (data->square_x + data->square_y > 8)
			return (i);
		i += 1;
	}
	return (i);
}

static int	color_julia(t_fcol *c, int i)
{
	double	theta;

	if (i > (ITER_LIM - 40))
	{
		theta = (i - 4) * M_PI / 11.0;
		c->red = (int)(128.0 + 124.0 * sin(theta + 2.0 * M_PI / 4.0));
		c->green = (int)(128.0 + 127.0 * sin(theta));
		c->blue = (int)(128.0 + 124.0 * sin(theta + 4.0 * M_PI / 3.0));
		return (get_rgba(c->red, c->green, c->blue, 255));
	}
	else if (i > (ITER_LIM - 30))
	{
		c->shade = i * 255 / ITER_LIM;
		return (get_rgba(c->shade, c->shade, c->shade, 255));
	}
	else
	{
		c->shade = i + 10 * 255 / ITER_LIM;
		return (get_rgba(c->shade, c->shade, c->shade, 255));
	}
}
