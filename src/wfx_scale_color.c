/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_scale_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 09:40:29 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 14:03:12 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_math.h"

int	wfx_colour_brightness(int color, double scale)
{
	color = (color & 0xff00ffff) |
		(CLAMP(((int)(((color & 0x00ff0000) >> 16) * scale)), 0, 0xff) << 16);
	color = (color & 0xffff00ff) |
		(CLAMP(((int)(((color & 0x0000ff00) >> 8) * scale)), 0, 0xff) << 8);
	color = (color & 0xffffff00) |
		CLAMP(((int)(((color & 0x000000ff)) * scale)), 0, 0xff);
	return (color);
}
