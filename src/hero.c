/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 12:36:11 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/17 19:23:19 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"
#include "hero.h"

void	rotate_hero(t_hero *hero, double rad)
{
	hero->direction = vec2_rotate(hero->direction, rad);
	hero->plane = vec2_rotate(hero->plane, rad);
}

void	update_hero(t_hero *hero)
{
	rotate_hero(hero, hero->rotation);
	hero->pos = vec2_add(hero->pos, vec2_scale(hero->direction, hero->velocity));
}

t_hero	scale_hero(t_hero hero, double scale)
{
	hero.plane = vec2_scale(hero.plane, scale);
	hero.pos = vec2_scale(hero.pos, scale);
	hero.direction = vec2_scale(hero.direction, scale);
	return (hero);
}

void	draw_hero(t_window *window, t_hero *hero, double scale)
{
	t_vec2i	heading;
	t_hero sc_hero;

	sc_hero = scale_hero(*hero, scale);
	wfx_fcircle(window, &VEC2_TO_I(sc_hero.pos), HERO_SIZE, HERO_COL);
	heading = VEC2_TO_I(vec2_add(sc_hero.pos, sc_hero.direction));
	wfx_line(window, &VEC2_TO_I(sc_hero.pos), &heading, 0x00ff0000);
}