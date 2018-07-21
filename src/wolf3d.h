/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 08:35:53 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/21 23:29:02 by wseegers         ###   ########.fr       */
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

# define WIDTH (640)
# define HEIGHT (400)

# define MAX_TEXTURE (8)

typedef	t_image *t_image_set[8];

typedef struct	s_env
{
	t_window	*window;
	t_hero		*hero;
	t_grid		map;
	t_state		game_state;
	t_image_set	hd_textures;
}				t_env;

int 	fp_basic(void *param);
int		draw_map(void *parm);

#endif