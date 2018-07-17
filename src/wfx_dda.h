/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_dda.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 00:44:01 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/18 00:45:50 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WFX_DDA
# define WFX_DDA

# include "libwtcfx.h"

typedef struct	s_hit_report
{
	double	hit_dist;
	int		value;
	int		boundry;
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

double		wfx_dda(t_vec2 start, t_vec2 direction, t_grid map);

#endif