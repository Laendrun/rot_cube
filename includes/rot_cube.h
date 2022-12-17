/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_cube.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:36:34 by saeby             #+#    #+#             */
/*   Updated: 2022/12/17 12:17:02 by saeby            ###   ########.fr       */
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
	int			trigger;
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
int		render(t_env *env);

// utils.c
int		close_window(t_env *env);
void	ft_translate_center(t_vector2 *v);

// draw.c
void	draw_background(t_env *env, t_vector2 s, t_vector2 e);
void	draw_line(t_env *env, t_vector2 s, t_vector2 e, int col);
void	put_rect(t_env *env, t_vector2 *s_v, t_vector2 *e_v, int color);

// draw_utils.c
void	connect(t_env *env, int i, int j, t_vector2 *points);
void	put_mlx_pixel(t_env *env, t_vector2 v, int color);

// inputs.c
int		key_handler(int keycode, t_env *env);
int		mouse_handler(int mouse_code, int x, int y, t_env *env);

// init.c
void	init(t_env *env);
void	create_cube(t_env *env);

// update.c
void	update_rotation_matrices(t_env *env);

#endif