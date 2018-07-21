/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 21:31:18 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/21 22:08:35 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"
#include "wolf3d.h"
#include "dda.h"

void	draw_floor(t_window *window, t_image_set images, t_hit_report hr, t_vec2i bot, t_hero *hero)
{
	t_vec2i	p;
	t_vec2	current;
	double	weight;
	int		color;
	t_image	*image;

	while (++bot.y < window->width)
	{
		double c_dist = window->height / (2.0 * bot.y - window->height);
		weight =  c_dist / hr.hit_dist;
		current.x = weight * hr.pos.x + (1.0 - weight) * hero->pos.x;
		current.y = weight * hr.pos.y + (1.0 - weight) * hero->pos.y;
		image = images[0];
		p.x = (int)(current.x * image->width) % image->width;
		p.y = (int)(current.y * image->height) % image->height;
		color = GET_IMAGE_PIXEL(image, p.x, p.y);
		wfx_set_pixel(window, bot.x, bot.y, color);
		image = images[1];
		p.x = (int)(current.x * image->width) % image->width;
		p.y = (int)(current.y * image->height) % image->height;
		color = GET_IMAGE_PIXEL(image, p.x, p.y);
		wfx_set_pixel(window, bot.x, window->height - bot.y, color);
	}
}

void	draw_wall(t_window *window, t_image *image, double offset, t_vec2i top, t_vec2i bot)
{
	t_vec2i	p;
	int		y;
	int 	color;

	p.x = (int)LERP(0.0, (double)image->width, offset);
	y = 0;
	while (top.y + y < 0)
		y = -top.y;
	while (top.y + y < bot.y)
	{
		offset = (double)y / (double)(bot.y - top.y);
		p.y = (int)LERP(0.0, (double)image->height, offset);
		color = GET_IMAGE_PIXEL(image, p.x, p.y);
		wfx_set_pixel(window, top.x, top.y + y, color);
		y++;
		if (top.y + y > window->width)
			return ;
	}
	
}

static void	draw_first_person2(t_env *env)
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
		p1 = VEC2I(env->window->width - x, (env->window->height / 2) - (1 / hr.hit_dist * env->window->height / 2));
		p2 = VEC2I(env->window->width - x, (env->window->height / 2) + (1 / hr.hit_dist * env->window->height / 2));
		draw_wall(env->window, env->hd_textures[2], hr.offset, p1, p2);
		draw_floor(env->window, env->hd_textures, hr, p2, env->hero);
	}
	wfx_blit(env->window);
}

static void	draw_first_person(t_env *env)
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

int 		fp_basic(void *param)
{
	t_env			*env;

	env = (t_env*)param;
	update_hero(env->hero, env->map);
	draw_first_person2(env);
	return (0);
}