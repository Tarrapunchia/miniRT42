/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:46:11 by fzucconi          #+#    #+#             */
/*   Updated: 2025/03/25 14:46:11 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

int	extract_dimensions(char **words, t_cylinder *cylinder, int *n_el,
	char **buf)
{
	cylinder->type = 'C';
	cylinder->id = *n_el;
	buf = ft_split(words[1], ',');
	cylinder->dimensions.x = ft_atof(buf[0]);
	cylinder->dimensions.y = ft_atof(buf[1]);
	cylinder->dimensions.z = ft_atof(buf[2]);
	cylinder->center = create_point(0, 0, 0);
	ft_free_matrix(buf);
	buf = ft_split(words[2], ',');
	cylinder->direction.x = ft_atof(buf[0]);
	cylinder->direction.y = ft_atof(buf[1]);
	cylinder->direction.z = ft_atof(buf[2]);
	ft_free_matrix(buf);
	cylinder->diameter = ft_atof(words[3]);
	cylinder->height = ft_atof(words[4]);
	if (cylinder->diameter <= 0 || cylinder->height <= 0)
		return (0);
	cylinder->minimum_y = -(cylinder->height) / 2.0f;
	cylinder->maximum_y = (cylinder->height) / 2.0f;
	cylinder->rotation = rotate_cylinder(create_vector(cylinder->direction.x,
				cylinder->direction.y, cylinder->direction.z));
	cylinder->scaling = scaling_matrix(cylinder->diameter / 2.0f,
			1.0f, cylinder->diameter / 2.0f);
	return (1);
}

int	init_cylinder(char **words, t_world *world, int *n_el)
{
	t_cylinder	*cylinder;
	char		**buf;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (print_error("Error in allocating Cylinder.\n"));
	buf = NULL;
	if (extract_dimensions(words, cylinder, n_el, buf) == 0)
		return (free(cylinder), print_error("Error Cylinder dimensions.\n"));
	cylinder->translation = translation_matrix(cylinder->dimensions.x,
			cylinder->dimensions.y, cylinder->dimensions.z);
	cylinder->transform = mult_matrices(cylinder->translation,
			mult_matrices(cylinder->rotation, cylinder->scaling));
	buf = ft_split(words[5], ',');
	cylinder->material = cylinder_base_material();
	cylinder->material.color = create_color(
			(float)(ft_atof(buf[0]) / 255),
			(float)(ft_atof(buf[1]) / 255),
			(float)(ft_atof(buf[2]) / 255)
			);
	ft_free_matrix(buf);
	if (!check_vector(cylinder->material.color, 0))
		return (free(cylinder), print_error("Error in sphere color\n"));
	world->obj[*n_el] = set_obj('C', (void *)cylinder);
	printf("Cylinder color %f %f %f\n",	cylinder->material.color.x,cylinder->material.color.y,
cylinder->material.color.z);
	return (++(*n_el), 1);
}

t_vector	cylinder_normal_at(t_cylinder *cylinder, t_vector point)
{
	float		dist;
	t_vector	normal;
	t_vector	local_point;

	local_point = mult_matrix_vector(
			matrix_inversion(cylinder->transform), point);
	dist = (local_point.x * local_point.x) + (local_point.z * local_point.z);
	if (dist < 1 && local_point.y >= (cylinder->maximum_y - EPSILON))
		normal = ((create_vector(0, 1.0f, 0)));
	else if (dist < 1 && local_point.y <= (cylinder->minimum_y + EPSILON))
		normal = ((create_vector(0, -1.0f, 0)));
	else
		normal = ((create_vector(local_point.x, 0, local_point.z)));
	return (normalize(mult_matrix_vector(transpose_matrix(
					matrix_inversion(cylinder->transform)),
				normal)));
}

void	intersect_helper(t_cylinder_xs_data *data, t_cylinder *cylinder,
	t_intersection **xs)
{
	float	temp;

	data->t[0] = (-data->b - sqrtf(data->disc)) / (2.0f * data->a);
	data->t[1] = (-data->b + sqrtf(data->disc)) / (2.0f * data->a);
	if (data->t[0] > data->t[1])
	{
		temp = data->t[0];
		data->t[0] = data->t[1];
		data->t[1] = temp;
	}
	data->y[0] = data->local_ray.origin.y + data->t[0]
		* data->local_ray.direction.y;
	if (cylinder->minimum_y <= data->y[0]
		&& data->y[0] <= cylinder->maximum_y)
		*xs = add_intersection(*xs,
				init_intersection(
					data->t[0], 'C', cylinder, cylinder->id));
	data->y[1] = data->local_ray.origin.y + data->t[1]
		* data->local_ray.direction.y;
	if (cylinder->minimum_y <= data->y[1] && data->y[1] <= cylinder->maximum_y)
		*xs = add_intersection(*xs,
				init_intersection(
					data->t[1], 'C', cylinder, cylinder->id));
}

t_intersection	*ray_intersect_cylinder(t_intersection *xs,
	t_cylinder *cylinder, t_ray ray)
{
	t_cylinder_xs_data	data;

	data.inverse_transform = matrix_inversion(cylinder->transform);
	data.local_ray.origin = mult_matrix_vector(data.inverse_transform,
			ray.origin);
	data.local_ray.direction = mult_matrix_vector(data.inverse_transform,
			ray.direction);
	data.a = (data.local_ray.direction.x * data.local_ray.direction.x)
		+ (data.local_ray.direction.z * data.local_ray.direction.z);
	if (fabs(data.a) >= EPSILON)
	{
		data.b = (2 * data.local_ray.origin.x * data.local_ray.direction.x
				+ 2 * data.local_ray.origin.z * data.local_ray.direction.z);
		data.c = (data.local_ray.origin.x * data.local_ray.origin.x)
			+ (data.local_ray.origin.z * data.local_ray.origin.z) - 1.0f;
		data.disc = (data.b * data.b) - (4 * data.a * data.c);
		if (data.disc < 0)
			return (xs);
		intersect_helper(&data, cylinder, &xs);
	}
	return (xs);
}
