/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:17:36 by jmuhlber          #+#    #+#             */
/*   Updated: 2024/03/30 16:07:27 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init(t_fractol *frct, int argc, char **argv);

int	main(int argc, char **argv)
{
	t_fractol	*frct;

	if (argc < 2 || argc > 4)
		return (ft_printf("Usage: %s %s\n", argv[0], MSG_USAGE), 1);
	frct = malloc(sizeof(t_fractol));
	if (!frct)
		return (frct = NULL, ft_printf("%s\n", MEM_FAIL), 1);
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		frct->fractal_type = 1;
	else if (ft_strncmp(argv[1], "julia", 6) == 0)
		frct->fractal_type = 2;
	else if (ft_strncmp(argv[1], "burningship", 6) == 0)
		frct->fractal_type = 3;
	else
		return (ft_printf("Usage: %s %s\n", argv[0], MSG_USAGE),
			frct_quit(frct, FQ_ERR), 1);
	init(frct, argc, argv);
	mlx_loop(frct->mlx);
	mlx_terminate(frct->mlx);
	frct_quit (frct, FQ_OK);
	return (0);
}

static void	init(t_fractol *frct, int argc, char **argv)
{
	frct->width = FRCT_WIDTH;
	frct->height = FRCT_HEIGHT;
	frct->scale = FRCT_SCALE;
	if (frct->fractal_type == 1)
		frct->mlx = mlx_init(frct->width, frct->height, TITLE_MANDELBROT, true);
	else if (frct->fractal_type == 2)
		frct->mlx = mlx_init(frct->width, frct->height, TITLE_JULIA, true);
	else if (frct->fractal_type == 3)
		frct->mlx = mlx_init(frct->width, frct->height, TITLE_BRNSHIP, true);
	else
		return (ft_printf("%s\n", MLX_FAIL), frct_quit(frct, FQ_ERR));
	if (!frct->mlx)
		return (ft_printf("%s\n", MLX_FAIL), frct_quit(frct, FQ_ERR));
	frct->img = mlx_new_image(frct->mlx, frct->width, frct->height);
	mlx_image_to_window(frct->mlx, frct->img, 0, 0);
	mlx_resize_hook(frct->mlx, resizeaction, frct);
	mlx_key_hook(frct->mlx, keyaction, frct);
	mlx_scroll_hook(frct->mlx, mouseaction, frct);
	if (frct->fractal_type == 1)
		mandelbrot_p(frct, argc, argv);
	else if (frct->fractal_type == 2)
		julia_p(frct, argc, argv);
	else if (frct->fractal_type == 3)
		burningship_p(frct, argc, argv);
}

void	frct_quit(t_fractol *frct, const int is_err)
{
	if (is_err)
	{
		free(frct);
		exit(1);
	}
	else
	{
		free(frct);
		exit(0);
	}
}
