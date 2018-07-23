/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_texture_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 08:42:56 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/23 10:24:10 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"
#include "wolf3d.h"
#include "dda.h"
#include "f_math.h"

static void	draw_floor(t_env *env, t_hit_report hr, t_vec2i bot)
{
	t_vec2i	p;
	t_vec2	current;
	double	weight;
	int		color;
	t_image	*image;

	while (++bot.y < env->window->width)
	{
		double c_dist = env->window->height / (2.0 * bot.y - env->window->height);
		weight =  c_dist / hr.hit_dist;
		current.x = weight * hr.pos.x + (1.0 - weight) * env->hero->pos.x;
		current.y = weight * hr.pos.y + (1.0 - weight) * env->hero->pos.y;
		image = env->hd_textures[0];
		p.x = (int)(current.x * image->width) % image->width;
		p.y = (int)(current.y * image->height) % image->height;
		
		weight = 1 - (c_dist / VEIW_DISTANCE);
		if (weight < 1)
		{
			color = GET_IMAGE_PIXEL(image, p.x, p.y);
			color = wfx_colour_brightness(color, weight);
		}
		else
			color = 0x00000000;
		wfx_set_pixel(env->window, bot.x, bot.y, color);
		image = env->hd_textures[1];
		p.x = (int)(current.x * image->width) % image->width;
		p.y = (int)(current.y * image->height) % image->height;
		color = GET_IMAGE_PIXEL(image, p.x, p.y);
		color = wfx_colour_brightness(color, weight);
		wfx_set_pixel(env->window, bot.x, env->window->height - bot.y, color);
	}
}

static void	draw_wall(t_env *env, t_hit_report hr, t_vec2i top, t_vec2i bot)
{
	t_vec2i	p;
	int		y;
	int 	color;
	t_image *image;
	double	weight;

	image = env->hd_textures[2];
	weight = 1 - (hr.hit_dist / VEIW_DISTANCE);
	p.x = (int)LERP(0.0, (double)image->width, hr.offset);
	y = 0;
	while (top.y + y < 0)
		y = -top.y;
	while (top.y + y < bot.y)
	{
		hr.offset = (double)y / (double)(bot.y - top.y);
		p.y = (int)LERP(0.0, (double)image->height, hr.offset);
		if (hr.hit_dist < VEIW_DISTANCE)
		{
			color = GET_IMAGE_PIXEL(image, p.x, p.y);
			color = wfx_colour_brightness(color, weight);
		}
		else
			color = 0x0;
		wfx_set_pixel(env->window, top.x, top.y + y, color);
		y++;
		if (top.y + y > env->window->width)
			return ;
	}
	wfx_set_pixel(env->window, top.x, top.y + y, color);
	
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
		p1 = VEC2I(env->window->width - x, (env->window->height / 2) - (1 / hr.hit_dist * env->window->height / 2));
		p2 = VEC2I(env->window->width - x, (env->window->height / 2) + (1 / hr.hit_dist * env->window->height / 2));
		draw_wall(env, hr, p1, p2);
		draw_floor(env, hr, p2);
	}
	wfx_blit(env->window);
}

int 		fp_texture_loop(void *param)
{
	t_env			*env;

	env = (t_env*)param;
	update_hero(env->hero, env->map);
	draw_first_person(env);
	return (0);
}