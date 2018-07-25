/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_texture_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 08:42:56 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/25 08:21:11 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "dda.h"

static int	get_shaded_pixel(t_window *window, t_image *image,
													t_vec2i p, double weight)
{
	int color;

	if (weight < 1)
	{
		color = GET_IMAGE_PIXEL(image, p.x, p.y);
		return (wfx_colour_brightness(color, weight));
	}
	else
		return (0x0);
}

static void	draw_ceil_floor(t_env *env, t_hit_report hr, t_vec2i bot)
{
	t_vec2i	p[2];
	t_vec2	current;
	double	weight[2];
	int		color[2];
	t_image	*image[2];

	while (++bot.y < POV_WIDTH)
	{
		weight[0] = POV_HEIGHT / (2.0 * bot.y - POV_HEIGHT);
		weight[1] = weight[0] / hr.hit_dist;
		current.x = weight[1] * hr.pos.x + (1.0 - weight[1]) * env->hero->pos.x;
		current.y = weight[1] * hr.pos.y + (1.0 - weight[1]) * env->hero->pos.y;
		image[0] = env->hd_textures[0];
		p[0].x = (int)(current.x * image[0]->width) % image[0]->width;
		p[0].y = (int)(current.y * image[0]->height) % image[0]->height;
		image[1] = env->hd_textures[1];
		p[1].x = (int)(current.x * image[1]->width) % image[1]->width;
		p[1].y = (int)(current.y * image[1]->height) % image[1]->height;
		weight[1] = 1 - (weight[0] / VEIW_DISTANCE);
		color[0] = get_shaded_pixel(env->window, image[0], p[0], weight[1]);
		color[1] = get_shaded_pixel(env->window, image[1], p[0], weight[1]);
		set_pixel_pov(env->window, bot.x, bot.y, color[0]);
		set_pixel_pov(env->window, bot.x,
			POV_HEIGHT - bot.y, color[1]);
	}
}

static void	draw_wall(t_env *env, t_hit_report hr, t_vec2i top, t_vec2i bot)
{
	t_vec2i	p;
	int		y;
	int		color;
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
		color = get_shaded_pixel(env->window, image, p, weight);
		set_pixel_pov(env->window, top.x, top.y + y, color);
		y++;
		if (top.y + y > POV_WIDTH)
			return ;
	}
	set_pixel_pov(env->window, top.x, top.y + y, color);
}

static void	draw_first_person(t_env *env)
{
	t_hit_report	hr;
	t_vec2i			p1;
	t_vec2i			p2;
	t_vec2			ray;
	int				x;

	x = -1;
	while (++x < POV_WIDTH)
	{
		ray = vec2_add(env->hero->direction,
			vec2_scale(env->hero->plane, 2 *
				x / (double)POV_WIDTH - 1));
		hr = dda(env->hero->pos, ray, env->map);
		p1 = VEC2I(POV_WIDTH - x,
			(POV_HEIGHT / 2) -
				(1 / hr.hit_dist * POV_HEIGHT / 2));
		p2 = VEC2I(POV_WIDTH - x,
			(POV_HEIGHT / 2) +
				(1 / hr.hit_dist * POV_HEIGHT / 2));
		draw_wall(env, hr, p1, p2);
		draw_ceil_floor(env, hr, p2);
	}
}

int			fp_texture_loop(void *param)
{
	t_env			*env;

	env = (t_env*)param;
	update_hero(env->hero, env->map);
	draw_first_person(env);
	draw_ui(env);
	wfx_blit(env->window);
	return (0);
}
