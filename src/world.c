/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:32:03 by fzucconi          #+#    #+#             */
/*   Updated: 2025/04/14 15:32:03 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

t_vector	normal_at(t_obj obj, t_vector world_point)
{
	if (obj.type == 'S')
		return (sphere_normal_at((t_sphere *)(obj.obj), world_point));
	else if (obj.type == 'P')
		return (plane_normal_at((t_plane *)(obj.obj)));
	else if (obj.type == 'C')
		return (cylinder_normal_at((t_cylinder *)(obj.obj), world_point));
	else
		return (create_vector(-1, -1, -1));
}

t_material	set_type(t_intersection xs, t_comps comps)
{
	if (comps.obj.type == 'P')
		return (((t_plane *)(xs.obj))->material);
	else if (comps.obj.type == 'S')
		return (((t_sphere *)(xs.obj))->material);
	else if (comps.obj.type == 'C')
		return (((t_cylinder *)(xs.obj))->material);
	else
		return (sphere_base_material());
}

t_comps	prepare_computations(t_intersection xs, t_ray ray, t_intersection *xss)
{
	t_comps	comps;
	float	dot;

	comps.t = xs.t;
	comps.obj.obj = xs.obj;
	comps.obj.type = xs.type;
	xss = xss;
	comps.point = ray_position(ray, comps.t);
	comps.eye_v = normalize(scalar_mult_vec(ray.direction, -1));
	comps.normal_v = normalize(normal_at(comps.obj, comps.point));
	if (dot_product(comps.normal_v, comps.eye_v) < 0)
	{
		comps.is_inside = 1;
		comps.normal_v = normalize(scalar_mult_vec(comps.normal_v, -1));
	}
	else
		comps.is_inside = 0;
	dot = dot_product(ray.direction, comps.normal_v);
	comps.reflect_v = normalize(sub_vec((ray.direction),
				(scalar_mult_vec(comps.normal_v, 2 * dot))));
	comps.obj.material = set_type(xs, comps);
	comps.over_point = add_vec(comps.point,
			scalar_mult_vec(comps.normal_v, EPSILON));
	return (comps);
}

t_vector	shade_hit(t_world world, t_comps comps)
{
	T_COLOR	surface;
	T_COLOR	ambient;
	int		shadowed;
	int		i;

	if (comps.obj.type == 'S')
		comps.obj.material = ((t_sphere *)(comps.obj.obj))->material;
	else if (comps.obj.type == 'P')
		comps.obj.material = ((t_plane *)(comps.obj.obj))->material;
	else if (comps.obj.type == 'C')
		comps.obj.material = ((t_cylinder *)(comps.obj.obj))->material;
	surface = black();
	ambient = scalar_mult_vec(mul_vectors(comps.obj.material.color,
				world.ambient.color), world.ambient.ratio);
	surface = add_vec(surface, ambient);
	i = -1;
	while (++i < world.n_lights)
	{
		shadowed = is_shadowed(world, comps.over_point, i);
		if (comps.obj.type == 'C')
			shadowed = !shadowed;
		surface = add_vec(surface, lighting(comps,
					world.lights[i], shadowed));
	}
	return (clamp_vec(surface, 0.0, 1.0));
}

t_intersection	*intersect_world(t_world world, t_ray ray)
{
	int				i;
	t_intersection	*xs;

	i = 0;
	xs = NULL;
	while (i < world.n_obj)
	{
		xs = ray_intersect(xs, world.obj[i], ray);
		i++;
	}
	sort_intersections(xs, num_intersections(xs));
	return (xs);
}
