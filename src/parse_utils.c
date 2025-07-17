/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-03 17:54:08 by fzucconi          #+#    #+#             */
/*   Updated: 2025-03-03 17:54:08 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "inc.h"

int	check_vector(t_vector vector, int color)
{
	if (!color)
	{
		if ((vector.x > 1.0f || vector.x < -1.0f)
			|| (vector.y > 1.0f || vector.y < -1.0f)
			|| (vector.z > 1.0f || vector.z < -1.0f))
			return (0);
	}
	else
	{
		if ((vector.x > 255.0f || vector.x < 0.0f)
			|| (vector.y > 255.0f || vector.y < 0.0f)
			|| (vector.z > 255.0f || vector.z < 0.0f))
			return (0);
	}
	return (1);
}

t_obj	set_obj(char type, void *element)
{
	t_obj	obj;

	obj.obj = element;
	obj.type = type;
	return (obj);
}
