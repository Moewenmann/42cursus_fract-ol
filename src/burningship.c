/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:31:57 by julian            #+#    #+#             */
/*   Updated: 2024/03/31 22:45:31 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	iterburningship(t_fractol *frct, t_calc_data *data);
static int	color_brnshp(t_fcol *c, int i);

void	burningship_p(t_fractol *frct, int argc, char **argv)
{
	frct->shift_x = 0.5;
	frct->shift_y = 0.5;
	if (argc == 2)
		return (frct->param1 = -1.8, frct->param2 = -0.08, burningship(frct));
	eval_params(frct, argc, argv);
	if (argc == 3)
		return (frct->param2 = -0.08, burningship(frct));
	else if (argc == 4)
		return (burningship(frct));
}

void	burningship(t_fractol *frct)
{
	t_calc_data	*data;
	t_fcol		*col;
	int			i;

	if (!(data = malloc(sizeof(t_calc_data)))
		|| !(col = malloc(sizeof(t_fcol))))
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
			i = iterburningship(frct, data);
			mlx_put_pixel(frct->img, data->x, data->y, color_brnshp(col, i));
			data->x += 1;
		}
		data->y += 1;
	}
	return (free(data), free(col));
}

static int	iterburningship(t_fractol *frct, t_calc_data *data)
{
	int		i;

	i = 0;
	while (i < ITER_LIM)
	{
		data->square_x = data->xp * data->xp;
		data->square_y = data->yp * data->yp;
		if (data->xp * data->yp < 0)
			data->xpyp = -2 * data->xp * data->yp;
		else
			data->xpyp = 2 * data->xp * data->yp;
		data->square_xy = data->square_x - data->square_y;
		data->xp = data->square_xy + frct->param1;
		data->yp = data->xpyp + frct->param2;
		if (data->square_x + data->square_y > 8)
			return (i);
		i += 1;
	}
	return (i);
}

static int	color_brnshp(t_fcol *c, int i)
{
	double	theta;

	if (i > (ITER_LIM - 90))
	{
		theta = (i - 4) * M_PI / 10.0;
		c->red = (int)(192.0 + 64.0 * sin(theta + 2.0 * M_PI / 30.0));
		c->green = (int)(128.0 + 64.0 * sin(theta));
		c->blue = (int)(64.0 + 64.0 * sin(theta + 4.0 * M_PI / 3.0));
		return (get_rgba(c->red, c->green, c->blue, 255));
	}
	else if (i > (ITER_LIM - 91))
		return (c->shade = ((i + 4)* 255 / ITER_LIM),
				get_rgba(c->shade, c->shade, c->shade, 255));
	else if (i > (ITER_LIM - 93))
		return (c->shade = ((i + 7)* 255 / ITER_LIM),
				get_rgba(c->shade, c->shade, c->shade, 255));
	else if (i > (ITER_LIM - 95))
		return (c->shade = ((i + 9)* 255 / ITER_LIM),
				get_rgba(c->shade, c->shade, c->shade, 255));
	else if (i > (ITER_LIM - 97))
		return (c->shade = ((i + 11)* 255 / ITER_LIM),
				get_rgba(c->shade, c->shade, c->shade, 255));
	else
		return (c->shade = ((i + 15)* 255 / ITER_LIM),
				get_rgba(c->shade, c->shade, c->shade, 255));
}

/* static int	color_brnshp(t_fcol *c, int i)
{
	double	theta;

	if (i > (ITER_LIM - 90))
	{
		theta = (i - 4) * M_PI / 10.0;
		c->red = (int)(192.0 + 64.0 * sin(theta + 2.0 * M_PI / 30.0));
		c->green = (int)(128.0 + 64.0 * sin(theta));
		c->blue = (int)(64.0 + 64.0 * sin(theta + 4.0 * M_PI / 3.0));
		return (get_rgba(c->red, c->green, c->blue, 255));
	}
	else if (i > (ITER_LIM - 94))
	{
		c->shade = i * 255 / ITER_LIM;
		return (get_rgba(c->shade, c->shade, c->shade, 255));
	}
	else if (i > (ITER_LIM - 97))
	{
		c->shade = (i + 3) * 255 / ITER_LIM;
		return (get_rgba(c->shade, c->shade, c->shade, 255));
	}
	else
	{
		c->shade = (i + 10) * 255 / ITER_LIM;
		return (get_rgba(c->shade, c->shade, c->shade, 255));
	}
} */
