/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:38:09 by fzucconi          #+#    #+#             */
/*   Updated: 2025/04/08 15:01:00 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

t_matrix	transpose_matrix(t_matrix matrix)
{
	t_matrix	transposed;
	int			i;
	int			j;

	i = -1;
	transposed = init_matrix(matrix.rows, matrix.cols, "Z");
	while (++i < matrix.rows)
	{
		j = -1;
		while (++j < matrix.cols)
		{
			transposed.matrix[j][i] = matrix.matrix[i][j];
		}
	}
	return (transposed);
}

t_matrix	create_submatrix(t_matrix matrix, int row, int col)
{
	t_matrix	submatrix;
	int			i;
	int			j;
	int			sub_row;
	int			sub_col;

	i = -1;
	submatrix = init_matrix(matrix.rows - 1, matrix.cols - 1, "Z");
	while (++i < matrix.rows)
	{
		j = -1;
		while (++j < matrix.cols)
		{
			if (i >= row)
				sub_row = i + 1;
			else
				sub_row = i;
			if (j >= col)
				sub_col = j + 1;
			else
				sub_col = j;
			submatrix.matrix[i][j] = matrix.matrix[sub_row][sub_col];
		}
	}
	return (submatrix);
}

float	matrix_determinant(t_matrix matrix)
{
	float	determinant;
	int		i;

	i = -1;
	determinant = 0;
	if (matrix.cols == 2)
	{
		determinant = matrix.matrix[0][0] * matrix.matrix[1][1]
			- matrix.matrix[0][1] * matrix.matrix[1][0];
	}
	else
	{
		while (++i < matrix.cols)
		{
			determinant += matrix.matrix[0][i] * matrix_cofactor(matrix, 0, i);
		}
	}
	return (determinant);
}

float	matrix_minor(t_matrix matrix, int row, int col)
{
	t_matrix	sub;
	float		determinant;

	sub = create_submatrix(matrix, row, col);
	determinant = matrix_determinant(sub);
	return (determinant);
}

float	matrix_cofactor(t_matrix matrix, int row, int col)
{
	float	cofactor;

	cofactor = matrix_minor(matrix, row, col);
	if ((row + col) % 2 != 0)
		cofactor *= -1;
	return (cofactor);
}
