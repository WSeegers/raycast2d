/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hero.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 12:45:15 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/19 22:02:20 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERO_H
# define HERO_H

# include "libwtcfx.h"

# define HERO_COL	0x00ffffff
# define HERO_SIZE	10
# define HERO_SPD	0.1
# define HERO_ROT	0.02 * M_PI

typedef struct	s_hero
{
    t_vec2	pos;
	double	velocity;
	t_vec2	direction;
	double 	rotation;
	t_vec2	plane;
}               t_hero;

void	draw_hero(t_window *window, t_hero *hero, double scale);
void	update_hero(t_hero *hero, t_grid map);
void	rotate_hero(t_hero *hero, double rad);

int		key_release(int key, void *p);
int		key_press(int key, void *p);

#endif