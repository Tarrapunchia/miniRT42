/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:56:07 by fzucconi          #+#    #+#             */
/*   Updated: 2025/04/14 14:59:04 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vector	scalar_div_vec(t_vector a, float b)
{
	t_vector	result;

	if (b == 0)
		return ((t_vector){0, 0, 0, 1});
	result.x = a.x / b;
	result.y = a.y / b;
	result.z = a.z / b;
	result.is_point = a.is_point;
	return (result);
}

float	magnitude_vec(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vector	normalize(t_vector a)
{
	t_vector	result;

	if (magnitude_vec(a) == 0)
		return ((t_vector){0, 0, 0, 1});
	else
	{
		result.x = a.x / magnitude_vec(a);
		result.y = a.y / magnitude_vec(a);
		result.z = a.z / magnitude_vec(a);
		result.is_point = a.is_point;
	}
	return (result);
}

float	dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x
		+ a.y * b.y
		+ a.z * b.z);
}

t_vector	cross_product(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	result.is_point = a.is_point;
	return (result);
}
