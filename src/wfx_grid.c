/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 12:02:38 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/19 19:58:27 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

void		wfx_grid(t_window *window, t_vec2i origin, int cols, int rows, int size)
{
    t_vec2i track;
    int i;

    track = origin;
    track.x += (size * cols);
    
    i = -1;
    while (++i <= rows)
        wfx_line(window,
            VEC2I(origin.x, origin.y + (i * size)),
            VEC2I(track.x, track.y + (i * size)),
            0x00ffffff);

    track = origin;
    track.y += (size * rows);
    
    i = -1;
    while (++i <= cols)
        wfx_line(window,
            VEC2I(origin.x + (i * size), origin.y),
            VEC2I(track.x + (i * size), track.y),
            0x00ffffff);
}