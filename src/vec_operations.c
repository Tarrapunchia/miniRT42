/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:51:32 by fzucconi          #+#    #+#             */
/*   Updated: 2025/04/14 14:51:32 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vector	add_vec(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.is_point = a.is_point + b.is_point;
	return (result);
}

t_vector	sub_vec(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.is_point = a.is_point - b.is_point;
	return (result);
}

t_vector	negate_vec(t_vector a)
{
	t_vector	result;

	result.x = -1 * a.x;
	result.y = -1 * a.y;
	result.z = -1 * a.z;
	result.is_point = a.is_point;
	return (result);
}

t_vector	mul_vectors(t_vector a, t_vector b)
{
	return ((t_vector){
		a.x * b.x,
		a.y * b.y,
		a.z * b.z,
		a.is_point * b.is_point
	});
}

t_vector	scalar_mult_vec(t_vector a, float b)
{
	t_vector	result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	result.is_point = a.is_point;
	return (result);
}
