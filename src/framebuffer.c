/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framebuffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:09:37 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 17:26:37 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "framebuffer.h"

#include <MLX42/MLX42.h>

#include "fdf.h"
#include "math/math.h"
#include "math/vec4.h"

void fbdraw(void* info, int x, int y, int color)
{
	const t_info* const i = info;

	if(i->docurve)
		y -= ftabs(x - 960) * ftabs(x - 960) * 0.0005f;
	if(x > 1919 || x < 0 || y > 1079 || y < 0)
		return;
	mlx_put_pixel(i->fb, x, y, color);
}

static void initdl(const t_linedata* data, int d[8], float* i)
{
	d[0] = ftabs(data->x2 - data->x1);
	d[1] = -ftabs(data->y2 - data->y1);
	d[2] = 2 * (data->x1 < data->x2) - 1;
	d[3] = 2 * (data->y1 < data->y2) - 1;
	d[4] = d[0] + d[1];
	d[6] = data->x1 + data->y1;
	*i = 0.0f;
}

static int culling(const t_linedata* d)
{
	if((d->x1 < 0 && d->x2 < 0) ||
		(d->y1 < 0 && d->y2 < 0) ||
		(d->x1 > 1920 && d->x2 > 1920) ||
		(d->y1 > 1080 && d->y2 > 1080))
		return 1;
	return 0;
}

void fbdrawline(void* info, t_linedata d, int c1, int c2)
{
	int t[8];
	float it;

	if(culling(&d))
		return;

	initdl(&d, t, &it);
	while(1)
	{
		if((d.x2 + d.y2 - t[6]))
			it = (float)(d.x1 + d.y1 - t[6]) / (float)(d.x2 + d.y2 - t[6]);
		fbdraw(info, d.x1, d.y1, interpc(c1, c2, it));
		if(d.x1 == d.x2 && d.y1 == d.y2)
			break;
		t[5] = 2 * t[4];
		if(t[5] >= t[1])
		{
			t[4] += t[1];
			d.x1 += t[2];
		}
		if(t[5] <= t[0])
		{
			t[4] += t[0];
			d.y1 += t[3];
		}
	}
}

void fbclear(void* info, int color, const t_vec4 l)
{
	t_info* const i = info;
	int x;
	int y;
	int rx[2];

	x = -1;
	while(++x < 1920)
	{
		y = -1;
		while(++y < 1080)
		{
			rx[0] = (int)((l.x + 1.0f) * 960.0f);
			rx[1] = (int)((l.y + 1.0f) * 540.0f);
			if(i->dolight)
				color = interpc(0x080808ff, 0xf0f0f0ff,
					0.8f - ftminf((ftabs((rx[0] - x)) + ftabs((rx[1] - y))
						- -1920.0f) / (1920.0f * 2)
						- ftabsf(l.w) * -0.1f, 0.8f));
			mlx_put_pixel(i->fb, x, y, color);
		}
	}
}
