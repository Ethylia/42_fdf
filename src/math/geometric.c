/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:22:42 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 16:53:49 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>

#include "mat4.h"
#include "vec4.h"

float v4dot(const t_vec4* v1, const t_vec4* v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z + v1->w * v2->w);
}

t_vec4 v4cross(const t_vec4* v1, const t_vec4* v2)
{
	t_vec4 r;

	r.x = v1->y * v2->z - v2->y * v1->z;
	r.y = v1->z * v2->x - v2->z * v1->x;
	r.z = v1->x * v2->y - v2->x * v1->y;
	r.w = 0.0f;
	return (r);
}

static float invsqrt(float number)
{
	return (1.0f / sqrtf(number));
}

t_vec4 v4normalize(const t_vec4 v)
{
	return (v4multf(v, invsqrt(v4dot(&v, &v))));
}

t_mat4 lookvector(const t_vec4 pos, const t_vec4 vec)
{
	t_vec4 up;
	t_vec4 s;
	t_vec4 u;
	t_mat4 r;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	s = v4normalize(v4cross(&vec, &up));
	u = v4cross(&s, &vec);
	m4init(&r, 0.0f);
	r.cols[0].v[0] = s.x;
	r.cols[1].v[0] = s.y;
	r.cols[2].v[0] = s.z;
	r.cols[0].v[1] = u.x;
	r.cols[1].v[1] = u.y;
	r.cols[2].v[1] = u.z;
	r.cols[0].v[2] = -vec.x;
	r.cols[1].v[2] = -vec.y;
	r.cols[2].v[2] = -vec.z;
	r.cols[3].v[0] = -v4dot(&s, &pos);
	r.cols[3].v[1] = -v4dot(&u, &pos);
	r.cols[3].v[2] = v4dot(&vec, &pos);
	return (r);
}
