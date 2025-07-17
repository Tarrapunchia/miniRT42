/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:07:33 by fzucconi          #+#    #+#             */
/*   Updated: 2025/05/07 12:20:44 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

int	set_trasform(char **words, char **buf, t_sphere *sphere)
{
	float	radius;

	buf = ft_split(words[1], ',');
	sphere->center = create_vector(0, 0, 0);
	sphere->transform = translation_matrix(
			ft_atof(buf[0]),
			ft_atof(buf[1]),
			ft_atof(buf[2])
			);
	sphere->radius = 1.0f;
	radius = ft_atof(words[2]) / 2;
	if (radius < 0)
		return (free(sphere), ft_free_matrix(buf),
			print_error("Error in sphere radius.\n"));
	sphere->transform = mult_matrices(sphere->transform, scaling_matrix(
				radius,
				radius,
				radius
				));
	ft_free_matrix(buf);
	return (1);
}

int	init_sphere(char **words, t_world *world, int *n_el)
{
	t_sphere	*sphere;
	char		**buf;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
	sphere->type = 'S';
	sphere->id = *n_el;
	buf = NULL;
	if (set_trasform(words, buf, sphere) == 0)
		return (0);
	buf = ft_split(words[3], ',');
	sphere->material = sphere_base_material();
	sphere->material.color = create_color(
			(float)(ft_atof(buf[0]) / 255),
			(float)(ft_atof(buf[1]) / 255),
			(float)(ft_atof(buf[2]) / 255)
			);
	ft_free_matrix(buf);
	if (!check_vector(sphere->material.color, 0))
		return (free(sphere), print_error("Error in sphere color\n"));
	world->obj[*n_el] = set_obj('S', (void *)sphere);
	*n_el += 1;
	return (1);
}

void	populate_xss(t_intersection **xss, t_sphere *sphere, float buf)
{
	if (buf > 0)
		*xss = add_intersection(*xss,
				init_intersection(buf, 'S', sphere, sphere->id));
}

t_intersection	*ray_intersect_sphere(t_intersection *intersections,
	t_sphere *sphere, t_ray ray)
{
	float		a;
	float		b;
	float		c;
	float		buf;
	t_vector	obj_to_ray;

	ray.direction = mult_matrix_vector(matrix_inversion(
				sphere->transform), ray.direction);
	ray.origin = mult_matrix_vector(matrix_inversion(
				sphere->transform), ray.origin);
	obj_to_ray = sub_vec(ray.origin, create_point(0, 0, 0));
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, obj_to_ray);
	c = dot_product(obj_to_ray, obj_to_ray) - 1;
	c = b * b - 4 * a * c;
	if (c < 0)
		return (intersections);
	buf = ((-b - sqrt(c)) / (2 * a));
	populate_xss(&intersections, sphere, buf);
	buf = ((-b + sqrt(c)) / (2 * a));
	populate_xss(&intersections, sphere, buf);
	return (intersections);
}

t_vector	sphere_normal_at(t_sphere *sphere, t_vector world_point)
{
	t_vector	world_normal;
	t_vector	obj_normal;
	t_vector	obj_point;

	obj_point = mult_matrix_vector(
			matrix_inversion(sphere->transform), world_point
			);
	obj_normal = sub_vec(obj_point, (t_vector){0, 0, 0, 0});
	world_normal = mult_matrix_vector(
			transpose_matrix(
				matrix_inversion(sphere->transform)),
			obj_normal
			);
	world_normal.is_point = 0;
	return (normalize(world_normal));
}
