/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:40:09 by saeby             #+#    #+#             */
/*   Updated: 2022/12/12 21:34:05 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT_H
# define MAT_H
# include "mat_structures.h"

float		**ft_matmul(float **a, float **b, t_vector3 *v);
void		ft_print_matrix(float **a, t_vector2 *v);
float		**ft_create_matrix(t_vector2 *v);
void		ft_free_matrix(float **m, int rows);

float		**ft_vec_to_matrix(t_vector3 *v);
t_vector3	ft_matrix_to_vec3(float **m);
t_vector2	ft_matrix_to_vec2(float **m);

void		ft_print_vector2(t_vector2 *v);
void		ft_print_vector3(t_vector3 *v);

#endif