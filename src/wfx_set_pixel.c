/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_set_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 19:53:56 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 14:03:23 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

void		wfx_set_pixel(t_window *window, int x, int y, int col)
{
	if (x < 0 || y < 0 || x >= window->width || y >= window->height)
		return ;
	SET_IMAGE_PIXEL(window->back, x, y, col);
}
