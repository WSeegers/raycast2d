/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 14:27:52 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/21 08:35:39 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"
#include "f_math.h"

static void	draw_on_x(t_window *window, t_vec2i p1, t_vec2i p2, int colour)
{
	int		y;
	int		de;
	int		e;
	int		dx;

	y = p1.y;
	dx = p2.x - p1.x;
	de = f_abs(p2.y - p1.y) * 2;
	e = 0;
	while (p1.x < p2.x)
	{
		wfx_set_pixel(window, p1.x++, y, colour);
		e += de;
		if (e > dx)
		{
			y += (p2.y > p1.y) ? 1 : -1;
			e -= dx * 2;
		}
	}
}

static void	draw_on_y(t_window *window, t_vec2i p1, t_vec2i p2, int colour)
{
	int		x;
	int		de;
	int		e;
	int		dy;

	x = p1.x;
	dy = p2.y - p1.y;
	de = f_abs(p2.x - p1.x) * 2;
	e = 0;
	while (p1.y < p2.y)
	{
		wfx_set_pixel(window, x, p1.y++, colour);
		e += de;
		if (e > dy)
		{
			x += (p2.x > p1.x) ? 1 : -1;
			e -= dy * 2;
		}
	}
}

#define OCT_CENT	(0x000)
#define OCT_LEFT	(0xf000)
#define OCT_RIGHT	(0x000f)
#define OCT_BOT		(0x00f0)
#define OCT_TOP		(0x0f00)

typedef int			oct_code;

static int	get_octant(t_window	*window, t_vec2i p)
{
	oct_code	ret;

	ret = 0;
	if (p.x < 0)
		ret |= OCT_LEFT;
	else if	(p.x > window->width)
		ret |= OCT_RIGHT;
	if	(p.y < 0)
		ret	|= OCT_TOP;
	else if (p.y > window->height)
		ret |= OCT_BOT;
	return (ret);
}

#include <stdlib.h>

int		clip(t_window *window, t_vec2i *p1, t_vec2i *p2)
{
	oct_code	p1_oct;
	oct_code	p2_oct;
	oct_code	check;
	t_vec2		v1;
	t_vec2		v2;
	t_vec2i		temp;

	v1 = VEC2_TO_F((*p1));
	v2 = VEC2_TO_F((*p2));
	while (1)
	{
		p1_oct = get_octant(window, *p1);
		p2_oct = get_octant(window, *p2);
		if (!(p1_oct | p2_oct))
			return (0);
		if (p1_oct & p2_oct)
			return (1);
		check = p1_oct ? p1_oct : p2_oct;
		if (check & OCT_BOT)
		{
			temp.x = v1.x + (v2.x - v1.x) * (-v1.y + (window->height)) / (v2.y - v1.y);
			temp.y = window->height;
		}
		else if (check & OCT_TOP)
		{
			temp.x = v1.x + (v2.x - v1.x) * (-v1.y) / (v2.y - v1.y);
			temp.y = 0;
		}
		else if (check & OCT_RIGHT)
		{
			temp.y = v1.y + (v2.y - v1.y) * (-v1.x + (window->width)) / (v2.x - v1.x);
			temp.x = window->width;
		}
		else if (check & OCT_LEFT)
		{
			temp.y = v1.y + (v2.y - v1.y) * (-v1.x) / (v2.x - v1.x);
			temp.x = 0;
		}
		if (check == p1_oct)
			*p1 = temp;
		else
			*p2 = temp;
	}
}

void		wfx_line(t_window *window, t_vec2i p1, t_vec2i p2, int colour)
{
	t_vec2i	temp;
	double	m;

	if (clip(window, &p1, &p2))
		return;
	if (p1.x == p2.x && p1.y == p2.y)
		wfx_set_pixel(window, p1.x, p1.y, colour);
	m =	(double)(p2.y - p1.y) / (double)(p2.x - p1.x);
	if (fabs(m) <= 1)
	{
		if (p1.x > p2.x)
			draw_on_x(window, p2, p1, colour);
		draw_on_x(window, p1, p2, colour);
	}
	else  
	{
		if (p1.y > p2.y)
			draw_on_y(window, p2, p1, colour);
		draw_on_y(window, p1, p2, colour);
	}
}
