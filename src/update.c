/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:16:41 by saeby             #+#    #+#             */
/*   Updated: 2022/12/17 12:29:10 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rot_cube.h"

void	update_rotation_matrices(t_env *env)
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
}
