/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:35:57 by saeby             #+#    #+#             */
/*   Updated: 2022/12/15 16:59:47 by saeby            ###   ########.fr       */
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

	env.angle = 0;
	env.angle_update = 0.01;
	env.points = malloc(8 * sizeof(t_vector3));
	env.points_matrices = malloc(8 * sizeof(float **));
	env.rotated = malloc(8 * sizeof(float **));
	env.projected = malloc(8 * sizeof(float **));
	env.final_points = malloc(8 * sizeof(t_vector2));

	t_vector2 pm_v = {2, 3};
	env.p = ft_create_matrix(&pm_v);

	t_vector2 ro_m_v = {3, 3};
	env.rotationZ = ft_create_matrix(&ro_m_v);
	env.rotationY = ft_create_matrix(&ro_m_v);
	env.rotationX = ft_create_matrix(&ro_m_v);

	env.points[0] = (t_vector3){-0.5, -0.5, -0.5};
	env.points[1] = (t_vector3){0.5, -0.5, -0.5};
	env.points[2] = (t_vector3){0.5, 0.5, -0.5};
	env.points[3] = (t_vector3){-0.5, 0.5, -0.5};

	env.points[4] = (t_vector3){-0.5, -0.5, 0.5};
	env.points[5] = (t_vector3){0.5, -0.5, 0.5};
	env.points[6] = (t_vector3){0.5, 0.5, 0.5};
	env.points[7] = (t_vector3){-0.5, 0.5, 0.5};

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_W, WIN_H, "rot_cube");
	env.img = mlx_new_image(env.mlx, WIN_W, WIN_H);
	env.addr = mlx_get_data_addr(env.img, &env.bits_per_pixel, &env.line_length, &env.endian);

	mlx_hook(env.win, 2, 1L << 0, key_handler, &env);
	mlx_hook(env.win, 17, 1L << 0, close_window, &env);
	
	mlx_loop_hook(env.mlx, draw, &env);
	mlx_loop(env.mlx);
	return (0);
}

int	draw(t_env *env)
{
	env->rotationZ[0][0] = cosf(env->angle);
	env->rotationZ[0][1] = -sinf(env->angle);
	env->rotationZ[0][2] = 0;
	env->rotationZ[1][0] = sinf(env->angle);
	env->rotationZ[1][1] = cosf(env->angle);
	env->rotationZ[1][2] = 0;
	env->rotationZ[2][0] = 0;
	env->rotationZ[2][1] = 0;
	env->rotationZ[2][2] = 1;

	env->rotationX[0][0] = 1;
	env->rotationX[0][1] = 0;
	env->rotationX[0][2] = 0;
	env->rotationX[1][0] = 0;
	env->rotationX[1][1] = cosf(env->angle);
	env->rotationX[1][2] = -sinf(env->angle);
	env->rotationX[2][0] = 0;
	env->rotationX[2][1] = sinf(env->angle);
	env->rotationX[2][2] = cosf(env->angle);

	env->rotationY[0][0] = cosf(env->angle);
	env->rotationY[0][1] = 0;
	env->rotationY[0][2] = sinf(env->angle);
	env->rotationY[1][0] = 0;
	env->rotationY[1][1] = 1;
	env->rotationY[1][2] = 0;
	env->rotationY[2][0] = -sinf(env->angle);
	env->rotationY[2][1] = 0;
	env->rotationY[2][2] = cosf(env->angle);

	draw_background(env, (t_vector2){0, 0}, (t_vector2){1280, 720});

	for (int i = 0; i < 8; i++)
	{
		env->points_matrices[i] = ft_vec_to_matrix(env->points[i]);
		env->rotated[i] = ft_matmul(env->rotationX, env->points_matrices[i], &(t_vector3){3, 3, 1});
		env->rotated[i] = ft_matmul(env->rotationY, env->rotated[i], &(t_vector3){3, 3, 1});
		env->rotated[i] = ft_matmul(env->rotationZ, env->rotated[i], &(t_vector3){3, 3, 1});
		t_vector3	rotated = ft_matrix_to_vec3(env->rotated[i]);
		float	z = 1 / (env->distance - rotated.z);
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
		//draw_point(env, env->final_points[i], env->color, 3);
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

int	close_window(t_env *env)
{
	mlx_destroy_window(env->mlx, env->win);
	exit(0);
}

int	key_handler(int keycode, t_env *env)
{
	if (keycode == 53 || keycode == 65307)
		close_window(env);
	return (0);
}

void	connect(t_env *env, int i, int j, t_vector2 *points)
{
	t_vector2	a = points[i];
	t_vector2	b = points[j];
	draw_line(env, a, b, env->color);
}

void	put_mlx_pixel(t_env *env, t_vector2 *v, int color)
{
	char	*dst;

	dst = env->addr + ((int)v->y * env->line_length + (int)v->x * (env->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_background(t_env *env, t_vector2 s, t_vector2 e)
{
	int	i;
	i = s.x;
	while (s.y <= e.y)
	{
		while (i <= e.x)
		{
			put_mlx_pixel(env, &(t_vector2){i, s.y}, 0x000000);
			i++;
		}
		i = s.x;
		s.y++;
	}
}

void draw_point(t_env *env, t_vector2 p, int col, int strokeweight)
{
	strokeweight = strokeweight <= 0 ? 1 : strokeweight;
	for (int y = p.y - strokeweight; y <= p.y + strokeweight; y++)
	{
		for (int x = p.x - strokeweight; x <= p.x + strokeweight; x++)
		{
			put_mlx_pixel(env, &(t_vector2){x, y}, col);
		}
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
		put_mlx_pixel(env, &(t_vector2){x, y}, col);
		x = x + delta_x;
		y = y + delta_y;
		i++;
	}
}

void	ft_translate_center(t_vector2 *v)
{
	v->x += WIN_W / 2;
	v->y += WIN_H / 2;
}