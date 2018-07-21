/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 10:19:55 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/21 10:37:17 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WFX_LINE_H
# define WFX_LINE_H

# include "libwtcfx.h"
# include "f_math.h"

#define OCT_CENT	(0x000)
#define OCT_LEFT	(0xf000)
#define OCT_RIGHT	(0x000f)
#define OCT_BOT		(0x00f0)
#define OCT_TOP		(0x0f00)

typedef int			oct_code;

int		clip(t_window *window, t_vec2i *p1, t_vec2i *p2);

#endif