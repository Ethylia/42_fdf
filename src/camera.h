/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:33:32 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 17:12:10 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
#define CAMERA_H

#include "math/vec4.h"
#include "math/mat4.h"

typedef struct s_camera
{
	t_mat4 pr;
	t_mat4 vw;
	t_vec4 pos;
	float fov;
	float ang[2];
} t_camera;

void caminit(float w, float h, t_camera* cam);
void camper(float w, float h, t_camera* cam);
void camheading(t_camera* cam);
void camortho(float w, float h, t_camera* cam);

#endif
