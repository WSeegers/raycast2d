/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 08:47:07 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/19 21:41:01 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_MAP_H
# define DRAW_MAP_H

#include "hero.h"
#include "dda.h"
#include "wolf3d.h"

# define MAP_SCALE 20

int		draw_map(void *param);
t_hero	scale_hero(t_hero hero, double scale);

#endif