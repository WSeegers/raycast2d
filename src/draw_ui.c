/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:46:09 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 13:59:13 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_mhero(t_env *env, int size)
{
	t_vec2i pos;

	pos = VEC2I((int)(MAP_OFFSET + env->hero->pos.x * size),
		(int)(MAP_OFFSET + env->hero->pos.y * size));
	wfx_fcircle(env->window, pos, 5, 0x00a00202);
}

static void		draw_mmap(t_env *env)
{
	int		size;
	int		colour;
	t_vec2i loc;

	size = MAP_SIZE / env->map.width;
	loc.y = -1;
	while (++loc.y < env->map.height && (loc.x = -1))
		while (++loc.x < env->map.width)
		{
			if (grid_get(&env->map, loc.x, loc.y))
				colour = 0x00808080;
			else
				colour = 0x00c0c0c0;
			wfx_frect(env->window,
				VEC2I(MAP_OFFSET + (loc.x * size),
					MAP_OFFSET + (loc.y * size)),
				VEC2I(MAP_OFFSET + (loc.x * size + size),
					MAP_OFFSET + (loc.y * size + size)),
				colour);
		}
	draw_mhero(env, size);
}

void			draw_ui(t_env *env)
{
	draw_mmap(env);
}
