/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 08:32:23 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/23 08:45:41 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"
#include "wolf3d.h"

#define HERO_SSPD 0.1

int 		fp_texture_loop(void *param);

int	key_release(int key, void *p)
{
	t_env	*env = (t_env*)p;

	//printf("key: %d\n", key);
	if (key == KEY_LEFT)
		env->hero->rotation += HERO_ROT;
	else if (key == KEY_W)
		env->hero->velocity -= HERO_SPD;
	else if (key == KEY_RIGHT)
		env->hero->rotation -= HERO_ROT;
	else if (key == KEY_S)
		env->hero->velocity = 0;
	else if (key == KEY_A)
		env->hero->strafe -= HERO_SSPD;
	else if (key == KEY_D)
		env->hero->strafe += HERO_SSPD;
	else if (key == KEY_TAB)
		wfx_loop_hook(env->window, env->game_state.loop, p);
	return (0);
}

int	key_press(int key, void *p)
{
	t_env	*env = (t_env*)p;

	//printf("key: %d\n", key);
	if (key == 53)
		exit(0);
	else if (key == KEY_LEFT)
		env->hero->rotation -= HERO_ROT;
	else if (key == KEY_W)
		env->hero->velocity += HERO_SPD;
	else if (key == KEY_RIGHT)
		env->hero->rotation += HERO_ROT;
	else if (key == KEY_S)
		env->hero->velocity -= HERO_SPD;
	else if (key == KEY_A)
		env->hero->strafe += HERO_SSPD;
	else if (key == KEY_D)
		env->hero->strafe -= HERO_SSPD;
	else if (key == KEY_TAB)
		wfx_loop_hook(env->window, fp_texture_loop, p);
	return (0);
}