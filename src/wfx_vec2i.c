/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_vec2i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 21:29:19 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 14:09:59 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

t_vec2i		*vec2i_create(void)
{
	return (f_memalloc(sizeof(t_vec2i)));
}

void		vec2i_init(t_vec2i *v2, int x, int y)
{
	v2->x = x;
	v2->y = y;
}

t_vec2i		*vec2i_copy(t_vec2i *v)
{
	t_vec2i	*ret;

	ret = vec2i_create();
	vec2i_init(ret, v->x, v->y);
	return (ret);
}
