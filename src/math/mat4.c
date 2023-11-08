/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:09:11 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 16:54:07 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4.h"
#include "mat4.h"

#include <stddef.h>
#include <math.h>

void m4init(t_mat4* mat, float diagonal)
{
	size_t i;

	i = -1;
	while(++i < 16)
		mat->mat[i] = 0.0f;
	mat->mat[0] = diagonal;
	mat->mat[5] = diagonal;
	mat->mat[10] = diagonal;
	mat->mat[15] = diagonal;
}

t_mat4 m4m4(const t_mat4 m1, const t_mat4 m2)
{
	t_mat4 mat;

	mat.cols[0]
		= v4addv4(v4multf(m1.cols[0], m2.cols[0].v[0]),
			v4addv4(v4multf(m1.cols[1], m2.cols[0].v[1]),
				v4addv4(v4multf(m1.cols[2], m2.cols[0].v[2]),
					(v4multf(m1.cols[3], m2.cols[0].v[3])))));
	mat.cols[1]
		= v4addv4(v4multf(m1.cols[0], m2.cols[1].v[0]),
			v4addv4(v4multf(m1.cols[1], m2.cols[1].v[1]),
				v4addv4(v4multf(m1.cols[2], m2.cols[1].v[2]),
					(v4multf(m1.cols[3], m2.cols[1].v[3])))));
	mat.cols[2]
		= v4addv4(v4multf(m1.cols[0], m2.cols[2].v[0]),
			v4addv4(v4multf(m1.cols[1], m2.cols[2].v[1]),
				v4addv4(v4multf(m1.cols[2], m2.cols[2].v[2]),
					(v4multf(m1.cols[3], m2.cols[2].v[3])))));
	mat.cols[3]
		= v4addv4(v4multf(m1.cols[0], m2.cols[3].v[0]),
			v4addv4(v4multf(m1.cols[1], m2.cols[3].v[1]),
				v4addv4(v4multf(m1.cols[2], m2.cols[3].v[2]),
					(v4multf(m1.cols[3], m2.cols[3].v[3])))));
	return (mat);
}

t_vec4 m4v4(const t_mat4 m, const float v[4])
{
	t_vec4 r;

	r.x = m.cols[0].v[0] * v[0] + m.cols[1].v[0] * v[1]
		+ m.cols[2].v[0] * v[2] + m.cols[3].v[0] * v[3];
	r.y = m.cols[0].v[1] * v[0] + m.cols[1].v[1] * v[1]
		+ m.cols[2].v[1] * v[2] + m.cols[3].v[1] * v[3];
	r.z = m.cols[0].v[2] * v[0] + m.cols[1].v[2] * v[1]
		+ m.cols[2].v[2] * v[2] + m.cols[3].v[2] * v[3];
	r.w = m.cols[0].v[3] * v[0] + m.cols[1].v[3] * v[1]
		+ m.cols[2].v[3] * v[2] + m.cols[3].v[3] * v[3];
	if(r.w)
	{
		r.x /= r.w;
		r.y /= r.w;
	}
	return (r);
}
