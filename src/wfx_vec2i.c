/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_vec2i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 21:29:19 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/15 21:33:27 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

t_vec2i		*vec2i_create()
{
	return (f_memalloc(sizeof(t_vec2i)));
}

void		vec2i_init(t_vec2i *v2, int x, int y)
{
	v2->x = x;
	v2->y = y;
}
