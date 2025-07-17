/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:55:01 by fzucconi          #+#    #+#             */
/*   Updated: 2025/05/07 12:10:15 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

float	f_max(float a, float b, float c)
{
	return (fmax(a, fmax(b, c)));
}

float	f_min(float a, float b, float c)
{
	return (fmin(a, fmin(b, c)));
}

double	ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;
	int		sign;

	c = (char *)str;
	if (*c == '-')
		sign = -1;
	else
		sign = 1;
	res = (double)ft_atoi(c);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	res2 = (double)ft_atoi(c);
	len = ft_strlen(c);
	while (len--)
		res2 /= 10;
	return (sign * (fabs(res) + res2));
}

void	exit_error(t_world *world, char **words, const char *err)
{
	if (world)
		free_world(world);
	if (words)
		ft_free_matrix(words);
	write(2, err, ft_strlen(err));
	exit (-1);
}

void	free_world(t_world *world)
{
	int	i;

	i = 0;
	if (world->obj)
	{
		while (i < world->n_obj)
		{
			if (world->obj[i].obj)
				free(world->obj[i].obj);
			i++;
		}
		free(world->obj);
	}
	if (world->lights)
		free(world->lights);
}
