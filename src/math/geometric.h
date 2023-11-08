/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometric.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:21:33 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 16:54:50 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include "vec4.h"

float v4dot(const t_vec4 *v1, const t_vec4 *v2);
t_vec4 v4cross(const t_vec4 *v1, const t_vec4 *v2);
t_vec4 v4normalize(const t_vec4 v);

#endif
