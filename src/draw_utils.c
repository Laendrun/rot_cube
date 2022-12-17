/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:07:31 by saeby             #+#    #+#             */
/*   Updated: 2022/12/17 12:08:53 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rot_cube.h"

void	put_mlx_pixel(t_env *env, t_vector2 v, int color)
{
	char	*dst;

	if (v.x >= 0 && v.x < WIN_W && v.y >= 0 && v.y < WIN_H)
	{	
		dst = env->addr + ((int)v.y * env->line_length \
									+ (int)v.x * (env->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	connect(t_env *env, int i, int j, t_vector2 *points)
{
	t_vector2	a = points[i];
	t_vector2	b = points[j];
	draw_line(env, a, b, env->color);
}
