/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_key_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 13:54:19 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 12:29:42 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

void	wfx_key_press_hook(t_window *window, int (*f)(int, void*), void *param)
{
	mlx_hook(window->ptr, 2, 0, f, param);
}

void	wfx_key_release_hook(t_window *window, int (*f)(int, void*),
			void *param)
{
	mlx_hook(window->ptr, 3, 0, f, param);
	mlx_do_key_autorepeatoff(window->mlx);
}

void	wfx_exit_hook(t_window *window, int (*f)(void*), void *param)
{
	mlx_hook(window->ptr, 17, 0, f, param);
}
