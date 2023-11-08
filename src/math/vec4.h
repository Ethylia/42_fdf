/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:25:09 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 16:56:58 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC4_H
#define VEC4_H

typedef struct s_vec4
{
	union
	{
		float v[4];
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
} t_vec4;

void v4init(t_vec4* vec, float v);
t_vec4 v4addv4(const t_vec4 v1, const t_vec4 v2);
t_vec4 v4multf(const t_vec4 v, float f);

#endif
