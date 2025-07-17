/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-09 15:44:24 by fzucconi          #+#    #+#             */
/*   Updated: 2025-04-09 15:44:24 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

t_ray	init_ray(t_vector origin, t_vector direction)
{
	t_ray		ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_vector	ray_position(t_ray ray, float t)
{
	t_vector	new_position;

	new_position = scalar_mult_vec(ray.direction, t);
	new_position = add_vec(ray.origin, new_position);
	return (new_position);
}

t_ray	transform_ray(t_ray ray, t_matrix matrix, char type)
{
	t_ray	new_ray;

	new_ray.origin = mult_matrix_vector(matrix, ray.origin);
	if (type == TRANSLATE)
		new_ray.direction = normalize(mult_matrix_vector(matrix, ray.origin));
	else if (type == SCALE)
		new_ray.direction = mult_matrix_vector(matrix, ray.origin);
	return (new_ray);
}
