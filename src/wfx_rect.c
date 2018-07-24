/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_rect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 11:22:11 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 14:07:43 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

void	wfx_frect(t_window *window, t_vec2i p1, t_vec2i p2, int colour)
{
	t_vec2i start;
	t_vec2i end;
	t_vec2i count;

	start.x = MIN(p1.x, p2.x);
	end.x = MAX(p1.x, p2.x);
	start.y = MIN(p1.y, p2.y);
	end.y = MAX(p1.y, p2.y);
	count.y = start.y;
	while (count.y < end.y)
	{
		count.x = start.x;
		while (count.x < end.x)
			wfx_set_pixel(window, count.x++, count.y, colour);
		count.y++;
	}
}

void	wfx_rect(t_window *window, t_vec2i p1, t_vec2i p2, int colour)
{
	t_vec2i count;

	count.x = p2.x;
	count.y = p1.y;
	wfx_line(window, p1, count, colour);
	wfx_line(window, p2, count, colour);
	count.x = p1.x;
	count.y = p2.y;
	wfx_line(window, p1, count, colour);
	wfx_line(window, p2, count, colour);
}
