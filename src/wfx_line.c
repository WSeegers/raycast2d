/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 14:27:52 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/19 19:53:24 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"
#include "f_math.h"

static void	draw_vert(t_window *window, t_vec2i p1, t_vec2i p2, int colour)
{
	int		start;
	int		end;

	start = f_min(p1.y, p2.y) - 1;
	end = f_max(p1.y, p2.y);
	while (++start < end)
		wfx_set_pixel(window, p1.x, start, colour);
}

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

void		swap_points(t_vec2i *v1, t_vec2i *v2)
{
	t_vec2i temp;

	temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}

void		wfx_line(t_window *window, t_vec2i p1, t_vec2i p2, int colour)
{
	int		dx;
	int		dy;
	double	m;

	if (p1.x == p2.x)
	{
		if (p1.y == p2.y)
			wfx_set_pixel(window, p1.x, p1.y, colour);
		else
			draw_vert(window, p1, p2, colour);
		return ;
	}
	if (p1.x > p2.x)
		swap_points(&p1, &p2);
	m =	(double)(dy = p2.y - p1.y) / (double)(dx = p2.x - p1.x);
	if (fabs(m) <= 1)
		draw_on_x(window, p1, p2, colour);
	else
	{
		if (p1.y > p2.y)
			draw_on_y(window, p2, p1, colour);
		draw_on_y(window, p1, p2, colour);
	}
}
