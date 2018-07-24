/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 19:04:09 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 14:12:38 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libwtcfx.h"

t_window	*wfx_create_window(void)
{
	return (f_memalloc(sizeof(t_window)));
}

void		wfx_init_window(t_window *window, int width, int height,
				char *title)
{
	if (!title)
		title = "No Title";
	if (!(window->ptr = mlx_new_window(wfx_get_mlx(), width, height, title)))
		f_eexit(0, "mlx_new_window failed");
	window->mlx = wfx_get_mlx();
	window->width = width;
	window->height = height;
	window->front = wfx_create_image();
	wfx_init_image(window->front, width, height);
	window->back = wfx_create_image();
	wfx_init_image(window->back, width, height);
	window->frame_count = 0;
	window->resx = 0;
	window->resy = 0;
}

void		wfx_destroy_window(t_window *window)
{
	if (!window)
		return ;
	wfx_destroy_image(window->front);
	window->front = NULL;
	wfx_destroy_image(window->back);
	window->back = NULL;
	mlx_destroy_window(wfx_create_window(), window->ptr);
}

void		wfx_image_to_window(t_window *window, t_image *image, t_vec2i pos)
{
	wfx_image_to_image(window->back, image, pos);
}
