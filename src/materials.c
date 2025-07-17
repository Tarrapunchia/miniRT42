/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:20:14 by fzucconi          #+#    #+#             */
/*   Updated: 2025/04/08 14:32:41 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

t_material	sphere_base_material( void )
{
	return ((t_material){
		(T_COLOR){1.0f, 1.0f, 1.0f, 0},
		(t_pattern){create_color(0.0f, 0.0f, 0.0f),
			create_color(1.0f, 1.0f, 1.0f), 'Z'},
		0.4, // amb
		0.9, // diffuse
		0.4, // specular
		10, // shininess
		0.4f, // refl
		0.0f,
		1.0f
	});
}

t_material	cylinder_base_material( void )
{
	return ((t_material){
		(T_COLOR){1.0f, 1.0f, 1.0f, 0},
		(t_pattern){create_color(0.0f, 0.0f, 0.0f),
			create_color(1.0f, 1.0f, 1.0f), 'Z'},
		0.4, // amb
		0.2, // diffuse
		0.4, // specular
		2.0, // shininess
		0.1f, // refl
		0.0f,
		1.0f
	});
}