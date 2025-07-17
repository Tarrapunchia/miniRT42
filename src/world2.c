/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:48:35 by fzucconi          #+#    #+#             */
/*   Updated: 2025/05/07 12:17:36 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

int	hit(t_intersection *xs)
{
	int	n_xs;
	int	i;

	n_xs = num_intersections(xs);
	i = -1;
	while (++i < n_xs)
	{
		if (xs[i].t >= 0)
			return (i);
	}
	return (-1);
}

t_vector	color_at(t_world world, t_ray ray, int remaining)
{
	t_intersection	*xs;
	t_comps			comps;
	t_vector		color;

	remaining = remaining;
	xs = intersect_world(world, ray);
	if (!xs)
		return (black());
	comps = prepare_computations(xs[0], ray, xs);
	free(xs);
	color = shade_hit(world, comps);
	color = clamp_vec(color, 0.0f, 1.0f);
	return (color);
}

void	fill_matrix(t_matrix *matrix, t_matrix src)
{
	int	i;
	int	j;

	matrix->rows = src.rows;
	matrix->cols = src.cols;
	i = -1;
	while (++i < matrix->rows)
	{
		j = -1;
		while (++j < matrix->cols)
		{
			matrix->matrix[i][j] = src.matrix[i][j];
		}
	}
}

t_matrix	view_transform(t_vector from, t_vector to, t_vector up)
{
	t_vector	forward;
	t_vector	upn;
	t_vector	left;
	t_vector	true_up;
	t_matrix	orientation;

	forward = normalize(sub_vec(to, from));
	upn = normalize(up);
	left = cross_product(forward, upn);
	true_up = cross_product(left, forward);
	fill_matrix(&orientation, (t_matrix){
		4,
		4, {
	{left.x, left.y, left.z, 0},
	{true_up.x, true_up.y, true_up.z, 0},
	{-forward.x, -forward.y, -forward.z, 0},
	{0, 0, 0, 1}}
	});
	return (
		mult_matrices(
			orientation, translation_matrix(-from.x, -from.y, -from.z)
		)
	);
}

int	print_error(char *error)
{
	return (ft_putstr_fd(error, 2), 0);
}
