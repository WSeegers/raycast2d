/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_dda.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 00:44:01 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/18 01:23:33 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WFX_DDA
# define WFX_DDA

# include "libwtcfx.h"

# define HIT_NORTH	1
# define HIT_SOUTH	2
# define HIT_WEST	3
# define HIT_EAST	4

typedef struct	s_hit_report
{
	double		hit_dist;
	t_vec2i		cell;
	int			side;
	int			value;
}				t_hit_report;

typedef struct	s_dda
{
	t_vec2	d;
	t_vec2	side;
	t_vec2i cell;
	t_vec2i hitx;
	t_vec2i hity;
	t_vec2i	step;
	int		yhit;
	double 	hitdist;
}				t_dda;

t_hit_report	wfx_dda(t_vec2 start, t_vec2 direction, t_grid map);

#endif