/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:20:01 by fzucconi          #+#    #+#             */
/*   Updated: 2025/04/08 14:30:17 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

t_intersection	init_intersection(float t, char type, void *obj, int id)
{
	t_intersection	intersection;

	intersection.id = id;
	intersection.t = t;
	intersection.type = type;
	intersection.obj = obj;
	return (intersection);
}

size_t	num_intersections(t_intersection *array)
{
	size_t	size;

	size = 0;
	if (array)
		while ((array + size) && (array[size].id != -1))
			size++;
	return (size);
}

void	sort_intersections(t_intersection *array, size_t size)
{
	size_t			i;
	size_t			j;
	t_intersection	key;

	i = 1;
	while (++i < size)
	{
		key = array[i];
		j = i;
		while (j > 0 && array[j - 1].t > key.t)
		{
			array[j] = array[j - 1];
			j--;
		}
		array[j] = key;
	}
}

t_intersection	*add_intersection(t_intersection *old_array,
	t_intersection new_intersection)
{
	t_intersection	*new_array;
	size_t			size;
	size_t			i;

	size = num_intersections(old_array);
	i = 0;
	new_array = malloc(sizeof(t_intersection) * (size + 2));
	while (i < size)
	{
		new_array[i] = old_array[i];
		i++;
	}
	new_array[size] = new_intersection;
	new_array[size + 1] = (t_intersection){-1, -1, NULL, -1};
	free(old_array);
	old_array = NULL;
	return (new_array);
}
