/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_vec2i_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 11:12:48 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 14:05:20 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

t_vec2i		vec2i_add(t_vec2i v1, t_vec2i v2)
{
	return (VEC2I(v1.x + v2.x, v1.y + v2.y));
}

t_vec2i		vec2i_sub(t_vec2i v1, t_vec2i v2)
{
	return (VEC2I(v1.x - v2.x, v1.y - v2.y));
}

t_vec2i		vec2i_scale(t_vec2i v1, int scalar)
{
	return (VEC2I(v1.x * scalar, v1.y * scalar));
}
