/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_blit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 19:47:41 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/17 15:02:19 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

void		wfx_blit(t_window *window)
{
	double frame_dif;
	struct timespec wait;

	window->frame_count++;
	f_swapptr((void**)&window->front, (void**)&window->back);
	// frame_dif =  (double)(clock() - window->last_blit) / CLOCKS_PER_SEC;
	// if (frame_dif < 1.0 / MAX_FPS)
	// {
	// 	wait.tv_sec = 0;
	// 	wait.tv_nsec = (long)((1.0 / MAX_FPS - frame_dif) * 1000000000L);
	// 	nanosleep(&wait, NULL);
	// }
	mlx_put_image_to_window(window->mlx, window->ptr, window->front->ptr, 0, 0);
	window->last_blit = clock();
}