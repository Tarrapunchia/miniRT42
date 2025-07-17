/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro_subs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-09 15:29:16 by fzucconi          #+#    #+#             */
/*   Updated: 2025-04-09 15:29:16 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "inc.h"

t_vector	create_point(float x, float y, float z)
{
	t_vector	point;

	point.is_point = 1;
	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_vector	create_vector(float x, float y, float z)
{
	t_vector	vector;

	vector.is_point = 0;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

T_COLOR	create_color(float r, float g, float b)
{
	T_COLOR	color;

	color.is_point = 0;
	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

char	get_object_type(t_obj *obj)
{
	return (obj->type);
}

T_COLOR	black(void)
{
	return (create_color(0, 0, 0));
}
