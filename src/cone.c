/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:15:44 by fzucconi          #+#    #+#             */
/*   Updated: 2025/03/25 14:15:44 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

t_cone	*basic_cone( void )
{
	t_cone	*cone;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (NULL);
	cone->type = 'K';
	cone->id = 0;
	cone->transform = identity_matrix();
	cone->material = base_material();
	cone->center = create_point(0, 0, 0);
	cone->dimensions = create_point(3.0f, 6.0f, 1.0f);
	cone->is_closed = 0;
	cone->maximum_y = 0;
	cone->minimum_y = -(cone->dimensions.y / 2);
	return (cone);
}

t_vector	cone_normal_at(t_cone *cone, t_vector point)
{
	float		dist;
	t_vector	normal;
	t_vector	local_point;

	local_point = mult_matrix_vector(matrix_inversion(cone->transform), point);
	dist = sqrtf((local_point.x * local_point.x)
			+ (local_point.z * local_point.z));
	if (dist < EPSILON && local_point.y >= (cone->maximum_y - EPSILON))
		normal = ((create_vector(0, 1, 0)));
	else if (dist < EPSILON && local_point.y <= (cone->minimum_y + EPSILON))
		normal = ((create_vector(0, -1, 0)));
	else
		normal = ((create_vector(local_point.x,
						- (sqrtf(local_point.x
								* local_point.x + local_point.z
								* local_point.z)), local_point.z)));
	return (normalize(mult_matrix_vector(
				transpose_matrix(matrix_inversion(cone->transform)), normal)));
}

void	quadratic_calcs(cone_xs_data_t *data, t_cone *cone, t_ray ray)
{
	data->inverse_transform = matrix_inversion(cone->transform);
	data->local_ray.origin = mult_matrix_vector(data->inverse_transform,
			ray.origin);
	data->local_ray.direction = mult_matrix_vector(data->inverse_transform,
			ray.direction);
	data->radius = cone->dimensions.x;
	data->height = cone->maximum_y - cone->minimum_y;
	data->a = data->local_ray.direction.x * data->local_ray.direction.x
		+ data->local_ray.direction.z * data->local_ray.direction.z
		- (data->radius * data->radius / (data->height * data->height))
		* data->local_ray.direction.y * data->local_ray.direction.y;
	data->b = 2.0f * (data->local_ray.origin.x * data->local_ray.direction.x
			+ data->local_ray.origin.z * data->local_ray.direction.z)
		- 2.0f * (data->radius * data->radius
			/ (data->height * data->height)) * data->local_ray.origin.y
		* data->local_ray.direction.y;
	data->c = data->local_ray.origin.x * data->local_ray.origin.x
		+ data->local_ray.origin.z * data->local_ray.origin.z
		- (data->radius * data->radius / (data->height * data->height))
		* data->local_ray.origin.y * data->local_ray.origin.y;
	data->disc = data->b * data->b - 4 * data->a * data->c;
}

t_intersection	*ray_intersect_cone(
	t_intersection *xs, t_cone *cone, t_ray ray)
{
	t_matrix		inverse_transform;
	t_ray			local_ray;
	cone_xs_data_t	data;

	quadratic_calcs(&data, cone, ray);
	if (data.disc < EPSILON)
		return (xs);
	data.t[0] = (-data.b - sqrtf(data.disc)) / (2 * data.a);
	data.t[1] = (-data.b + sqrtf(data.disc)) / (2 * data.a);
	if (data.t[0] > data.t[1])
	{
		data.temp = data.t[0];
		data.t[0] = data.t[1];
		data.t[1] = data.temp;
	}
	data.i = -1;
	while (++(data.i) < 2)
	{
		data.y[data.i] = local_ray.origin.y + t[data.i] * local_ray.direction.y;
		if (y[data.i] >= cone->minimum_y + EPSILON
			&& y[data.i] <= cone->maximum_y - EPSILON)
			xs = add_intersection(xs,
					init_intersection(t[data.i], 'K', cone, cone->id));
	}
	return (xs);
}
