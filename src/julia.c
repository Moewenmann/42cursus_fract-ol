/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:18:23 by jmuhlber          #+#    #+#             */
/*   Updated: 2024/03/29 21:59:23 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	iterjulia(t_fractol *frct, t_calc_data *data);

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
	int			i;
	int			col;

	data = malloc(sizeof(t_calc_data));
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
			col = (i * 255 / ITER_LIM);
			mlx_put_pixel(frct->img, data->x, data->y, col);
			data->x += 1;
		}
		data->y += 1;
	}
	free(data);
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
