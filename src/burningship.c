/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:31:57 by julian            #+#    #+#             */
/*   Updated: 2024/03/30 23:14:44 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	iterburningship(t_fractol *frct, t_calc_data *data);

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
			i = iterburningship(frct, data);
			col = get_rgba(i * 255 / ITER_LIM + 5, i * 255 / ITER_LIM / 2 + 5, i * 255 / ITER_LIM / 15, 255);
			mlx_put_pixel(frct->img, data->x, data->y, col);
			data->x += 1;
		}
		data->y += 1;
	}
	free(data);
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
