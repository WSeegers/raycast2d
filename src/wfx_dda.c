/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 23:22:41 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/18 01:59:34 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wfx_dda.h"

static void	dda_loop(t_dda *dda, t_grid map)
{
	while (!GRID_GET(map, dda->cell.x, dda->cell.y))
    {
    	if (dda->side.x < dda->side.y)
    	{
    	  dda->side.x += dda->d.x;
    	  dda->cell.x += dda->step.x;
    	  dda->yhit = 0;
    	}
    	else
    	{
    	  dda->side.y += dda->d.y;
    	  dda->cell.y += dda->step.y;
    	  dda->yhit = 1;
    	}
    }
}

void	get_hit_side(t_dda *dda, t_hit_report *hr)
{
	if (dda->yhit)
		hr->side = (dda->step.y == 1) ? HIT_NORTH : HIT_SOUTH;
	else
		hr->side = (dda->step.x == 1) ? HIT_WEST : HIT_EAST;
}

t_hit_report	wfx_dda(t_vec2 start, t_vec2 direction, t_grid map)
{
	t_dda			dda;
	t_hit_report	hr;
	
	dda.d.x = CLAMP(fabs(1.0 / direction.x), 1, 50);
	dda.d.y = CLAMP(fabs(1.0 / direction.y), 1, 50);
	dda.cell = VEC2_TO_I(start);
	if (direction.x < 0 && (dda.step.x = -1))
      dda.side.x = (start.x - dda.cell.x) * dda.d.x;
    else if ((dda.step.x = 1))
      dda.side.x = (dda.cell.x + 1.0 - start.x) * dda.d.x;
    if (direction.y < 0 && (dda.step.y = -1))
      dda.side.y = (start.y - dda.cell.y) * dda.d.y;
    else if ((dda.step.y = 1))
      dda.side.y = (dda.cell.y + 1.0 - start.y) * dda.d.y;
	dda_loop(&dda, map);
	if (!dda.yhit)
		MIN(hr.hit_dist = (dda.cell.x - start.x + (1 - dda.step.x) / 2) / direction.x, 100);
	else
		MIN(hr.hit_dist = (dda.cell.y - start.y + (1 - dda.step.y) / 2) / direction.y, 100);
	get_hit_side(&dda, &hr);
	hr.value = GRID_GET(map, dda.cell.x, dda.cell.y);
	return (hr);
}
