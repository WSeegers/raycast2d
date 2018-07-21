/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 21:31:18 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/21 08:38:06 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"
#include "wolf3d.h"
#include "dda.h"

static void	draw_fps(t_env *env)
{
	t_hit_report	hr;
	t_vec2i			p1;
	t_vec2i			p2;
	t_vec2			ray;
	int				colour;

	for	(int x = 0; x < env->window->width; x++)
	{
		ray = vec2_add(env->hero->direction, vec2_scale(env->hero->plane, 2 * x / (double)env->window->width - 1));
		hr = dda(env->hero->pos, ray, env->map);
		if (hr.side == HIT_NORTH)
			colour = 0x0000ffff;
		else if (hr.side == HIT_EAST)
			colour = 0x00ff00ff;
		else if (hr.side == HIT_SOUTH)
			colour = 0x00ffff00;
		else if (hr.side == HIT_WEST)
			colour = 0x003d8e51;
		p1 = VEC2I(env->window->width - x, (env->window->height / 2) - (1 / hr.hit_dist * env->window->height / 2));
		p2 = VEC2I(env->window->width - x, (env->window->height / 2) + (1 / hr.hit_dist * env->window->height / 2));
		wfx_line(env->window, VEC2I(env->window->width - x, 0), p1, 0x00cbd88f);
		wfx_line(env->window, p1, p2, colour);
		wfx_line(env->window, p2, VEC2I(env->window->width - x, env->window->height - 1), 0x00546d6d);
	}
	wfx_blit(env->window);
}

int 		game_loop(void *param)
{
	t_env			*env;

	env = (t_env*)param;
	update_hero(env->hero, env->map);
	draw_fps(env);
	return (0);
}