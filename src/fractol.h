/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:17:33 by jmuhlber          #+#    #+#             */
/*   Updated: 2024/03/30 22:42:37 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# include "../lib/libft/libft.h"
# include "../lib/mlx/include/MLX42/MLX42.h"

typedef struct s_fractol
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				fractal_type;
	double			width;
	double			height;
	double			scale;
	double			shift_x;
	double			shift_y;
	double			param1;
	double			param2;
}				t_fractol;

typedef struct s_calc_data
{
	int				x;
	int				y;
	double			xp;
	double			yp;
	double			xc;
	double			yc;
	double			square_x;
	double			square_y;
	double			square_xy;
	double			xpyp;
}				t_calc_data;

typedef struct s_frct_rgba
{
	int				red;
	int				green;
	int				blue;
	int				alpha;
}				t_frct_rgba;

# ifndef MSG_USAGE
#  define MSG_USAGE "[mandelbrot | julia] <rendering options>"
# endif

# ifndef MLX_FAIL
#  define MLX_FAIL "Error: mlx_init() failed!"
# endif

# ifndef MEM_FAIL
#  define MEM_FAIL "Error: memory allocation failed!"
# endif

# ifndef MSG_PARAM
#  define MSG_PARAM "Wrong parameter type! Only numbers or specific keywords are allowed."
# endif

# ifndef TITLE_MANDELBROT
#  define TITLE_MANDELBROT "42 Fract'ol - Mandelbrot"
# endif

# ifndef TITLE_JULIA
#  define TITLE_JULIA "42 Fract'ol - Julia"
# endif

# ifndef TITLE_BRNSHIP
#  define TITLE_BRNSHIP "42 Fract'ol - Burning Ship"
# endif

# ifndef FQ_ERR
#  define FQ_ERR 1
# endif

# ifndef FQ_OK
#  define FQ_OK 0
# endif

# ifndef FRCT_WIDTH
#  define FRCT_WIDTH 1080
# endif

# ifndef FRCT_HEIGHT
#  define FRCT_HEIGHT 1080
# endif

# ifndef FRCT_SCALE
#  define FRCT_SCALE 3.5
# endif

# ifndef ITER_LIM
#  define ITER_LIM 100
# endif

void	mandelbrot_p(t_fractol *frct, int argc, char **argv);
void	mandelbrot(t_fractol *frct);

void	julia_p(t_fractol *frct, int argc, char **argv);
void	julia(t_fractol *frct);

void	burningship_p(t_fractol *frct, int argc, char **argv);
void	burningship(t_fractol *frct);

void	keyaction(mlx_key_data_t keydata, void *params);
void	mouseaction(double a, double b, void *params);
void	resizeaction(int width, int height, void *params);
void	quitaction(void *params);

int		eval_params(t_fractol *frct, int argc, char **argv);
int		get_rgba(int red, int green, int blue, int alpha);
void	frct_quit(t_fractol *frct, const int is_err);;
double	ft_atof(const char *s);

#endif
