/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 18:12:48 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/18 12:50:53 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_map.h"

//todo: create appropriatly
#define ROWS 24
#define COLS 24

void	draw_rays(t_window *window, t_hero *hero, t_grid map, double scale)
{
	t_hit_report	hr;
	t_vec2i			p2;
	t_vec2			ray;

	for	(int x = 0; x < window->width; x++)
	{
		ray = vec2_add(hero->direction, vec2_scale(hero->plane, 2 * x / (double)window->width - 1));
		hr = dda(hero->pos, ray, map);
		if (hr.side == HIT_EAST || hr.side == HIT_WEST)
		{
			p2 = VEC2_TO_I(vec2_scale(vec2_add(hero->pos, vec2_scale(ray, hr.hit_dist)), scale));
			wfx_line(window, &VEC2_TO_I(vec2_scale(hero->pos, scale)), &p2, 0x0000ffff);
		}
		else
		{
			p2 = VEC2_TO_I(vec2_scale(vec2_add(hero->pos, vec2_scale(ray, hr.hit_dist)), scale));
			wfx_line(window, &VEC2_TO_I(vec2_scale(hero->pos, scale)), &p2, 0x0000ffff);
		}
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
	wfx_line(window, &VEC2_TO_I(p1), &VEC2_TO_I(p2), 0x0000ffff);
	wfx_line(window, &VEC2_TO_I(p1), &VEC2_TO_I(p3), 0x0000ffff);
}

int		draw_map(void *parm)
{
	t_env *env;

	env = (t_env*)parm;
	update_hero(env->hero);
	for(int y = 0; y < env->map.height; y++)
		for(int x = 0; x < env->map.width; x++)
		{
			if (grid_get(&env->map, x, y))
				wfx_rect(env->window,
					&VEC2I(x * MAP_SCALE + 1, y * MAP_SCALE + 1),
					&VEC2I(x * MAP_SCALE + MAP_SCALE, y * MAP_SCALE + MAP_SCALE),
					0x00ff00ff, true);
		}
	//wfx_grid(env->window, &VEC2I(0, 0), COLS, ROWS, MAP_SCALE);
	draw_rays(env->window, env->hero, env->map, MAP_SCALE);
	draw_hero(env->window, env->hero, MAP_SCALE);
	wfx_blit(env->window);
	wfx_clear_window(env->window);
	return (0);
}

int 	draw_fps(void *parm)
{
	t_env			*env;
	t_hit_report	hr;
	t_vec2i			p1, p2;
	t_vec2			ray;
	int				colour;

	env = (t_env*)parm;
	update_hero(env->hero);
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
			colour = 0x00ffffff;
		p1 = VEC2I(env->window->width - x, (env->window->height / 2) - (1 / hr.hit_dist * env->window->height / 2));
		p2 = VEC2I(env->window->width - x, (env->window->height / 2) + (1 / hr.hit_dist * env->window->height / 2));
		wfx_line(env->window, &VEC2I(env->window->width - x, 0), &p1, 0x00cbd88f);
		wfx_line(env->window, &p1, &p2, colour);
		wfx_line(env->window, &p2, &VEC2I(env->window->width - x, env->window->height - 1), 0x00546d6d);
	}
	wfx_blit(env->window);
	wfx_clear_window(env->window);
	return (0);
}