/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:59:49 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 17:02:12 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H

#include "fdf.h"

enum
{
	I_KEYW = MLX_KEY_W,
	I_KEYS = MLX_KEY_S,
	I_KEYF = MLX_KEY_F,
	I_KEYC = MLX_KEY_C,
	I_KEYP = MLX_KEY_P,
	I_KEYR = MLX_KEY_R,
	I_M1 = MLX_MOUSE_BUTTON_LEFT,
	I_M2 = MLX_MOUSE_BUTTON_RIGHT,
	I_ESC = MLX_KEY_ESCAPE
};

void _ft_key(mlx_key_data_t key, void* i);
void _ft_mouse(mouse_key_t button, action_t action,
	modifier_key_t mods, void* info);
void handleinput(t_info* i);

#endif
