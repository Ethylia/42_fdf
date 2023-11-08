/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:09:15 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 17:12:54 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>

#include <stdlib.h>

#include "framebuffer.h"
#include "math/mat4.h"
#include "math/transform.h"
#include "fdf.h"
#include "input.h"
#include "map.h"

static void _ft_destroy(void* info)
{
	t_info* const i = info;

	mlx_delete_image(i->mlx, i->fb);
	free(i->map.v);
	free(i->map.vc);
	free(i->map.c);
	mlx_terminate(i->mlx);
	exit(0);
}

static void drawlines(t_info* i, size_t x, size_t y)
{
	t_linedata ld;
	const size_t cv = y * i->map.w + x;
	const t_vec4* t[2]
		= { &i->map.vc[cv + (x < i->map.w - 1)],
		&i->map.vc[cv + i->map.w * (y < i->map.h - 1)] };

	if(i->mode && i->map.vc[cv].w >= -0.1f)
		return;
	ld.v1 = &i->map.v[cv];
	ld.x1 = (int)((i->map.vc[cv].x + 1.0f) * 960.0f);
	ld.y1 = (int)((i->map.vc[cv].y + 1.0f) * 540.0f);
	if(x < i->map.w - 1)
	{
		ld.v2 = &i->map.v[cv + 1];
		ld.x2 = (int)((t[0]->x + 1.0f) * 960.0f);
		ld.y2 = (int)((t[0]->y + 1.0f) * 540.0f);
		fbdrawline(i, ld, i->map.c[cv], i->map.c[cv + 1]);
	}
	if(y < i->map.h - 1)
	{
		ld.v2 = &i->map.v[cv + i->map.w];
		ld.x2 = (int)((t[1]->x + 1.0f) * 960.0f);
		ld.y2 = (int)((t[1]->y + 1.0f) * 540.0f);
		fbdrawline(i, ld, i->map.c[cv], i->map.c[cv + i->map.w]);
	}
}

static void drawmesh(t_info* i, const t_mat4 pvm)
{
	size_t x;
	size_t y;

	y = -1;
	while(++y < i->map.h)
	{
		x = -1;
		while(++x < i->map.w)
			i->map.vc[y * i->map.w + x]
			= m4v4(pvm, i->map.v[y * i->map.w + x].v);
	}
	y = -1;
	while(++y < i->map.h)
	{
		x = -1;
		while(++x < i->map.w)
			drawlines(i, x, y);
	}
}

static void _ft_loop(void* info)
{
	t_info* const i = info;
	const t_vec4 axis = { .x = 0.0f, .y = 1.0f, .z = 0.0f };
	const t_vec4 axis2 = { .x = 0.0f, .y = 0.0f, .z = 1.0f };
	const t_vec4 axis3 = { .x = 1.0f, .y = 0.0f, .z = 0.0f };
	t_mat4 pvm;

	camheading(&i->cam);
	if(!i->mode)
		camortho(1920.0f * 0.1f * (-i->cam.fov * 0.1f), 1080.0f * 0.1f
			* (-i->cam.fov * 0.1f), &i->cam);
	else
		camper(1920.0f, 1080.0f, &i->cam);
	i->ml = m4rotation(i->angle[1], axis);
	i->ml = m4m4(m4translation(i->pos.x, i->pos.y, i->pos.z),
		m4m4(m4rotation(i->angle[2], axis3),
			m4m4(m4rotation(i->angle[0], axis2), i->ml)));
	i->ml = (m4m4(i->ml, m4scaley(i->amp)));
	pvm = m4m4(m4m4(i->cam.pr, i->cam.vw), i->ml);
	fbclear(i, 0x000000ff, m4v4(pvm, i->light.v));
	handleinput(i);
	drawmesh(i, pvm);
}

int main(int argc, char** argv)
{
	t_info info = {0};

	if(argc != 2 || !loadmap(&info.map, argv[1]))
		return (0);
	caminit(1920.0f, 1080.0f, &info.cam);
	info.angle[1] = 0.785398f;
	info.cam.ang[0] = 0.78f;
	info.amp = 4.0f;
	v4init(&info.light, 0.8f);
	info.light.y = 0.04f;
	m4init(&info.ml, 1.0f);
	info.mlx = mlx_init(1920, 1080, "FDF", 0);
	info.fb = mlx_new_image(info.mlx, 1920, 1080);
	mlx_image_to_window(info.mlx, info.fb, 0, 0);
	mlx_loop_hook(info.mlx, _ft_loop, &info);
	mlx_close_hook(info.mlx, _ft_destroy, &info);
	mlx_key_hook(info.mlx, _ft_key, &info);
	mlx_mouse_hook(info.mlx, _ft_mouse, &info);
	mlx_loop(info.mlx);
	_ft_destroy(&info);
	return (0);
}
