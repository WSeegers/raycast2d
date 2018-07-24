/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 12:02:38 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 13:56:56 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

void	wfx_grid(t_window *window, t_vec2i origin, t_vec2i grid_size,
	int cell_size)
{
	t_vec2i	track;
	int		i;

	track = origin;
	track.x += (cell_size * grid_size.x);
	i = -1;
	while (++i <= grid_size.y)
		wfx_line(window,
		VEC2I(origin.x, origin.y + (i * cell_size)),
		VEC2I(track.x, track.y + (i * cell_size)),
		0x00ffffff);
	track = origin;
	track.y += (cell_size * grid_size.y);
	i = -1;
	while (++i <= grid_size.x)
		wfx_line(window,
		VEC2I(origin.x + (i * cell_size), origin.y),
		VEC2I(track.x + (i * cell_size), track.y),
		0x00ffffff);
}
