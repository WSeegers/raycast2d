/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hero.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 12:45:15 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/16 12:57:43 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERO_H
# define HERO_H

# include "libwtcfx.h"

typedef struct	s_hero
{
    t_vec2	pos;
	t_vec2	vel;
}               t_hero;

#endif