/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:24:53 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 16:56:26 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "mat4.h"
#include "vec4.h"
#include "geometric.h"

t_mat4 m4perspective(float fov, float aspectRatio, float near, float far)
{
	t_mat4 mat;
	const float tanhalffov = tan(fov / 2.0f);

	m4init(&mat, 0.0f);
	mat.cols[0].v[0] = 1.0f / (aspectRatio * tanhalffov);
	mat.cols[1].v[1] = 1.0f / (tanhalffov);
	mat.cols[2].v[3] = -1.0f;
	mat.cols[2].v[2] = -(far + near) / (far - near);
	mat.cols[3].v[2] = -(2.0f * far * near) / (far - near);
	return (mat);
}

t_mat4	m4ortho(float w, float h, float near, float far)
{
	t_mat4 r;

	m4init(&r, 0.0f);
	r.cols[0].v[0] = 2.0f / w;
	r.cols[1].v[1] = 2.0f / h;
	r.cols[2].v[2] = 1.0f / (far - near);
	r.cols[3].v[3] = 1.0f;
	r.cols[3].v[2] = -near / (far - near);
	return (r);
}

t_mat4	m4translation(float x, float y, float z)
{
	t_mat4 r;

	m4init(&r, 1.0f);
	r.cols[3].v[0] = x;
	r.cols[3].v[1] = y;
	r.cols[3].v[2] = z;
	return (r);
}

t_mat4	m4rotation(float angle, const t_vec4 axis)
{
	const float a = angle;
	const float c = cosf(a);
	const float s = sinf(a);
	const t_vec4 temp = v4multf(axis, (1.0f - c));
	t_mat4 mat;

	m4init(&mat, 1.0f);
	mat.cols[0].v[0] = c + temp.v[0] * axis.v[0];
	mat.cols[0].v[1] = temp.v[0] * axis.v[1] + s * axis.v[2];
	mat.cols[0].v[2] = temp.v[0] * axis.v[2] - s * axis.v[1];
	mat.cols[1].v[0] = temp.v[1] * axis.v[0] - s * axis.v[2];
	mat.cols[1].v[1] = c + temp.v[1] * axis.v[1];
	mat.cols[1].v[2] = temp.v[1] * axis.v[2] + s * axis.v[0];
	mat.cols[2].v[0] = temp.v[2] * axis.v[0] + s * axis.v[1];
	mat.cols[2].v[1] = temp.v[2] * axis.v[1] - s * axis.v[0];
	mat.cols[2].v[2] = c + temp.v[2] * axis.v[2];
	return (mat);
}

t_mat4	m4scaley(float scale)
{
	t_mat4 r;

	m4init(&r, 1.0f);
	r.mat[5] = scale;
	return (r);
}
