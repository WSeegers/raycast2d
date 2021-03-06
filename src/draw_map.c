/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 18:12:48 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 13:58:42 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_map.h"

void	draw_rays(t_window *window, t_hero *hero, t_grid map, double scale)
{
	t_hit_report	hr;
	t_vec2i			p2;
	t_vec2			ray;
	int				x;

	x = -1;
	while (++x < window->width)
	{
		ray = vec2_add(hero->direction,
			vec2_scale(hero->plane, 2 * x / (double)window->width - 1));
		hr = dda(hero->pos, ray, map);
		p2 = VEC2_TO_I(vec2_scale(vec2_add(hero->pos,
			vec2_scale(ray, hr.hit_dist)), scale));
		wfx_line(window, VEC2_TO_I(vec2_scale(hero->pos, scale)), p2,
			0x0000ffff);
	}
}

void	draw_plane(t_window *window, t_hero *hero)
{
	t_vec2 p1;
	t_vec2 p2;
	t_vec2 p3;

	p1 = vec2_add(hero->pos, hero->direction);
	p2 = vec2_add(p1, hero->plane);
	p3 = vec2_sub(p1, hero->plane);
	wfx_line(window, VEC2_TO_I(p1), VEC2_TO_I(p2), 0x0000ffff);
	wfx_line(window, VEC2_TO_I(p1), VEC2_TO_I(p3), 0x0000ffff);
}

int		draw_map(void *parm)
{
	t_env	*env;
	t_vec2i	v;

	env = (t_env*)parm;
	update_hero(env->hero, env->map);
	v.y = -1;
	while (v.y++ < env->map.height && (v.x = -1))
		while (v.x++ < env->map.width)
		{
			if (grid_get(&env->map, v.x, v.y))
				wfx_frect(env->window,
					VEC2I(v.x * MAP_SCALE + 1, v.y * MAP_SCALE + 1),
					VEC2I(v.x * MAP_SCALE + MAP_SCALE,
						v.y * MAP_SCALE + MAP_SCALE),
					0x00ff00ff);
		}
	draw_rays(env->window, env->hero, env->map, MAP_SCALE);
	draw_hero(env->window, env->hero, MAP_SCALE);
	wfx_blit(env->window);
	wfx_clear_window(env->window);
	return (0);
}
