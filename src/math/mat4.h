/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:23:27 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 16:54:43 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_H
#define MAT4_H

#include "vec4.h"

typedef struct s_mat4
{
	union
	{
		float mat[16];
		t_vec4 cols[4];
	};
} t_mat4;

void m4init(t_mat4* mat, float diagonal);
t_vec4 m4v4(const t_mat4 m, const float v[4]);
t_mat4 m4m4(const t_mat4 m1, const t_mat4 m2);

#endif
