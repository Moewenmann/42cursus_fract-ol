/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:18:29 by jmuhlber          #+#    #+#             */
/*   Updated: 2024/03/30 23:09:41 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	itermandelbrot(t_calc_data *data);

void	mandelbrot_p(t_fractol *frct, int argc, char **argv)
{
	(void)argv;
	frct->scale -= 0.5;
	frct->shift_x = 0.73;
	frct->shift_y = 0.5;
	if (argc == 2)
		return (mandelbrot(frct));
	else
		return (mandelbrot(frct));
}

void	mandelbrot(t_fractol *frct)
{
	t_calc_data	*data;
	int			i;
	int			col;

	data = malloc(sizeof(t_calc_data));
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
			i = itermandelbrot(data);
			col = get_rgba(i * 255 / ITER_LIM / 7, i * 255 / ITER_LIM / 3,
					i * 255 / ITER_LIM, 255);
			mlx_put_pixel(frct->img, data->x, data->y, col);
		}
		data->y += 1;
	}
	free(data);
}

static int	itermandelbrot(t_calc_data *data)
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
		data->xp = data->square_xy + data->xc;
		data->yp = data->xpyp + data->yc;
		if (data->square_x + data->square_y > 8)
			return (i);
		i += 1;
	}
	return (i);
}
