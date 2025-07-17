/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro_subs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-09 15:29:08 by fzucconi          #+#    #+#             */
/*   Updated: 2025-04-09 15:29:08 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "inc.h"

t_camera	no_camera(void)
{
	return ((t_camera){
		0,
		0,
		-1,
		0,
		0,
		identity_matrix(),
		0
	});
}

t_light	no_ambient_light(void)
{
	return ((t_light){
		create_point(0, 0, 0),
		-1,
		create_vector(0, 0, 0)
	});
}

float	clamp(float value, float min, float max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	return (value);
}

float	to_radians(float deg)
{
	return ((deg / 180) * M_PI);
}
