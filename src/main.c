/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:35:57 by saeby             #+#    #+#             */
/*   Updated: 2022/12/17 12:31:23 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rot_cube.h"

int	main(int ac, char *av[])
{
	t_env env;
	env.color = 0xFFFFFFFF;
	env.distance = 1;
	env.scale = 100;

	if (ac == 2)
		env.distance = atof(av[1]);
	else if (ac == 3)
	{
		env.scale = atof(av[1]);
		env.distance = atof(av[2]);
	}
	else if (ac == 4)
	{
		env.color = strtol(av[1], NULL, 16);
		env.scale = atof(av[2]);
		env.distance = atof(av[3]);
	}
	init(&env);
	create_cube(&env);

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_W, WIN_H, "rot_cube");
	env.img = mlx_new_image(env.mlx, WIN_W, WIN_H);
	env.addr = mlx_get_data_addr(env.img, &env.bits_per_pixel, &env.line_length, &env.endian);

	mlx_hook(env.win, 4, 0, mouse_handler, &env);
	mlx_hook(env.win, 2, 1L << 0, key_handler, &env);
	mlx_hook(env.win, 17, 1L << 0, close_window, &env);
	
	mlx_loop_hook(env.mlx, render, &env);
	mlx_loop(env.mlx);
	return (0);
}

int	render(t_env *env)
{
	update_rotation_matrices(env);
	draw_background(env, (t_vector2){0, 0}, (t_vector2){1280, 720});

	for (int i = 0; i < 8; i++)
	{
		env->points_matrices[i] = ft_vec_to_matrix(env->points[i]);
		env->rotated[i] = ft_matmul(env->rotationX, env->points_matrices[i], &(t_vector3){3, 3, 1});
		env->rotated[i] = ft_matmul(env->rotationY, env->rotated[i], &(t_vector3){3, 3, 1});
		env->rotated[i] = ft_matmul(env->rotationZ, env->rotated[i], &(t_vector3){3, 3, 1});
		float	z = 1 / (env->distance - env->rotated[i][2][0]);
		env->p[0][0] = z;
		env->p[0][1] = 0;
		env->p[0][2] = 0;
		
		env->p[1][0] = 0;
		env->p[1][1] = z;
		env->p[1][2] = 0;
		env->projected[i] = ft_matmul(env->p, env->rotated[i], &(t_vector3){2, 3, 1});
		env->final_points[i] = ft_matrix_to_vec2(env->projected[i]);
		ft_scale_vector2(&env->final_points[i], env->scale);
		ft_translate_center(&env->final_points[i]);
	}

	// draw lines
	for (int i = 0; i < 4; i++)
	{
		connect(env, i, (i + 1) % 4, env->final_points);
		connect(env, i + 4, ((i + 1) % 4) + 4, env->final_points);
		connect(env, i, i + 4, env->final_points);
	}
	
	env->angle += env->angle_update;
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}

void	draw_background(t_env *env, t_vector2 s, t_vector2 e)
{
	int	i;
	i = s.x;
	while (s.y <= e.y)
	{
		while (i <= e.x)
		{
			put_mlx_pixel(env, (t_vector2){i, s.y}, 0x000000);
			i++;
		}
		i = s.x;
		s.y++;
	}
}

void	draw_line(t_env *env, t_vector2 s, t_vector2 e, int col)
{
	float	delta_x, delta_y, step, x, y;
	int		i;

	delta_x = e.x - s.x;
	delta_y = e.y - s.y;

	if (fabsf(delta_x) >= fabsf(delta_y))
		step = fabsf(delta_x);
	else
		step = fabsf(delta_y);

	delta_x = delta_x / step;
	delta_y = delta_y / step;

	x = s.x;
	y = s.y;
	i = 0;
	while (i < step)
	{
		put_mlx_pixel(env, (t_vector2){x, y}, col);
		x = x + delta_x;
		y = y + delta_y;
		i++;
	}
}
