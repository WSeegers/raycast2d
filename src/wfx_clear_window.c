/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_clear_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 21:34:40 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 14:09:42 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

void	wfx_clear_window(t_window *window)
{
	int height;
	int width;
	int y;
	int x;

	height = window->height;
	width = window->width;
	y = -1;
	while (++y < height && (x = -1))
		while (++x < width)
		{
			wfx_set_pixel(window, x, y, 0x0);
		}
}
