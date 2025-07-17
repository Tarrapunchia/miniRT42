/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:56:42 by fzucconi          #+#    #+#             */
/*   Updated: 2025/04/14 15:58:53 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vector	reflect_vector(t_vector in, t_vector normal)
{
	float	dot;

	dot = dot_product(in, normal);
	normal = scalar_mult_vec(normal, 2.0f * dot);
	return (normalize(sub_vec(in, normal)));
}
