/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuhlber <jmuhlber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:18:31 by jmuhlber          #+#    #+#             */
/*   Updated: 2024/04/02 13:19:43 by jmuhlber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	ft_atof(const char *str);
static int		ft_is_space(const char *str);
static double	atof_parse_number(const char *str, double *f, int *d);

int	get_rgba(int red, int green, int blue, int alpha)
{
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

int	eval_params(t_fractol *frct, int argc, char **argv)
{
	int	i;

	i = 0;
	while (argv[2][i])
	{
		if (!ft_isdigit(argv[2][i]) && argv[2][i] != '.' && argv[2][i] != '-')
			return (ft_printf("%s\n", MSG_PARAM), frct_quit(frct, FQ_ERR), 1);
		i += 1;
	}
	if (argc == 3)
		return (frct->param1 = ft_atof(argv[2]));
	i = 0;
	while (argv[3][i])
	{
		if (!ft_isdigit(argv[3][i]) && argv[3][i] != '.' && argv[3][i] != '-')
			return (ft_printf("%s\n", MSG_PARAM), frct_quit(frct, FQ_ERR), 1);
		i += 1;
	}
	if (argc == 4)
	{
		frct->param1 = ft_atof(argv[2]);
		frct->param2 = ft_atof(argv[3]);
	}
	return (1);
}

static double	ft_atof(const char *str)
{
	double	res;
	double	fraction;
	int		prefix;
	int		decimals;

	res = 0.0;
	fraction = 0.0;
	prefix = 1;
	decimals = 1;
	while (ft_is_space(str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			prefix = -1;
		str++;
	}
	res = atof_parse_number(str, &fraction, &decimals);
	return ((res + fraction / decimals) * prefix);
}

static int	ft_is_space(const char *str)
{
	if (*str == ' ' || *str == '\t'
		|| *str == '\r' || *str == '\n'
		|| *str == '\f' || *str == '\v')
		return (1);
	else
		return (0);
}

static double	atof_parse_number(const char *str, double *f, int *d)
{
	double	res;

	res = 0.0;
	while (ft_isdigit(*str) || *str == '.')
	{
		if (*str == '.')
		{
			*d = 1;
			str++;
			continue ;
		}
		if (!(*d))
			res = (res * 10) + (*str - '0');
		else
		{
			*f = (*f * 10) + (*str - '0');
			*d *= 10;
		}
		str++;
	}
	return (res);
}
