/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_wolf_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 13:37:03 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/25 10:19:30 by wseegers         ###   ########.fr       */
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

static void	draw_wall(t_env *env, t_hit_report hr, t_vec2i top, t_vec2i bot)
{
	t_vec2i	p;
	int		y;
	int		color;
	t_image *image;
	double	weight;

	image = env->wolf3d_textures[hr.value % 8];
	weight = 1 - (hr.hit_dist / VEIW_DISTANCE);
	p.x = (int)LERP(0.0, (double)image->width, hr.offset);
	y = 0;
	while (top.y + y < 0)
		y = -top.y;
	while (top.y + y < bot.y)
	{
		hr.offset = (double)y / (double)(bot.y - top.y);
		p.y = (int)LERP(0.0, (double)image->height, hr.offset);
		color = GET_IMAGE_PIXEL(image, p.x, p.y);
		set_pixel_pov(env->window, top.x, top.y + y, color);
		y++;
		if (top.y + y > POV_WIDTH)
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
		pov_line(env->window, VEC2I(POV_WIDTH - x, 0), p1, 0x00cbd88f);
		pov_line(env->window, p2, VEC2I(POV_WIDTH - x,
			POV_HEIGHT - 1), 0x00546d6d);
	}
}

int			fp_wolf_loop(void *param)
{
	t_env			*env;

	env = (t_env*)param;
	update_hero(env->hero, env->map);
	draw_first_person(env);
	draw_ui(env);
	wfx_blit(env->window);
	return (0);
}
