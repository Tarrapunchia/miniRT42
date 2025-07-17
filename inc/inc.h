/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:19:52 by fzucconi          #+#    #+#             */
/*   Updated: 2025/05/07 12:40:14 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INC_H
# define INC_H
# include "mlx.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "vectors.h"

# define WIDTH 400
# define HEIGHT 400
# define EPSILON 0.0001f
# define REFLECTIONS 2
# define VACUUM 1.0f
# define WATER 1.333f
# define AIR 1.00029
# define GLASS 1.52
# define DIAMOND 2.417
# define SCALE 's'
# define TRANSLATE 't'
# define T_COLOR t_vector

typedef struct s_scene
{
	int	buf;
}	t_scene;

typedef struct s_video
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_scene	*scene;
}	t_video;

typedef struct s_matrix
{
	int		rows;
	int		cols;
	float	matrix[4][4];
}	t_matrix;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

typedef struct s_pattern
{
	t_vector	a;
	t_vector	b;
	char		type;
}	t_pattern;

typedef struct s_material
{
	t_vector	color;
	t_pattern	pattern;
	float		ambient;
	float		diffuse;
	float		specular;
	float		shininess;
	float		reflective;
	float		transparency;
	float		refractive;
}	t_material;

typedef struct s_sphere
{
	char		type;
	int			id;
	t_vector	center;
	float		radius;
	t_matrix	transform;
	t_material	material;
}	t_sphere;

typedef struct s_plane
{
	char		type;
	int			id;
	t_matrix	transform;
	t_vector	normal;
	t_material	material;
	t_vector	point;
}	t_plane;

typedef struct s_cylinder
{
	char		type;
	int			id;
	t_matrix	transform;
	t_material	material;
	t_vector	center;
	float		minimum_y;
	float		maximum_y;
	float		diameter;
	float		height;
	t_vector	dimensions;
	t_vector	direction;
	t_matrix	rotation;
	t_matrix	scaling;
	t_matrix	translation;
}	t_cylinder;

typedef struct s_cone
{
	char		type;
	int			id;
	t_matrix	transform;
	t_material	material;
	t_vector	center;
	float		minimum_y;
	float		maximum_y;
	int			is_closed;
	t_vector	dimensions;
}	t_cone;

typedef struct s_obj
{
	char		type;
	void		*obj;
	t_material	material;
}	t_obj;

typedef struct s_intersection
{
	float	t;
	char	type;
	void	*obj;
	int		id;
}	t_intersection;

typedef struct s_light
{
	t_vector	position;
	float		ratio;
	t_vector	color;
}	t_light;

typedef struct s_comps
{
	float		t;
	t_obj		obj;
	int			is_inside;
	t_vector	point;
	t_vector	eye_v;
	t_vector	normal_v;
	t_vector	over_point;
	t_vector	reflect_v;
	t_vector	under_point;
	float		n1;
	float		n2;
}	t_comps;

typedef struct s_camera
{
	float		hsize;
	float		vsize;
	float		fov;
	float		half_height;
	float		half_width;
	t_matrix	transform;
	float		pixel_size;
}	t_camera;

typedef struct s_world
{
	t_light		*lights;
	t_light		ambient;
	t_obj		*obj;
	t_camera	camera;
	int			n_obj;
	int			n_lights;
	int			flag;
}	t_world;

typedef struct s_obj_lst
{
	t_obj				*obj;
	struct s_obj_lst	*next;
}	t_obj_lst;

typedef struct s_cylinder_xs_data
{
	float		a;
	float		b;
	float		c;
	float		disc;
	float		t[2];
	float		y[2];
	int			i;
	float		buf;
	float		radius;
	float		heigth;
	t_ray		local_ray;
	t_matrix	inverse_transform;
}	t_cylinder_xs_data;

typedef struct s_cylinder_rotation
{
	t_vector	base;
	double		cos_angle;
	t_matrix	rot;
	t_vector	axis;
	double		angle;
	double		c;
	double		s;
	double		t;
}	t_cylinder_rotation;

typedef struct s_all
{
	t_video	*video;
	t_world	*world;
}	t_all;

// matrices.c
t_matrix		init_matrix(int rows, int cols, char *values);
void			print_matrix(t_matrix matrix);
int				compare_matrices(t_matrix a, t_matrix b);
t_matrix		mult_matrices(t_matrix a, t_matrix b);
t_vector		mult_matrix_vector(t_matrix matrix, t_vector vector);
t_matrix		transpose_matrix(t_matrix matrix);
t_matrix		create_submatrix(t_matrix matrix, int row, int col);
float			matrix_minor(t_matrix matrix, int row, int col);
float			matrix_determinant(t_matrix matrix);
float			matrix_cofactor(t_matrix matrix, int row, int col);
t_matrix		matrix_inversion(t_matrix matrix);
t_matrix		translation_matrix(float x, float y, float z);
t_matrix		scaling_matrix(float x, float y, float z);
t_matrix		rotation_x(float radians);
t_matrix		rotation_y(float radians);
t_matrix		rotation_z(float radians);
t_matrix		identity_matrix(void);
t_matrix		rotate_cylinder(t_vector axis_v);

// ray.c
t_ray			init_ray(t_vector origin, t_vector direction);
t_vector		ray_position(t_ray ray, float t);
t_ray			transform_ray(t_ray ray, t_matrix matrix, char type);

// sphere
void			print_sphere(t_sphere *sphere);
int				init_sphere(char **words, t_world *world, int *n_el);
t_intersection	*ray_intersect_sphere(t_intersection *instersectons,
					t_sphere *sphere, t_ray ray);
t_vector		sphere_normal_at(t_sphere *sphere, t_vector point);

// planes
t_intersection	*ray_intersect_plane(t_intersection *intersections,
					t_plane *plane, t_ray ray);
int				init_plane(char **words, t_world *world, int *n_el);
t_vector		plane_normal_at(t_plane *plane);

// cylinders
t_intersection	*ray_intersect_cylinder(t_intersection *xs,
					t_cylinder *cylinder, t_ray ray);
t_vector		cylinder_normal_at(t_cylinder *cylinder, t_vector point);
int				check_cap(t_ray ray, float t);
int				init_cylinder(char **words, t_world *world, int *n_el);

// cones
t_intersection	*ray_intersect_cone(t_intersection *xs, t_cone *cone,
					t_ray ray);
t_vector		cone_normal_at(t_cone *cone, t_vector point);
t_cone			*basic_cone(void);

// intersection
t_intersection	init_intersection(float t, char type, void *obj, int id);
t_intersection	*add_intersection(t_intersection *old_array,
					t_intersection new_intersection);
size_t			num_intersections(t_intersection *array);
void			sort_intersections(t_intersection *array, size_t size);
void			print_intersections(t_intersection *xs, char type);

// materials
t_material		sphere_base_material(void);
t_material		cylinder_base_material(void);

// pattern
T_COLOR			pattern_at_obj(t_pattern pattern, t_obj obj, t_vector point);

// light
t_light			point_light(t_vector position, t_vector intensity);
t_light			spotlight(t_vector position, float ratio, t_vector color);
t_vector		clamp_vec(t_vector vec, float min, float max);
int				init_light(char **words, t_world *world, int *n_li);
int				init_ambient_light(char **words, t_world *world);
t_vector		lighting(t_comps comps, t_light light_source, int shadowed);

// world
t_intersection	*intersect_world(t_world world, t_ray ray);
t_comps			prepare_computations(t_intersection xs, t_ray ray,
					t_intersection *xss);
t_vector		normal_at(t_obj obj, t_vector world_point);
t_vector		color_at(t_world world, t_ray ray, int remaining);
int				hit(t_intersection *xs);
t_vector		shade_hit(t_world world, t_comps comps);

// camera
t_matrix		view_transform(t_vector from, t_vector to, t_vector up);
t_camera		new_camera(float fov, t_matrix transform);
void			print_camera(t_camera camera);
t_ray			ray_for_pixel(t_camera camera, float x, float y);
void			render(t_world world, t_video *video);
int				init_camera(char **words, t_world *world);

// shadow
int				is_shadowed(t_world world, t_vector point, int n_li);

// reflection
T_COLOR			reflected_color(t_world world, t_comps comps, int remaining);

// refraction
T_COLOR			refracted_color(t_world world, t_comps comps, int remaining);

// hits
t_intersection	*ray_intersect(t_intersection *xs, t_obj obj, t_ray ray);

// utils
void			free_array(char **array);
void			my_mlx_pixel_put(t_video *data, int x, int y, int color);
t_obj			set_obj(char type, void *element);
void			obj_lst_add(t_obj_lst **lst, t_obj *to_add);
int				lst_len(t_obj_lst *lst);
t_obj			*last_lst(t_obj_lst *lst);
int				lst_contains(t_obj_lst *lst, t_obj *obj);
void			remove_from_lst(t_obj_lst **lst, t_obj *obj);
void			obj_lst_append(t_obj_lst **lst, t_obj *to_add);
float			f_max(float a, float b, float c);
float			f_min(float a, float b, float c);
double			ft_atof(const char *str);
void			exit_error(t_world *world, char **words, const char *err);
void			free_world(t_world *world);
int				print_error(char *error);

// parsing
int				parse_file(const char *file_path, t_world *world, int *li_idx,
					int *o_idx);
int				check_vector(t_vector vector, int color);

// macro_subs
t_camera		no_camera(void);
t_light			no_ambient_light(void);
float			clamp(float value, float min, float max);
t_vector		create_point(float x, float y, float z);
t_vector		create_vector(float x, float y, float z);
T_COLOR			create_color(float r, float g, float b);
char			get_object_type(t_obj *obj);
T_COLOR			black(void);
float			to_radians(float deg);

#endif
