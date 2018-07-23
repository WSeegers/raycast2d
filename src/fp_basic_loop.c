/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_basic_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 21:31:18 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/23 16:12:56 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"
#include "wolf3d.h"
#include "dda.h"

static void	draw_first_person(t_env *env)
{
	t_hit_report	hr;
	t_vec2i			p1;
	t_vec2i			p2;
	t_vec2			ray;
	int				colour;

	for	(int x = 0; x < POV_WIDTH; x++)
	{
		ray = vec2_add(env->hero->direction, vec2_scale(env->hero->plane, 2 * x / (double)POV_WIDTH - 1));
		hr = dda(env->hero->pos, ray, env->map);
		if (hr.side == HIT_NORTH)
			colour = 0x0000ffff;
		else if (hr.side == HIT_EAST)
			colour = 0x00ff00ff;
		else if (hr.side == HIT_SOUTH)
			colour = 0x00ffff00;
		else if (hr.side == HIT_WEST)
			colour = 0x003d8e51;
		p1 = VEC2I(POV_WIDTH - x, (POV_HEIGHT / 2) - (1 / hr.hit_dist * POV_HEIGHT / 2));
		p2 = VEC2I(POV_WIDTH - x, (POV_HEIGHT / 2) + (1 / hr.hit_dist * POV_HEIGHT / 2));
		pov_line(env->window, VEC2I(POV_WIDTH - x, 0), p1, 0x00cbd88f);
		pov_line(env->window, p1, p2, colour);
		pov_line(env->window, p2, VEC2I(POV_WIDTH - x, POV_HEIGHT - 1), 0x00546d6d);
	}
}

int 		fp_basic_loop(void *param)
{
	t_env			*env;

	env = (t_env*)param;
	update_hero(env->hero, env->map);
	draw_first_person(env);
	draw_ui(env);
	wfx_blit(env->window);
	return (0);
}