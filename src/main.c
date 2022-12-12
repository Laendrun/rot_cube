/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:35:57 by saeby             #+#    #+#             */
/*   Updated: 2022/12/12 21:36:13 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rot_cube.h"

int	main(void)
{
	t_vector2 pm_v = {2, 3};
	float	**p = ft_create_matrix(&pm_v);
	p[0][0] = 1;
	p[0][1] = 0;
	p[0][2] = 0;
	p[1][0] = 0;
	p[1][1] = 1;
	p[1][2] = 0;

	t_vector3 v = {100, 75, 50};
	float	**point = ft_vec_to_matrix(&v);
	ft_print_matrix(point, &(t_vector2){3, 1});

	float	**result = ft_matmul(p, point, &(t_vector3){2, 3, 1});
	ft_print_matrix(result, &(t_vector2){1, 2});
	t_vector2 res_v = ft_matrix_to_vec2(result);
	ft_print_vector2(&res_v);
	
	ft_free_matrix(p, 2);
	ft_free_matrix(point, 1);
	return (0);
}
