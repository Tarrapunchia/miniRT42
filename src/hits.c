/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:19:42 by fzucconi          #+#    #+#             */
/*   Updated: 2025/04/14 16:04:41 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

t_intersection	*ray_intersect(t_intersection *xs, t_obj obj, t_ray ray)
{
	if (obj.type == 'S')
		return (ray_intersect_sphere(xs, (t_sphere *)(obj.obj), ray));
	if (obj.type == 'P')
		return (ray_intersect_plane(xs, (t_plane *)(obj.obj), ray));
	if (obj.type == 'C')
		return (ray_intersect_cylinder(xs, (t_cylinder *)(obj.obj), ray));
	return (xs);
}
