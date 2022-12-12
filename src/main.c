/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:35:57 by saeby             #+#    #+#             */
/*   Updated: 2022/12/12 23:17:06 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rot_cube.h"

int	main(void)
{
	t_env env;
	env.angle = 0;

	t_vector2 pm_v = {2, 3};
	env.p = ft_create_matrix(&pm_v);
	env.p[0][0] = 1;
	env.p[0][1] = 0;
	env.p[0][2] = 0;
	env.p[1][0] = 0;
	env.p[1][1] = 1;
	env.p[1][2] = 0;
	/*
	t_vector2 iso_proj_vect = {4, 4};
	float	**iso_proj = ft_create_matrix(&iso_proj_vect);
	iso_proj[0][0] = 1;
	iso_proj[0][1] = 0;
	iso_proj[0][2] = 0;
	iso_proj[0][3] = 0;

	iso_proj[1][0] = 0;
	iso_proj[1][1] = 1;
	iso_proj[1][2] = 0;
	iso_proj[1][3] = 0;

	iso_proj[2][0] = 0;
	iso_proj[2][1] = 0;
	iso_proj[2][2] = 0;
	iso_proj[2][3] = 0;

	iso_proj[3][0] = 0;
	iso_proj[3][1] = 0;
	iso_proj[3][2] = 0;
	iso_proj[3][3] = 1;
	//ft_print_matrix(iso_proj, &iso_proj_vect);
	*/

	t_vector2 ro_m_v = {2, 2};
	env.rotation = ft_create_matrix(&ro_m_v);

	env.ul = &(t_vector3){640, 360, 0};
	env.ur = &(t_vector3){0, 0, 0};
	env.bl = &(t_vector3){0, 0, 0};
	env.br = &(t_vector3){0, 0, 0};

	
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, 1280, 720, "rot_cube");
	env.img = mlx_new_image(env.mlx, 1280, 720);
	env.addr = mlx_get_data_addr(env.img, &env.bits_per_pixel, &env.line_length, &env.endian);

	mlx_hook(env.win, 2, 1L << 0, key_handler, &env);
	mlx_hook(env.win, 17, 1L << 0, close_window, &env);
	
	mlx_loop_hook(env.mlx, draw, &env);
	mlx_loop(env.mlx);

	//ft_free_matrix(p, 2);
	//ft_free_matrix(point, 1);
	return (0);
}

int	draw(t_env *env)
{
	env->rotation[0][0] = cosf(env->angle);
	env->rotation[0][1] = -sinf(env->angle);

	env->rotation[1][0] = sinf(env->angle);
	env->rotation[1][1] = cosf(env->angle);

	env->ul_f = ft_vec_to_matrix(env->ul);
	env->ur_f = ft_vec_to_matrix(env->ur);
	env->bl_f = ft_vec_to_matrix(env->bl);
	env->br_f = ft_vec_to_matrix(env->br);

	env->projected_2d_ul = ft_matmul(env->p, env->ul_f, &(t_vector3){2, 3, 1});
	env->projected_2d_ur = ft_matmul(env->p, env->ur_f, &(t_vector3){2, 3, 1});
	env->projected_2d_bl = ft_matmul(env->p, env->bl_f, &(t_vector3){2, 3, 1});
	env->projected_2d_br = ft_matmul(env->p, env->br_f, &(t_vector3){2, 3, 1});

	env->rotated_2d_ul = ft_matmul(env->rotation, env->projected_2d_ul, &(t_vector3){2, 2, 1});
	env->rotated_2d_ur = ft_matmul(env->rotation, env->projected_2d_ur, &(t_vector3){2, 2, 1});
	env->rotated_2d_bl = ft_matmul(env->rotation, env->projected_2d_bl, &(t_vector3){2, 2, 1});
	env->rotated_2d_br = ft_matmul(env->rotation, env->projected_2d_br, &(t_vector3){2, 2, 1});

	env->ul_final_v = ft_matrix_to_vec2(env->rotated_2d_ul);
	env->ur_final_v = ft_matrix_to_vec2(env->rotated_2d_ur);
	env->bl_final_v = ft_matrix_to_vec2(env->rotated_2d_bl);
	env->br_final_v = ft_matrix_to_vec2(env->rotated_2d_br);

	// Need to take into account the size of the screen and "translate" to a more centered position
	// before drawing the pixels but I have something moving on the screen and that's a great point
	// (I'll also have to change the vectors to float instead of int (maybe))
	// (and also make this code more readable)

	draw_background(env, (t_vector2){0, 0}, (t_vector2){1280, 720});
	put_mlx_pixel(env, &env->ul_final_v, 0xFFFFFFFF);
	put_mlx_pixel(env, &env->ur_final_v, 0xFFFFFFFF);
	put_mlx_pixel(env, &env->bl_final_v, 0xFFFFFFFF);
	put_mlx_pixel(env, &env->br_final_v, 0xFFFFFFFF);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	env->angle += 0.001;
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

void	put_mlx_pixel(t_env *env, t_vector2 *v, int color)
{
	char	*dst;

	dst = env->addr + (v->y * env->line_length + v->x * (env->bits_per_pixel / 8));
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

/*
void	put_rect(t_env *env, t_vector2 *s_v, t_vector2 *e_v, int color)
{
	int	i;
	int	j;

	i = s_v->x;
	while (i <= e_v->x)
	{

	}
}
*/
