/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framebuffer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:04:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 17:00:55 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "math/vec4.h"

typedef struct s_linedata
{
	const t_vec4* v1;
	const t_vec4* v2;
	int x1;
	int y1;
	int x2;
	int y2;
} t_linedata;

void fbdraw(void* i, int x, int y, int color);
void fbclear(void* i, int color, const t_vec4 l);
void fbdrawline(void* i, const t_linedata data, int c1, int c2);

#endif
