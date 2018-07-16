/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_blit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 19:47:41 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/15 22:05:42 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

//TODO: remove debug
#include <stdio.h>

void		wfx_blit(t_mlx mlx, t_window *window)
{
	double frame_dif;
	struct timespec wait;

	window->frame_count++;
	f_swapptr((void**)&window->front, (void**)&window->back);
	frame_dif =  (double)(clock() - window->last_blit) / CLOCKS_PER_SEC;
	if (frame_dif < 0.0166666666666666667)
	{
		wait.tv_sec = 0;
		wait.tv_nsec = (long)((0.0166666666666666667 - frame_dif) * 1000000000);
		nanosleep(&wait, NULL);
	}
	mlx_put_image_to_window(mlx, window->ptr, window->front->ptr, 0, 0);
	window->last_blit = clock();
	if (!(window->frame_count % 100))
	{
		printf("frames: %lu   fps: %f\n",window->frame_count, 1 / (((double)(clock() - window->last_fps) / 100) / CLOCKS_PER_SEC));
		window->last_fps = clock();
	}
}