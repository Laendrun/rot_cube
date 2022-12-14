/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:45:35 by saeby             #+#    #+#             */
/*   Updated: 2022/12/14 20:02:37 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rot_cube.h"

float	**ft_matmul(float **a, float **b, t_vector3 *v)
{
	/*
	 * v->x : rowsA
	 * v->y : colsA
	 * v->z : colsB
	 */
	float **result = malloc(v->x * sizeof(float *));
	for (int i = 0; i < v->x; i++) 
	{
		result[i] = malloc(v->z * sizeof(float));
		for (int j = 0; j < v->z; j++)
		{
			float	sum = 0;
			for (int k = 0; k < v->y; k++)
				sum += a[i][k] * b[k][j];
			result[i][j] = sum;
		}
	}
	return (result);
}

void	ft_print_matrix(float **a, t_vector2 *v)
{
	printf("%fx%f\n", v->x, v->y);
	printf("-------\n");
	for (int i = 0; i < v->x; i++) 
	{
		for (int j = 0; j < v->y; j++)
		{
			printf("%f ", a[i][j]);
		}
		printf("\n");
	}
}

float	**ft_create_matrix(t_vector2 *v)
{
	float	**result;

	result = malloc(v->x * sizeof(float *));
	for (int i = 0; i < v->x; i++)
		result[i] = malloc(v->y * sizeof(float));
	return (result);
}

void	ft_free_matrix(float **m, int rows)
{
	for (int i = 0; i < rows; i++)
		free(m[i]);
	free(m);
}

float		**ft_vec_to_matrix(t_vector3 *v)
{
	float	**m = ft_create_matrix(&(t_vector2){3, 1});
	m[0][0] = v->x;
	m[1][0] = v->y;
	m[2][0] = v->z;
	return (m);
}

t_vector3	ft_matrix_to_vec3(float **m)
{
	t_vector3	v;

	v.x = m[0][0];
	v.y = m[0][1];
	v.z = m[0][2];
	return (v);
}

t_vector2	ft_matrix_to_vec2(float **m)
{
	t_vector2	v;;

	v.x = m[0][0];
	v.y = m[1][0];
	return (v);
}

void	ft_print_vector2(t_vector2 *v)
{
	printf("=====VECTOR 2=====\n");
	printf("v->x : %f\n", v->x);
	printf("v->y : %f\n", v->y);
}

void	ft_print_vector3(t_vector3 *v)
{
	printf("=====VECTOR 3=====\n");
	printf("v->x : %f\n", v->x);
	printf("v->y : %f\n", v->y);
	printf("v->z : %f\n", v->z);
}