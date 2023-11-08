/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:23:13 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 16:56:22 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mat4.h"
#include "vec4.h"

t_mat4 m4perspective(float fov, float aspectRatio, float near, float far);
t_mat4 m4ortho(float w, float h, float near, float far);
t_mat4 m4translation(float x, float y, float z);
t_mat4 m4rotation(float angle, const t_vec4 axis);
t_mat4 m4scaley(float scale);
t_mat4 lookvector(const t_vec4 pos, const t_vec4 vec);

#endif
