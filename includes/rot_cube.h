/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_cube.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:36:34 by saeby             #+#    #+#             */
/*   Updated: 2022/12/12 23:14:09 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROT_CUBE_H
# define ROT_CUBE_H
# define PI 3.141592654
# include "mat.h"
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_env {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	float		angle;
	float		**p;
	float		**rotation;
	float	**ul_f;
	float	**ur_f;
	float	**bl_f;
	float	**br_f;
	float	**projected_2d_ul;
	float	**projected_2d_ur;
	float	**projected_2d_bl;
	float	**projected_2d_br;
	float	**rotated_2d_ul;
	float	**rotated_2d_ur;
	float	**rotated_2d_bl;
	float	**rotated_2d_br;
	t_vector3 *ul;
	t_vector3 *ur;
	t_vector3 *bl;
	t_vector3 *br;
	t_vector2 ul_final_v;
	t_vector2 ur_final_v;
	t_vector2 bl_final_v;
	t_vector2 br_final_v;
}				t_env;

// main.c
int		key_handler(int keycode, t_env *env);
int		close_window(t_env *env);
void	put_mlx_pixel(t_env *env, t_vector2 *v, int color);
void	put_rect(t_env *env, t_vector2 *s_v, t_vector2 *e_v, int color);
int		draw(t_env *env);
void	draw_background(t_env *env, t_vector2 s, t_vector2 e);

#endif