/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 13:07:22 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/19 19:56:40 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

static void	set_oct(t_window *window, t_vec2i v, t_vec2i offs, int colour)
{
	wfx_set_pixel(window, v.x + offs.x, v.y + offs.y, colour);
	wfx_set_pixel(window, v.x - offs.x, v.y + offs.y, colour);
	wfx_set_pixel(window, v.x + offs.y, v.y + offs.x, colour);
	wfx_set_pixel(window, v.x - offs.y, v.y + offs.x, colour);
	wfx_set_pixel(window, v.x - offs.y, v.y - offs.x, colour);
	wfx_set_pixel(window, v.x + offs.y, v.y - offs.x, colour);
	wfx_set_pixel(window, v.x + offs.x, v.y - offs.y, colour);
	wfx_set_pixel(window, v.x - offs.x, v.y - offs.y, colour);
}

void		wfx_circle(t_window *window, t_vec2i v, int radius, int colour)
{
	t_vec2i p;
	t_vec2i	d;
	int		err;

	p.x = radius - 1;
	p.y = 0;
	d.x = 1;
	d.y = 1;
	err = d.x - (radius << 1);
	while (p.x >= p.y)
	{
		set_oct(window, v, p, colour);
		if (err <= 0)
		{
			p.y++;
			err += d.y;
			d.y += 2;
			continue;
		}
		p.x--;
		d.x += 2;
		err += d.x - (radius << 1);
	}
}

static void	fill_oct(t_window *window, t_vec2i v, t_vec2i offs, int colour)
{
	wfx_line(window, VEC2I(v.x + offs.x, v.y + offs.y),
				VEC2I(v.x - offs.x, v.y + offs.y), colour);
	wfx_line(window, VEC2I(v.x + offs.y, v.y + offs.x),
				VEC2I(v.x - offs.y, v.y + offs.x), colour);
	wfx_line(window, VEC2I(v.x - offs.y, v.y - offs.x),
				VEC2I(v.x + offs.y, v.y - offs.x), colour);
	wfx_line(window, VEC2I(v.x + offs.x, v.y - offs.y),
				VEC2I(v.x - offs.x, v.y - offs.y), colour);
}

void		wfx_fcircle(t_window *window, t_vec2i v, int radius, int colour)
{
	t_vec2i p;
	t_vec2i	d;
	int		err;

	p.x = radius - 1;
	p.y = 0;
	d.x = 1;
	d.y = 1;
	err = d.x - (radius << 1);
	while (p.x >= p.y)
	{
		fill_oct(window, v, p, colour);
		if (err <= 0)
		{
			p.y++;
			err += d.y;
			d.y += 2;
			continue;
		}
		p.x--;
		d.x += 2;
		err += d.x - (radius << 1);
	}
}
