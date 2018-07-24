/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:34:53 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 13:51:46 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

void	wfx_expose_hook(t_window *window, int (*f)(void*), void *param)
{
	mlx_expose_hook(window->ptr, f, param);
}

void	wfx_loop_hook(t_window *window, int (*f)(void*), void *param)
{
	mlx_loop_hook(window->mlx, f, param);
}

void	wfx_start(t_window *window)
{
	mlx_loop(window->mlx);
}
