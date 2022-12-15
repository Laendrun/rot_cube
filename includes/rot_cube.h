/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_cube.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:36:34 by saeby             #+#    #+#             */
/*   Updated: 2022/12/15 14:33:53 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROT_CUBE_H
# define ROT_CUBE_H
# define WIN_H 720
# define WIN_W 1280
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
	int			color;
	float		distance;
	float		scale;
	float		angle;
	float		angle_update;
	float		**p;
	float		**rotationZ;
	float		**rotationY;
	float		**rotationX;
	t_vector3	*points;
	t_vector2	*final_points;
	float		***projected;
	float		***rotated;
	float		***points_matrices;
}				t_env;

// main.c
int		key_handler(int keycode, t_env *env);
int		close_window(t_env *env);
void	put_mlx_pixel(t_env *env, t_vector2 *v, int color);
void	put_rect(t_env *env, t_vector2 *s_v, t_vector2 *e_v, int color);
int		draw(t_env *env);
void	draw_background(t_env *env, t_vector2 s, t_vector2 e);
void	draw_point(t_env *env, t_vector2 p, int col, int strokeweight);
void	draw_line(t_env *env, t_vector2 s, t_vector2 e, int col);
void	connect(t_env *env, int i, int j, t_vector2 *points);
void	ft_translate_center(t_vector2 *v);

#endif