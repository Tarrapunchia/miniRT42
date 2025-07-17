/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:39:11 by fzucconi          #+#    #+#             */
/*   Updated: 2025/04/08 14:39:16 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

t_matrix	rotation_y(float radians)
{
	t_matrix	matrix;

	matrix = identity_matrix();
	matrix.matrix[0][0] = cos(radians);
	matrix.matrix[0][2] = sin(radians);
	matrix.matrix[2][0] = -sin(radians);
	matrix.matrix[2][2] = cos(radians);
	return (matrix);
}

t_matrix	rotation_z(float radians)
{
	t_matrix	matrix;

	matrix = identity_matrix();
	matrix.matrix[0][0] = cos(radians);
	matrix.matrix[0][1] = -sin(radians);
	matrix.matrix[1][0] = sin(radians);
	matrix.matrix[1][1] = cos(radians);
	return (matrix);
}

void	extract_rotation_values(t_cylinder_rotation *data, t_vector axis_v)
{
	data->axis = normalize(cross_product(data->base, axis_v));
	data->angle = acos(data->cos_angle);
	data->c = cos(data->angle);
	data->s = sin(data->angle);
	data->t = 1.0 - data->c;
	data->rot = identity_matrix();
	data->rot.matrix[0][0] = data->c + data->axis.x * data->axis.x * data->t;
	data->rot.matrix[0][1] = data->axis.x * data->axis.y * data->t
		- data->axis.z * data->s;
	data->rot.matrix[0][2] = data->axis.x * data->axis.z * data->t
		+ data->axis.y * data->s;
	data->rot.matrix[1][0] = data->axis.y * data->axis.x * data->t
		+ data->axis.z * data->s;
	data->rot.matrix[1][1] = data->c + data->axis.y * data->axis.y * data->t;
	data->rot.matrix[1][2] = data->axis.y * data->axis.z * data->t
		- data->axis.x * data->s;
	data->rot.matrix[2][0] = data->axis.z * data->axis.x * data->t
		- data->axis.y * data->s;
	data->rot.matrix[2][1] = data->axis.z * data->axis.y * data->t
		+ data->axis.x * data->s;
	data->rot.matrix[2][2] = data->c + data->axis.z * data->axis.z * data->t;
}

t_matrix	rotate_cylinder(t_vector axis_v)
{
	t_cylinder_rotation	data;

	axis_v = normalize(axis_v);
	data.base = create_vector(0, 1, 0);
	data.cos_angle = dot_product(data.base, axis_v);
	if (fabs(data.cos_angle - 1.0) < EPSILON)
		return (identity_matrix());
	if (fabs(data.cos_angle + 1.0) < EPSILON)
	{
		data.rot = identity_matrix();
		data.rot.matrix[1][1] = -1;
		data.rot.matrix[2][2] = -1;
		return (data.rot);
	}
	extract_rotation_values(&data, axis_v);
	return (data.rot);
}
