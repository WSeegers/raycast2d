/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:46:09 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/23 16:14:27 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_mhero(t_env *env)
{
	t_vec2i pos;

	pos = VEC2I((int)(env->hero->pos.x * 5), (int)(env->hero->pos.y * 5));
	wfx_fcircle(env->window, pos, 5, 0x00ffffff);
}

static void		draw_mmap(t_env *env)
{
	int 	size;
	int		colour;
	t_vec2i loc;
	
	size = 5;
	for(int y = 0; y < env->map.height; y++)
		for(int x = 0; x < env->map.width; x++)
		{
			if (grid_get(&env->map, x, y))
				colour = 0x00550055;
			else
				colour = 0x005500;
			wfx_rect(env->window,
					VEC2I(x * size, y * size),
					VEC2I(x * size + size, y * size + size),
					colour, true);

		}
}

void	draw_ui(t_env *env)
{
	draw_mmap(env);
	draw_mhero(env);
}
