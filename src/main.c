/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzucconi <fzucconi@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:20:09 by fzucconi          #+#    #+#             */
/*   Updated: 2025/05/07 12:26:51 by fzucconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

void	video_init(t_video *video, char *title, t_scene *scene)
{
	video->mlx = mlx_init();
	video->win = mlx_new_window(video->mlx, WIDTH, HEIGHT, title);
	video->img = mlx_new_image(video->mlx, WIDTH, HEIGHT);
	video->addr = mlx_get_data_addr(video->img, &video->bits_per_pixel,
			&video->line_length, &video->endian);
	video->scene = scene;
}

int	killall_free(int keycode, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (keycode == 65307)
	{
		printf("ESC pressed!\n");
		printf("Killing all processes...\n");
		mlx_destroy_image(all->video->mlx, all->video->img);
		mlx_destroy_window(all->video->mlx, all->video->win);
		mlx_destroy_display(all->video->mlx);
		free(all->video->mlx);
		printf("Memory Cleared.\nExiting...\n");
		free_world(all->world);
		exit(0);
	}
	return (0);
}

void	my_mlx_pixel_put(t_video *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_control_values(int *li, int *ob, t_world *world)
{
	*li = 0;
	*ob = 0;
	world->n_lights = 0;
	world->n_obj = 0;
	world->ambient = no_ambient_light();
	world->camera = no_camera();
	world->flag = 1;
}

int	main(int argc, char const *argv[])
{
	t_video	video;
	t_world	world;
	int		obj_idx;
	int		light_idx;
	t_all	all;

	if (argc != 2)
		exit_error(NULL, NULL, "No Scene (*.rt) file passed.\nExiting.\n");
	init_control_values(&light_idx, &obj_idx, &world);
	if (!parse_file(argv[1], &world, &light_idx, &obj_idx))
		exit_error(NULL, NULL, "Error while parsing the file.\n");
	video_init(&video, "MINIRT", NULL);
	all.video = &video;
	all.world = &world;
	render(world, &video);
	printf("ENDED RENDERING/n");
	mlx_put_image_to_window(video.mlx, video.win, video.img, 0, 0);
	mlx_hook(video.win, 2, 1L << 0, killall_free, &all);
	mlx_loop(video.mlx);
	return (0);
}
