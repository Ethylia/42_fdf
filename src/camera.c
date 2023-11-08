/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:36:27 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 17:13:17 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math/transform.h"
#include "camera.h"

void caminit(float w, float h, t_camera* cam)
{
	t_vec4 ax;

	*cam = (t_camera){0};
	cam->pos.x = 0.0f;
	cam->pos.y = 0.6f;
	cam->pos.z = 0.6f;
	ax.x = cosf(45.0f) * sinf(0.0f);
	ax.y = sinf(45.0f);
	ax.z = cosf(45.0f) * cosf(0.0f);
	cam->ang[0] = 0.0f;
	cam->ang[1] = 0.0f;
	cam->fov = 1.5f;
	cam->pr = m4perspective(cam->fov, w / h, 0.1f, 100.0f);
	cam->vw = lookvector(cam->pos, ax);
}

void camheading(t_camera* cam)
{
	t_vec4 ax;

	ax.x = cosf(cam->ang[0]) * sinf(cam->ang[1]);
	ax.y = sinf(cam->ang[0]);
	ax.z = cosf(cam->ang[0]) * cosf(cam->ang[1]);
	cam->vw = lookvector(cam->pos, ax);
}

void camper(float w, float h, t_camera* cam)
{
	cam->pr = m4perspective(cam->fov, w / h, 0.001f, 100.0f);
}

void camortho(float w, float h, t_camera* cam)
{
	cam->pr = m4ortho(w / 10.0f, h / 10.0f, 0.1f, 100.0f);
}
