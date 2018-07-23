/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 08:35:53 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/23 15:53:59 by wseegers         ###   ########.fr       */
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
# include "s_vector.h"

# define WIDTH (1000)
# define HEIGHT (600)
# define POV_WIDTH (800)
# define POV_HEIGHT (600)
# define POV_OFFSETX (200)
# define POV_OFFSETY (0)
# define POV_SET (VEC2I(POV_OFFSETX, POV_OFFSETY))
# define VEIW_DISTANCE (3.0)

typedef struct	s_env
{
	t_window	*window;
	t_hero		*hero;
	t_grid		map;
	t_state		game_state;
	t_image		*wolf3d_textures[8];
	t_image		*hd_textures[3];
}				t_env;

int				fp_basic_loop(void *param);
int				draw_map(void *parm);
int				fp_wolf_loop(void *param);
int				fp_texture_loop(void *param);
void			set_pixel_pov(t_window *window, int x, int y, int col);
void			pov_line(t_window *window, t_vec2i p1, t_vec2i p2, int colour);
void			draw_ui(t_env *env);


#endif