/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-03 17:27:45 by fzucconi          #+#    #+#             */
/*   Updated: 2025-03-03 17:27:45 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "inc.h"
#include "libft.h"
#include <stdlib.h>

int	check_file(const char *file_path)
{
	int		fd;
	char	*ext_file;

	ext_file = ft_strrchr(file_path, '.');
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		exit_error(NULL, NULL, "Error in reading .rt file\n");
	if (ft_strncmp(ext_file, ".rt\0", 4) != 0)
	{
		close(fd);
		exit_error(NULL, NULL, "Error: Wrong file format\n");
	}
	return (fd);
}

int	get_element_number(const char *file_path, char type)
{
	int			elements;
	char		*buf;
	char		**words;
	int			fd;

	fd = check_file(file_path);
	if (fd < 0)
		exit(-1);
	elements = 0;
	buf = ft_get_next_line(fd);
	while (buf)
	{
		words = ft_split(buf, ' ');
		if ((ft_strncmp(words[0], "sp\0", 3) == 0
				|| ft_strncmp(words[0], "pl\0", 3) == 0
				|| ft_strncmp(words[0], "cy\0", 3) == 0) && type != 'L')
			elements++;
		else if (ft_strncmp(words[0], "L\0", 2) == 0 && type == 'L')
			elements++;
		free(buf);
		ft_free_matrix(words);
		buf = ft_get_next_line(fd);
	}
	return (close(fd), elements);
}

int	init_world(char *line, t_world *world, int *n_el, int *n_li)
{
	char	**words;
	char	*type;
	int		flag;

	flag = 1;
	words = ft_split(line, ' ');
	free(line);
	type = words[0];
	n_li = n_li;
	if (ft_strncmp(type, "sp\0", 3) == 0)
		flag = init_sphere(words, world, n_el);
	else if (ft_strncmp(type, "pl\0", 3) == 0)
		flag = init_plane(words, world, n_el);
	else if (ft_strncmp(type, "cy\0", 3) == 0)
		flag = init_cylinder(words, world, n_el);
	else if (ft_strncmp(type, "A\0", 2) == 0)
		flag = init_ambient_light(words, world);
	else if (ft_strncmp(type, "C\0", 2) == 0)
		flag = init_camera(words, world);
	else if (ft_strncmp(type, "L\0", 2) == 0)
		flag = init_light(words, world, n_li);
	else
		return (ft_free_matrix(words), 0);
	return (ft_free_matrix(words), flag);
}

int	parse_file(const char *file_path, t_world *world, int *li_idx, int *o_idx)
{
	int		fd;
	char	*buf;

	fd = check_file(file_path);
	world->n_obj = get_element_number(file_path, 'Z');
	world->n_lights = get_element_number(file_path, 'L');
	if (world->n_lights > 1)
		exit_error(NULL, NULL, "Too many spotlights declared in .rt file.\n");
	world->obj = (t_obj *)calloc((world->n_obj), sizeof(t_obj));
	if (!world->obj)
		exit_error(NULL, NULL, "Error: allocation of the obj array.");
	world->lights = (t_light *)calloc((world->n_lights), sizeof(t_light));
	if (!world->lights)
		return (exit_error(world, NULL, "Error: allocating lights array."), 0);
	buf = ft_get_next_line(fd);
	while (buf)
	{
		if (!init_world(buf, world, o_idx, li_idx))
			world->flag = 0;
		buf = ft_get_next_line(fd);
	}
	if (world->flag == 0)
		return (close(fd), free_world(world), 0);
	return (close(fd), 1);
}
