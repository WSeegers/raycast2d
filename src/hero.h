/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hero.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 12:45:15 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/18 00:57:31 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERO_H
# define HERO_H

# include "libwtcfx.h"

# define HERO_COL 0x00ffffff
# define HERO_SIZE 10

typedef struct	s_hero
{
    t_vec2	pos;
	double	velocity;
	t_vec2	direction;
	double 	rotation;
	t_vec2	plane;
}               t_hero;

void	draw_hero(t_window *window, t_hero *hero, double scale);
void	update_hero(t_hero *hero);
void	rotate_hero(t_hero *hero, double rad);

void	draw_camera(t_window *window, t_hero *hero, t_grid map, double scale);
t_hero	scale_hero(t_hero hero, double scale);


#endif