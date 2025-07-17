/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-03 17:57:51 by fzucconi          #+#    #+#             */
/*   Updated: 2025-03-03 17:57:51 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "inc.h"
#include "libft.h"

int	init_light(char **words, t_world *world, int *n_li)
{
	char	**buf;

	if (world->n_lights > 1)
		return (print_error("Too many spotlights in .rt file.\n"));
	buf = ft_split(words[1], ',');
	world->lights[*n_li].position = create_point(
			ft_atof(buf[0]),
			ft_atof(buf[1]),
			ft_atof(buf[2])
			);
	ft_free_matrix(buf);
	world->lights[*n_li].ratio = ft_atof(words[2]);
	if (world->lights[*n_li].ratio > 1.0 || world->lights[*n_li].ratio < 0.0)
		return (print_error("Wrong value for spotlight ratio.\n"));
	buf = ft_split(words[3], ',');
	world->lights[*n_li].color = create_color(
			ft_atof(buf[0]) / 255.0f,
			ft_atof(buf[1]) / 255.0f,
			ft_atof(buf[2]) / 255.0f
			);
	ft_free_matrix(buf);
	if (!check_vector(world->lights[*n_li].color, 0))
		return (print_error("Wrong spotlight color.\n"));
	*n_li += 1;
	return (1);
}

int	init_ambient_light(char **words, t_world *world)
{
	char	**buf;

	if (world->ambient.ratio != -1)
		return (print_error("Too many ambient lights.\n"));
	world->ambient.ratio = ft_atof(words[1]);
	if (world->ambient.ratio > 1.0f || world->ambient.ratio < 0.0f)
		return (print_error("Wrong value for ambient light ratio.\n"));
	buf = ft_split(words[2], ',');
	world->ambient.color = create_color(
			ft_atof(buf[0]) / 255.0f,
			ft_atof(buf[1]) / 255.0f,
			ft_atof(buf[2]) / 255.0f
			);
	ft_free_matrix(buf);
	if (!check_vector(world->ambient.color, 0))
		return (print_error("Wrong ambient light color.\n"));
	world->ambient.position = create_point(0.0f, 0.0f, 0.0f);
	return (1);
}

t_vector	clamp_vec(t_vector vec, float min, float max)
{
	return ((t_vector){
		.x = clamp(vec.x, min, max),
		.y = clamp(vec.y, min, max),
		.z = clamp(vec.z, min, max),
		.is_point = vec.is_point
	});
}

t_vector	compute_specular(
	t_comps comps,
	t_light light_source,
	t_vector light_v
)
{
	t_vector	reflect_v;
	float		reflect_dot_eye;
	float		factor;

	reflect_v = reflect_vector(negate_vec(normalize(light_v)), comps.normal_v);
	reflect_dot_eye = dot_product(reflect_v, comps.eye_v);
	if (reflect_dot_eye < 0)
		return (black());
	else
	{
		factor = pow(reflect_dot_eye, comps.obj.material.shininess);
		return (scalar_mult_vec(light_source.color,
				comps.obj.material.specular * factor * light_source.ratio));
	}
}

t_vector	lighting(t_comps comps, t_light light_source, int shadowed)
{
	t_vector	diffuse;
	t_vector	specular;
	t_vector	effective_color;
	t_vector	light_v;
	float		light_dot_normal;

	effective_color = mul_vectors(comps.obj.material.color, light_source.color);
	light_v = normalize(sub_vec(light_source.position, comps.point));
	if (shadowed)
		return (black());
	light_dot_normal = dot_product((light_v), (comps.normal_v));
	if (light_dot_normal < 0)
	{
		diffuse = black();
		specular = black();
	}
	else
	{
		diffuse = scalar_mult_vec(effective_color,
				comps.obj.material.diffuse
				* light_source.ratio * light_dot_normal);
		specular = compute_specular(comps, light_source, light_v);
	}
	return (clamp_vec(add_vec(diffuse, specular), 0.0, 1.0));
}
// t_vector	lighting(t_comps comps, t_light light_source, int shadowed)
// {
// 	t_vector	diffuse;
// 	t_vector	specular;
// 	t_vector	effective_color;
// 	t_vector	light_v;
// 	float		light_dot_normal;

// 	if (get_object_type(&(comps.obj)) == 'S')

// 	effective_color = mul_vectors(comps.obj.material.color, light_source.color);
// 	light_v = normalize(sub_vec(light_source.position, comps.point));
// 	if (shadowed)
// 		return (black());
// 	light_dot_normal = dot_product((light_v), (comps.normal_v));
// 	if (light_dot_normal < 0)
// 	{
// 		diffuse = black();
// 		specular = black();
// 	}
// 	else
// 	{
// 		diffuse = scalar_mult_vec(effective_color,
// 				comps.obj.material.diffuse
// 				* light_source.ratio * light_dot_normal);
// 		t_vector reflect_v = reflect_vector(negate_vec(normalize(light_v)), comps.normal_v);
//         float reflect_dot_eye = dot_product(reflect_v, comps.eye_v);
        
//         if (reflect_dot_eye < 0)
//             specular = black();
//         else {
//             // float factor = pow(reflect_dot_eye, comps.obj.material.shininess);
// 		specular = compute_specular(comps, light_source, light_v);}
// 	}
// 	return (clamp_vec(add_vec(diffuse, specular), 0.0, 1.0));
// }