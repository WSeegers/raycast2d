/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_vec2_op1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 11:12:48 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 14:04:13 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

t_vec2		vec2_add(t_vec2 v1, t_vec2 v2)
{
	return (VEC2(v1.x + v2.x, v1.y + v2.y));
}

t_vec2		vec2_sub(t_vec2 v1, t_vec2 v2)
{
	return (VEC2(v1.x - v2.x, v1.y - v2.y));
}

t_vec2		vec2_scale(t_vec2 v1, double scalar)
{
	return (VEC2(v1.x * scalar, v1.y * scalar));
}

double		vec2_len(t_vec2 v)
{
	return (sqrt((v.x * v.x + v.y * v.y)));
}

t_vec2		vec2_norm(t_vec2 v)
{
	return (vec2_scale(v, 1 / vec2_len(v)));
}
