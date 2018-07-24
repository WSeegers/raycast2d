/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel_pov.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:24:43 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 12:20:34 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	pov_line(t_window *window, t_vec2i p1, t_vec2i p2, int colour)
{
	wfx_line(window, VEC2I(p1.x + POV_OFFSETX, p1.y + POV_OFFSETY),
		VEC2I(p2.x + POV_OFFSETX, p2.y + POV_OFFSETY), colour);
}

void	set_pixel_pov(t_window *window, int x, int y, int col)
{
	wfx_set_pixel(window, x + POV_OFFSETX, y + POV_OFFSETY, col);
}
