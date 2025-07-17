/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:20:33 by fzucconi          #+#    #+#             */
/*   Updated: 2025/05/07 12:13:16 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

void	set_plane(char **words, int *n_el, t_plane *plane, char **buf)
{
	plane->material = sphere_base_material();
	plane->transform = identity_matrix();
	plane->type = 'P';
	plane->id = *n_el;
	buf = ft_split(words[1], ',');
	plane->point = create_vector(
			ft_atof(buf[0]),
			ft_atof(buf[1]),
			ft_atof(buf[2])
			);
	ft_free_matrix(buf);
	buf = ft_split(words[2], ',');
	plane->normal = normalize(create_vector(
				ft_atof(buf[0]),
				ft_atof(buf[1]),
				ft_atof(buf[2]))
			);
	ft_free_matrix(buf);
}

int	init_plane(char **words, t_world *world, int *n_el)
{
	t_plane	*plane;
	char	**buf;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (print_error("Error in allocating Plane.\n"));
	buf = NULL;
	set_plane(words, n_el, plane, buf);
	buf = ft_split(words[3], ',');
	plane->material = sphere_base_material();
	plane->material.color = create_color(
			(float)(ft_atof(buf[0]) / 255),
			(float)(ft_atof(buf[1]) / 255),
			(float)(ft_atof(buf[2]) / 255)
			);
	ft_free_matrix(buf);
	if (!check_vector(plane->material.color, 0))
		return (free(plane), print_error("Error in Plane color.\n"));
	world->obj[*n_el] = set_obj('P', (void *)plane);
	*n_el += 1;
	return (1);
}

t_intersection	*ray_intersect_plane(t_intersection *intersections,
	t_plane *plane, t_ray ray)
{
	float	t;
	float	denom;

	denom = dot_product(plane->normal, ray.direction);
	if (fabs(denom) < -EPSILON)
		return (intersections);
	if (fabs(ray.direction.y) < EPSILON)
		return (intersections);
	t = dot_product(sub_vec(plane->point, ray.origin), plane->normal)
		/ denom;
	if (t > 0)
		intersections = add_intersection(intersections,
				init_intersection(t,
					'P', plane, plane->id));
	return (intersections);
}

t_vector	plane_normal_at(t_plane *plane)
{
	t_vector	normal;

	if (compare_matrices(identity_matrix(), plane->transform))
		return (normalize(plane->normal));
	normal = plane->normal;
	normal = mult_matrix_vector(transpose_matrix(
				matrix_inversion(plane->transform)), normal);
	return (normalize(negate_vec(normal)));
}
