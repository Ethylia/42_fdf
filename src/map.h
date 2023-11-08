/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:19:42 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 17:12:18 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
#define MAP_H

#include <stddef.h>

#include "math/vec4.h"

typedef struct s_map
{
	t_vec4 *v;
	t_vec4 *vc;
	int *c;
	size_t w;
	size_t h;
	float s;
} t_map;

int loadmap(t_map *map, const char *file);

#endif
