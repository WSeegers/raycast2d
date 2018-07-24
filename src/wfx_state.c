/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 04:36:40 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 14:03:51 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"
#include "f_memory.h"

void	wfx_init_state(t_state *state)
{
	f_bzero(state, sizeof(*state));
}

void	invoke_state(t_window *window, t_state *state, void *param)
{
	if (state->loop)
		wfx_loop_hook(window, state->loop, param);
	else
		wfx_loop_hook(window, NULL, param);
	if (state->key_down)
		wfx_key_press_hook(window, state->key_down, param);
	else
		wfx_key_press_hook(window, NULL, NULL);
	if (state->key_up)
		wfx_key_release_hook(window, state->key_up, param);
	else
		wfx_key_release_hook(window, NULL, NULL);
	if (state->mouse_down)
		wfx_mouse_press_hook(window, state->mouse_down, param);
	else
		wfx_mouse_press_hook(window, NULL, NULL);
	if (state->mouse_up)
		wfx_mouse_release_hook(window, state->mouse_up, param);
	else
		wfx_mouse_release_hook(window, NULL, NULL);
	if (state->mouse_move)
		wfx_motion_hook(window, state->mouse_move, param);
	else
		wfx_motion_hook(window, NULL, NULL);
}
