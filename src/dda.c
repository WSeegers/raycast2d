/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 23:22:41 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/18 08:13:05 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

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

// //calculate value of wallX
//       double wallX; //where exactly the wall was hit
//       if (side == 0) wallX = posY + perpWallDist * rayDirY;
//       else           wallX = posX + perpWallDist * rayDirX;
//       wallX -= floor((wallX));

// if(side == 0 && rayDirX > 0)
//       {
//         floorXWall = mapX;
//         floorYWall = mapY + wallX;
//       }
//       else if(side == 0 && rayDirX < 0)
//       {
//         floorXWall = mapX + 1.0;
//         floorYWall = mapY + wallX;
//       }
//       else if(side == 1 && rayDirY > 0)
//       {
//         floorXWall = mapX + wallX;
//         floorYWall = mapY;
//       }
//       else
//       {
//         floorXWall = mapX + wallX;
//         floorYWall = mapY + 1.0;
//       }


void	get_hit_side(t_dda *dda, t_hit_report *hr, t_vec2 start, t_vec2 ray)
{
	double axis_dist;

	hr->cell = dda->cell;
	if (dda->yhit)
	{
		hr->side = (dda->step.y == 1) ? HIT_NORTH : HIT_SOUTH;
		hr->offset = fmod(start.x + hr->hit_dist * ray.x, 1);
		hr->pos.x = hr->cell.x + hr->offset;
		hr->pos.y = hr->cell.y + (ray.y < 0);
	}
	else
	{
		hr->side = (dda->step.x == 1) ? HIT_WEST : HIT_EAST;
		hr->offset = fmod(start.y + hr->hit_dist * ray.y, 1);
		hr->pos.y = dda->cell.y + hr->offset;
		hr->pos.x = dda->cell.x + (ray.x < 0);
	}
}

t_hit_report	dda(t_vec2 start, t_vec2 direction, t_grid map)
{
	t_dda			dda;
	t_hit_report	hr;
	
	dda.d.x = fabs(1.0 / direction.x);
	dda.d.y = fabs(1.0 / direction.y);
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
		hr.hit_dist = (dda.cell.x - start.x + (1 - dda.step.x) / 2) / direction.x;
	else
		hr.hit_dist = (dda.cell.y - start.y + (1 - dda.step.y) / 2) / direction.y;
	get_hit_side(&dda, &hr, start, direction);
	hr.value = GRID_GET(map, dda.cell.x, dda.cell.y);
	return (hr);
}
