/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 18:12:48 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/18 01:00:50 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"
#include "hero.h"

char MAP[24][24];

void	draw_ray(t_window *window, t_hero *hero, t_grid map, double scale)
{
	t_vec2	d;
	t_vec2	side;
	t_vec2	ray;
	t_vec2i cell;
	t_vec2i hitx;
	t_vec2i hity;
	t_vec2i	step;

	d.x = CLAMP(fabs(1.0 / hero->direction.x), 1, 100); // needs to be clamped to a view distance
	d.y = CLAMP(fabs(1.0 / hero->direction.y), 1, 100);
	cell = VEC2_TO_I(hero->pos);
	if (hero->direction.x < 0)
    {
      step.x = -1;
      side.x = (hero->pos.x - cell.x) * d.x;
    }
    else
    {
      step.x = 1;
      side.x = (cell.x + 1.0 - hero->pos.x) * d.x;
    }
    if (hero->direction.y < 0)
    {
      step.y = -1;
      side.y = (hero->pos.y - cell.y) * d.y;
    }
    else
    {
      step.y = 1;
      side.y = (cell.y + 1.0 - hero->pos.y) * d.y;
    }
	int yhit;
    while (!GRID_GET(map, cell.x, cell.y))
    {
    	if (side.x < side.y)
    	{
    	  side.x += d.x;
    	  cell.x += step.x;
    	  yhit = 0;
    	}
    	else
    	{
    	  side.y += d.y;
    	  cell.y += step.y;
    	  yhit = 1;
    	}
    }
	double hitdist;
	if (!yhit)
	{
		hitdist = (cell.x - hero->pos.x + (1 - step.x) / 2) / hero->direction.x;
		hitx = VEC2_TO_I(vec2_scale(vec2_add(hero->pos, vec2_scale(hero->direction, hitdist)), scale));
		wfx_fcircle(window, &hitx, 5, 0x0000ffff);
		wfx_line(window, &VEC2_TO_I(vec2_scale(hero->pos, scale)), &hitx, 0x0000ffff);
	}
	else
	{
		hitdist = (cell.y - hero->pos.y + (1 - step.y) / 2) / hero->direction.y;
		hity = VEC2_TO_I(vec2_scale(vec2_add(hero->pos, vec2_scale(hero->direction, hitdist)), scale));
		wfx_fcircle(window, &hity, 5, 0x0000ffff);
		wfx_line(window, &VEC2_TO_I(vec2_scale(hero->pos, scale)), &hity, 0x0000ffff);
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