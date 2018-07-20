/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 08:35:53 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/19 21:38:24 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

//remove stdio
# include <stdio.h>
# include <stdlib.h>
# include "libwtcfx.h"
# include "hero.h"
# include "wfx_mac_keys.h"

typedef struct	s_env
{
	t_window	*window;
	t_hero		*hero;
	t_grid		map;
	t_state		game_state;
}				t_env;

int 	game_loop(void *param);
int		draw_map(void *parm);

#endif