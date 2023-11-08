/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:40:38 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 16:55:15 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int ftabs(int v)
{
	if(v < 0)
		return (-v);
	return (v);
}

float ftabsf(float v)
{
	if(v < 0)
		return (-v);
	return (v);
}

int ftmin(int n1, int n2)
{
	if(n1 < n2)
		return (n1);
	return (n2);
}

float ftminf(float n1, float n2)
{
	if(n1 < n2)
		return (n1);
	return (n2);
}

unsigned int interpc(int c1, int c2, float i)
{
	int32_t c[6];

	c[0] = (c1 >> 24) & 0xff;
	c[1] = (c1 >> 16) & 0xff;
	c[2] = (c1 >> 8) & 0xff;
	c[3] = (c2 >> 24) & 0xff;
	c[4] = (c2 >> 16) & 0xff;
	c[5] = (c2 >> 8) & 0xff;
	c[0] = (((int)(i * 100.0f)) * (c[3] - c[0])) / 100 + c[0];
	c[1] = (((int)(i * 100.0f)) * (c[4] - c[1])) / 100 + c[1];
	c[2] = (((int)(i * 100.0f)) * (c[5] - c[2])) / 100 + c[2];
	return (255 | (unsigned int)c[0] << 24
		| (unsigned int)c[1] << 16 | (unsigned int)c[2] << 8);
}
