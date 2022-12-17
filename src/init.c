/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:11:11 by saeby             #+#    #+#             */
/*   Updated: 2022/12/17 12:28:20 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rot_cube.h"
#define POINTS 8

void	init(t_env *env)
{
	t_vector2 pm_v = {2, 3};
	t_vector2 ro_m_v = {3, 3};

	env->trigger = 0;
	env->angle = 0;
	env->angle_update = 0.005;
	env->points = malloc(POINTS * sizeof(t_vector3));
	env->points_matrices = malloc(POINTS * sizeof(float **));
	env->rotated = malloc(POINTS * sizeof(float **));
	env->projected = malloc(POINTS * sizeof(float **));
	env->final_points = malloc(POINTS * sizeof(t_vector2));

	env->p = ft_create_matrix(&pm_v);

	env->rotationZ = ft_create_matrix(&ro_m_v);
	env->rotationY = ft_create_matrix(&ro_m_v);
	env->rotationX = ft_create_matrix(&ro_m_v);
}

void	create_cube(t_env *env)
{
	env->points[0] = (t_vector3){-0.5, -0.5, -0.5};
	env->points[1] = (t_vector3){0.5, -0.5, -0.5};
	env->points[2] = (t_vector3){0.5, 0.5, -0.5};
	env->points[3] = (t_vector3){-0.5, 0.5, -0.5};

	env->points[4] = (t_vector3){-0.5, -0.5, 0.5};
	env->points[5] = (t_vector3){0.5, -0.5, 0.5};
	env->points[6] = (t_vector3){0.5, 0.5, 0.5};
	env->points[7] = (t_vector3){-0.5, 0.5, 0.5};
}