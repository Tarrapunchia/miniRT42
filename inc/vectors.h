/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:57:09 by fzucconi          #+#    #+#             */
/*   Updated: 2025/05/07 12:39:37 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <math.h>

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
	int		is_point;
}	t_vector;

t_vector		add_vec(t_vector a, t_vector b);
t_vector		sub_vec(t_vector a, t_vector b);
t_vector		mul_vectors(t_vector a, t_vector b);
t_vector		negate_vec(t_vector a);
t_vector		scalar_mult_vec(t_vector a, float b);
t_vector		scalar_div_vec(t_vector a, float b);
float			magnitude_vec(t_vector a);
t_vector		normalize(t_vector a);
float			dot_product(t_vector a, t_vector b);
t_vector		cross_product(t_vector a, t_vector b);
t_vector		reflect_vector(t_vector in, t_vector normal);
void			print_vector(t_vector vector, char *name);

#endif