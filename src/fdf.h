/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:40:19 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 17:11:48 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include <MLX42/MLX42.h>

#include "math/vec4.h"
#include "math/mat4.h"
#include "framebuffer.h"
#include "camera.h"
#include "map.h"

typedef struct s_info
{
	t_camera cam;
	mlx_image_t* fb;
	t_map map;
	mlx_t* mlx;
	t_mat4 ml;
	t_vec4 pos;
	t_vec4 light;
	float angle[3];
	int inputs[16];
	int mode;
	float amp;
	int lp[2];
	int dolight;
	int docurve;
} t_info;

#endif
