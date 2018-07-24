/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_vec2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 21:29:19 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 14:05:06 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

t_vec2		*vec2_create(void)
{
	return (f_memalloc(sizeof(t_vec2)));
}

void		vec2_init(t_vec2 *v2, double x, double y)
{
	v2->x = x;
	v2->y = y;
}

t_vec2		*vec2_copy(t_vec2 *v)
{
	t_vec2	*ret;

	ret = vec2_create();
	vec2_init(ret, v->x, v->y);
	return (ret);
}
