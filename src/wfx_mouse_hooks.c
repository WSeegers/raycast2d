/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_mouse_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 13:45:39 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 13:52:33 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

void	wfx_mouse_press_hook(t_window *window,
	int (*f)(int, int, int, void*), void *param)
{
	mlx_hook(window->ptr, 4, 0, f, param);
}

void	wfx_mouse_release_hook(t_window *window,
	int (*f)(int, int, int, void*), void *param)
{
	mlx_hook(window->ptr, 5, 0, f, param);
}

void	wfx_motion_hook(t_window *window,
	int (*f)(int, int, void*), void *param)
{
	mlx_hook(window->ptr, 6, 0, f, param);
}
