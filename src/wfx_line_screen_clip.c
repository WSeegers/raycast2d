/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_line_screen_clip.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 10:35:10 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 13:51:16 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wfx_line.h"

static int		get_octant(t_window *window, t_vec2i p)
{
	t_oct_code	ret;

	ret = 0;
	if (p.x < 0)
		ret |= OCT_LEFT;
	else if (p.x > window->width)
		ret |= OCT_RIGHT;
	if (p.y < 0)
		ret |= OCT_TOP;
	else if (p.y > window->height)
		ret |= OCT_BOT;
	return (ret);
}

static t_vec2i	get_clip(t_vec2i window, t_vec2 v1, t_vec2 v2, t_oct_code check)
{
	t_vec2i		temp;

	if (check & OCT_BOT)
	{
		temp.x = v1.x + (v2.x - v1.x) * (-v1.y + (window.y)) / (v2.y - v1.y);
		temp.y = window.y;
	}
	else if (check & OCT_TOP)
	{
		temp.x = v1.x + (v2.x - v1.x) * (-v1.y) / (v2.y - v1.y);
		temp.y = 0;
	}
	else if (check & OCT_RIGHT)
	{
		temp.y = v1.y + (v2.y - v1.y) * (-v1.x + (window.x)) / (v2.x - v1.x);
		temp.x = window.x;
	}
	else if (check & OCT_LEFT)
	{
		temp.y = v1.y + (v2.y - v1.y) * (-v1.x) / (v2.x - v1.x);
		temp.x = 0;
	}
	return (temp);
}

int			clip(t_window *window, t_vec2i *p1, t_vec2i *p2)
{
	t_oct_code	p_oct[2];
	t_oct_code	check;
	t_vec2		v1;
	t_vec2		v2;
	t_vec2i		temp;

	v1 = VEC2_TO_F((*p1));
	v2 = VEC2_TO_F((*p2));
	while (1)
	{
		p_oct[0] = get_octant(window, *p1);
		p_oct[1] = get_octant(window, *p2);
		if (!(p_oct[0] | p_oct[1]))
			return (0);
		if (p_oct[0] & p_oct[1])
			return (1);
		check = p_oct[0] ? p_oct[0] : p_oct[1];
		temp = get_clip(VEC2I(window->width, window->height),
			VEC2_TO_F((*p1)), VEC2_TO_F((*p2)), check);
		if (check == p_oct[0])
			*p1 = temp;
		else
			*p2 = temp;
	}
}
