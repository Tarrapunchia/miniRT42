/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:05:35 by fzucconi          #+#    #+#             */
/*   Updated: 2025/03/25 14:05:35 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

t_camera	new_camera(float fov, t_matrix transform)
{
	t_camera	camera;
	double		half_view;
	float		aspect;

	camera.hsize = WIDTH;
	camera.vsize = HEIGHT;
	camera.fov = fov;
	camera.transform = transform;
	half_view = tan(camera.fov / 2);
	aspect = camera.hsize / camera.vsize;
	if (aspect >= 1)
	{
		camera.half_width = half_view;
		camera.half_height = half_view / aspect;
	}
	else
	{
		camera.half_width = half_view * aspect;
		camera.half_height = half_view;
	}
	camera.pixel_size = (camera.half_width * 2) / camera.hsize;
	return (camera);
}

t_ray	ray_for_pixel(t_camera camera, float x, float y)
{
	float		x_offs;
	float		y_offs;
	t_vector	pixel;
	t_vector	origin;
	t_vector	direction;

	x_offs = (x + 0.5) * camera.pixel_size;
	y_offs = (y + 0.5) * camera.pixel_size;
	x_offs = camera.half_width - x_offs;
	y_offs = camera.half_height - y_offs;
	pixel = mult_matrix_vector(matrix_inversion(camera.transform),
			create_point(x_offs, y_offs, -1));
	origin = mult_matrix_vector(matrix_inversion(camera.transform),
			create_point(0, 0, 0));
	direction = normalize(sub_vec(pixel, origin));
	return (init_ray(origin, direction));
}

void	render(t_world world, t_video *video)
{
	t_ray	ray;
	T_COLOR	color;
	float	delta;
	int		x;
	int		y;

	delta = 20;
	mlx_string_put(video->mlx, video->win,
		20, 100, 65000, "RENDERING IN PROGRESS");
	y = -1;
	while (++y < world.camera.vsize)
	{
		mlx_string_put(video->mlx, video->win, (int)delta, 150, 65000, "|");
		x = -1;
		while (++x < world.camera.hsize)
		{
			ray = ray_for_pixel(world.camera, x, y);
			color = color_at(world, ray, REFLECTIONS);
			my_mlx_pixel_put(video, x, y,
				(1 << 24
					| (int)(color.x * 255) << 16
					| (int)(color.y * 255) << 8 | (int)(color.z * 255)));
		}
		delta += ((WIDTH - 40) / 100.0f) / 3.3f;
	}
}

int	init_camera(char **words, t_world *world)
{
	char		**buf;
	t_vector	position;
	t_vector	direction;
	float		fov;

	if (world->camera.fov != -1)
		return (print_error("Too many cameras in .rt file.\n"));
	buf = ft_split(words[1], ',');
	position = create_point(ft_atof(buf[0]),
			ft_atof(buf[1]), ft_atof(buf[2]));
	ft_free_matrix(buf);
	buf = ft_split(words[2], ',');
	direction = (create_vector(ft_atof(buf[0]),
				ft_atof(buf[1]), ft_atof(buf[2])));
	ft_free_matrix(buf);
	if (!check_vector(direction, 0))
		return (print_error("Wrong camera direction.\n"));
	fov = (ft_atof(words[3]));
	if (fov <= 0 || fov >= 180)
		return (print_error("Wrong values for fov.\n"));
	fov = to_radians(fov);
	world->camera = new_camera(fov, view_transform(position,
				add_vec(position, direction),
				create_vector(0.0f, 1.0f, 0.0f)));
	return (1);
}
