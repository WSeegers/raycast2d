/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_vec2_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 11:12:48 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/16 12:56:21 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

void		vec2_add(t_vec2 *v1, t_vec2 *v2)
{
    v1->x += v2->x;
    v1->y += v2->y;
}

void		vec2_sub(t_vec2 *v1, t_vec2 *v2)
{
    v1->x -= v2->x;
    v1->y -= v2->y;
}

void		vec2_scale(t_vec2 *v1, double scalar)
{
    v1->x *= scalar;
    v1->y *= scalar;
}

double		vec2_len(t_vec2 *v)
{
    return (sqrt(v->x * v->x + v->y * v->y));
}

void		vec2_norm(t_vec2 *v)
{
	double len;

	vec2_scale(v, vec2_len(v));
}