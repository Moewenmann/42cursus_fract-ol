/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:18:31 by jmuhlber          #+#    #+#             */
/*   Updated: 2024/03/30 16:07:19 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

static int	ft_check_space(const char *str)
{
	if (*str == ' ' || *str == '\t'
		|| *str == '\r' || *str == '\n'
		|| *str == '\f' || *str == '\v')
		return (1);
	else
		return (0);
}

double	ft_atof(const char *str)
{
	double	res;
	double	fraction;
	int		prefix;
	int		decimals;

	res = 0.0;
	fraction = 0.0;
	prefix = 1;
	decimals = 1;
	while (ft_check_space(str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			prefix = -1;
		str++;
	}
	while (ft_isdigit(*str) || *str == '.')
	{
		if (*str == '.')
		{
			decimals = 1;
			str++;
			continue ;
		}
		if (!decimals)
			res = (res * 10) + (*str - '0');
		else
		{
			fraction = (fraction * 10) + (*str - '0');
			decimals *= 10;
		}
		str++;
	}
	return ((res + fraction / decimals) * prefix);
}
