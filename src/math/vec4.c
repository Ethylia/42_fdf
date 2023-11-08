/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:20:09 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 16:56:39 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4.h"

void v4init(t_vec4* vec, float v)
{
	vec->x = v;
	vec->y = v;
	vec->z = v;
	vec->w = v;
}

t_vec4 v4addv4(const t_vec4 v1, const t_vec4 v2)
{
	t_vec4 r;

	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;
	r.z = v1.z + v2.z;
	r.w = v1.w + v2.w;
	return (r);
}

t_vec4 v4multf(const t_vec4 v, float f)
{
	t_vec4 r;

	r.x = v.x * f;
	r.y = v.y * f;
	r.z = v.z * f;
	r.w = v.w * f;
	return (r);
}
