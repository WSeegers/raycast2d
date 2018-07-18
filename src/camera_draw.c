/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 18:12:48 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/18 02:00:06 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"
#include "hero.h"
#include "wfx_dda.h"

void	draw_ray(t_window *window, t_hero *hero, t_grid map, double scale)
{
	t_hit_report	hr;
	t_vec2i			p2;
	t_vec2			ray;

	for	(int x = 0; x < window->width; x++)
	{
		ray = vec2_add(hero->direction, vec2_scale(hero->plane, 2 * x / (double)window->width - 1));
		hr = wfx_dda(hero->pos, ray, map);
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

void	draw_camera(t_window *window, t_hero *hero, t_grid map, double scale)
{
	t_hero sc_hero;

	sc_hero = scale_hero(*hero, scale);
	draw_plane(window, &sc_hero);
	draw_ray(window, hero, map, scale);
}