/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:38:43 by fzucconi          #+#    #+#             */
/*   Updated: 2025/04/08 15:09:53 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

t_matrix	matrix_inversion(t_matrix matrix)
{
	t_matrix	inverted;
	float		cofactor;
	float		determinant;
	int			row;
	int			col;

	determinant = matrix_determinant(matrix);
	if (determinant == 0)
		return ((t_matrix){0});
	row = -1;
	inverted = init_matrix(matrix.rows, matrix.cols, "Z");
	while (++row < matrix.rows)
	{
		col = -1;
		while (++col < matrix.cols)
		{
			cofactor = matrix_cofactor(matrix, row, col);
			inverted.matrix[col][row] = cofactor / determinant;
		}
	}
	return (inverted);
}

t_matrix	identity_matrix(void)
{
	t_matrix	matrix;

	matrix = init_matrix(4, 4, "Z");
	matrix.matrix[0][0] = 1;
	matrix.matrix[1][1] = 1;
	matrix.matrix[2][2] = 1;
	matrix.matrix[3][3] = 1;
	return (matrix);
}

t_matrix	translation_matrix(float x, float y, float z)
{
	t_matrix	matrix;

	matrix = identity_matrix();
	matrix.matrix[0][3] = x;
	matrix.matrix[1][3] = y;
	matrix.matrix[2][3] = z;
	return (matrix);
}

t_matrix	scaling_matrix(float x, float y, float z)
{
	t_matrix	matrix;

	matrix = identity_matrix();
	matrix.matrix[0][0] = x;
	matrix.matrix[1][1] = y;
	matrix.matrix[2][2] = z;
	return (matrix);
}

t_matrix	rotation_x(float radians)
{
	t_matrix	matrix;

	matrix = identity_matrix();
	matrix.matrix[1][1] = cos(radians);
	matrix.matrix[1][2] = -sin(radians);
	matrix.matrix[2][1] = sin(radians);
	matrix.matrix[2][2] = cos(radians);
	return (matrix);
}
