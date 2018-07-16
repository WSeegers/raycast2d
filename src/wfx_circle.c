/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 13:07:22 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/16 13:14:25 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

void wfx_circle(t_window *window, t_vec2i *v, int radius, int colour)
{
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        wfx_set_pixel(window, v->x + x, v->y + y, colour);
        wfx_set_pixel(window, v->x + y, v->y + x, colour);
        wfx_set_pixel(window, v->x - y, v->y + x, colour);
        wfx_set_pixel(window, v->x - x, v->y + y, colour);
        wfx_set_pixel(window, v->x - x, v->y - y, colour);
        wfx_set_pixel(window, v->x - y, v->y - x, colour);
        wfx_set_pixel(window, v->x + y, v->y - x, colour);
        wfx_set_pixel(window, v->x + x, v->y - y, colour);
        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}