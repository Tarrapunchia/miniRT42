/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-09 15:44:51 by fzucconi          #+#    #+#             */
/*   Updated: 2025-04-09 15:44:51 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

int	is_shadowed(t_world world, t_vector point, int n_li)
{
	int				li;
	float			distance;
	t_vector		v;
	t_intersection	*xs;
	t_ray			r;

	li = n_li;
	v = sub_vec(world.lights[li].position, point);
	distance = magnitude_vec(v);
	v = normalize(v);
	r = init_ray(point, v);
	xs = intersect_world(world, r);
	li = hit(xs);
	if (li >= 0 && xs[li].t < distance && xs[li].t > EPSILON)
		return (free(xs), 1);
	else
	{
		if (xs)
			free(xs);
		return (0);
	}
}
