/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:05:11 by saeby             #+#    #+#             */
/*   Updated: 2022/12/17 12:06:21 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rot_cube.h"

int	mouse_handler(int mouse_code, int x, int y, t_env *env)
{
	if (mouse_code == 4 && env->scale > 5)
			env->scale-= 5;
	if (mouse_code == 5)
		env->scale += 5;
	
	return (0);
}

int	key_handler(int keycode, t_env *env)
{
	if (keycode == 53 || keycode == 65307)
		close_window(env);
	return (0);
}
