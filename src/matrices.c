/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:37:38 by fzucconi          #+#    #+#             */
/*   Updated: 2025/04/08 14:55:37 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

void	init_empty_matrix(int rows, int cols, t_matrix *matrix)
{
	int	i;
	int	j;

	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
			matrix->matrix[i][j] = 0;
	}
}

t_matrix	init_matrix(int rows, int cols, char *values)
{
	t_matrix	matrix;
	char		**single_values;
	int			i;
	int			j;

	i = -1;
	if (values[0] == 'Z')
		init_empty_matrix(rows, cols, &matrix);
	else
	{
		single_values = ft_split(values, ',');
		if (!single_values)
			return ((t_matrix){0});
		while (++i < rows)
		{
			j = -1;
			while (++j < cols)
				matrix.matrix[i][j] = atof(single_values[(i * cols) + j]);
		}
	}
	matrix.cols = cols;
	matrix.rows = rows;
	return (matrix);
}

int	compare_matrices(t_matrix a, t_matrix b)
{
	int	i;
	int	j;

	i = -1;
	if (a.cols != b.cols || a.rows != b.rows)
		return (0);
	while (++i < a.rows)
	{
		j = -1;
		while (++j < a.cols)
		{
			if (fabs(a.matrix[i][j] - b.matrix[i][j]) > EPSILON)
				return (0);
		}
	}
	return (1);
}

t_matrix	mult_matrices(t_matrix a, t_matrix b)
{
	int			i;
	int			j;
	int			size;
	t_matrix	matrix;

	i = -1;
	if (a.cols != b.cols || a.rows != b.rows)
		return ((t_matrix){0});
	matrix = init_matrix(a.rows, a.cols, "Z");
	while (++i < a.rows)
	{
		j = -1;
		while (++j < a.cols)
		{
			matrix.matrix[i][j] = 0;
			size = -1;
			while (++size < a.cols)
			{
				matrix.matrix[i][j] += a.matrix[i][size] * b.matrix[size][j];
			}
		}
	}
	return (matrix);
}

t_vector	mult_matrix_vector(t_matrix matrix, t_vector vector)
{
	t_vector	return_vec;

	return_vec.x = matrix.matrix[0][0] * vector.x
		+ matrix.matrix[0][1] * vector.y
		+ matrix.matrix[0][2] * vector.z
		+ matrix.matrix[0][3] * vector.is_point;
	return_vec.y = matrix.matrix[1][0] * vector.x
		+ matrix.matrix[1][1] * vector.y
		+ matrix.matrix[1][2] * vector.z
		+ matrix.matrix[1][3] * vector.is_point;
	return_vec.z = matrix.matrix[2][0] * vector.x
		+ matrix.matrix[2][1] * vector.y
		+ matrix.matrix[2][2] * vector.z
		+ matrix.matrix[2][3] * vector.is_point;
	return_vec.is_point = matrix.matrix[3][0] * vector.x
		+ matrix.matrix[3][1] * vector.y
		+ matrix.matrix[3][2] * vector.z
		+ matrix.matrix[3][3] * vector.is_point;
	return (return_vec);
}
