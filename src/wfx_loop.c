/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:34:53 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/17 15:05:12 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

int		wfx_std_loop(t_window *window)
{
	window->update(window->param);
	window->draw(window->param);
	wfx_blit(window);
	return (0);
}

void	wfx_loop_hook(t_window *window, int (*f)(void*), void *param)
{
	mlx_loop_hook(window->mlx, f, param);
}

void	wfx_start(t_window *window)
{
	mlx_loop(window->mlx);
}