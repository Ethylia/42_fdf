/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:00:11 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 17:01:57 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

#include <stdlib.h>

#include "fdf.h"

static void _reset(t_info* i)
{
	i->angle[1] = 0.785398f;
	i->angle[2] = 0.0f;
	i->pos.x = 0.0f;
	i->cam.pos.y = 0.6f;
	i->cam.pos.z = 0.6f;
	i->cam.fov = 1.5f;
}

void _ft_key(mlx_key_data_t key, void* info)
{
	t_info* const i = info;

	if(key.key == I_KEYW)
		i->inputs[0] = key.action;
	else if(key.key == I_KEYS)
		i->inputs[1] = key.action;
	else if(key.key == I_ESC)
	{
		mlx_close_window(i->mlx);
		mlx_delete_image(i->mlx, i->fb);
		free(i->map.v);
		free(i->map.vc);
		free(i->map.c);
		mlx_terminate(i->mlx);
		exit(0);
	}
	else if(key.key == I_KEYP && key.action == MLX_PRESS)
		i->mode = !i->mode;
	else if(key.key == I_KEYC && key.action == MLX_PRESS)
		i->docurve = !i->docurve;
	else if(key.key == I_KEYF && key.action == MLX_PRESS)
		i->dolight = !i->dolight;
	else if(key.key == I_KEYR && key.action == MLX_PRESS)
		_reset(i);
}

void _ft_mouse(mouse_key_t button, action_t action,
	modifier_key_t mods, void* info)
{
	t_info* const i = info;

	(void)mods;
	if(button == I_M1)
		i->inputs[8] = action;
	else if(button == I_M2)
		i->inputs[9] = action;
}

static void _ft_mdrag(int x, int y, t_info* i)
{
	int dp[2];

	dp[0] = x - i->lp[0];
	dp[1] = y - i->lp[1];
	if(i->inputs[8] && i->inputs[9])
	{
		i->pos.x += (float)dp[0] * 0.0025f * i->cam.fov * 0.4f;
		i->cam.pos.z -= (float)dp[1] * 0.00125f * i->cam.fov * 0.565f;
		i->cam.pos.y += (float)dp[1] * 0.00125f * i->cam.fov * 0.565f;
	}
	else if(i->inputs[8])
	{
		i->angle[1] += (float)dp[0] * 0.005f;
		i->angle[2] += (float)dp[1] * 0.005f;
	}
	else if(i->inputs[9])
	{
		i->cam.fov += (float)dp[1] * 0.002f;
		i->amp += (float)dp[0] * 0.01f;
	}
	i->lp[0] = x;
	i->lp[1] = y;
}

void handleinput(t_info* i)
{
	int mp[2];

	if(i->inputs[0])
		i->cam.fov += 0.04f;
	if(i->inputs[1])
		i->cam.fov -= 0.04f;
	if(i->inputs[2])
		i->pos.x -= 0.04f;
	if(i->inputs[3])
		i->pos.x += 0.04f;
	if(i->inputs[4])
		i->angle[0] += 0.1f;
	if(i->inputs[5])
		i->angle[0] -= 0.1f;
	if(i->inputs[6])
		i->angle[1] += 0.1f;
	if(i->inputs[7])
		i->angle[1] -= 0.1f;
	mlx_get_mouse_pos(i->mlx, &mp[0], &mp[1]);
	_ft_mdrag(mp[0], mp[1], i);
}
