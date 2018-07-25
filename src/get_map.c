/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 10:28:22 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/25 14:38:49 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	validate_map(t_grid *map)
{
	t_vec2i	pos;

	pos = VEC2I(-1, -1);
	while (pos.y++ < map->height && (pos.x = -1))
		while (pos.x++ < map->width)
		{
			if ((!pos.y || !pos.x || pos.x == map->width - 1 ||
				pos.y == map->height - 1) &&
				!GRID_GET((*map), pos.x, pos.y))
				grid_set(map, 1, pos.x, pos.y);
		}
}

static void	parse_map(t_grid *map, t_hero *hero, t_file *m_file)
{
	char	*line;
	char	*line_ptr;
	t_vec2i	pos;

	pos = VEC2I(0, 0);
	while (f_next_line(&line, m_file) && (pos.x = -1))
	{
		line_ptr = line;
		while (*line)
		{
			if (*line == 'x' && line[1] == ' ')
			{
				hero->pos = VEC2(pos.x + 0.5, pos.y + 0.5);
				grid_set(map, 0, ++pos.x, pos.y);
			}
			else if (!f_isdigit(line[0]) || !((line[1] == ' ') || !line[1]))
				f_eexit(0, "Map must be single digits only");
			else
				grid_set(map, f_atoi(line), ++pos.x, pos.y);
			line += 2;
		}
		pos.y++;
		f_strdel(&line_ptr);
	}
	f_strdel(&line);
}

void		get_map(t_grid *map, t_hero *hero)
{
	t_file	*m_file;
	char	*line;
	t_vec2i	t;

	if (!(m_file = f_openf("assets/map.w3d", 'r')))
		f_eexit(0, "Fail opening map file");
	t = VEC2I(0, 0);
	if (!f_next_line(&line, m_file))
		f_eexit(0, "Empty map");
	t.x = f_atoi(line);
	t.y = f_atoi(f_strchr(line, ' '));
	if (t.x < 3 || t.y < 3)
		f_eexit(0, "invalid map size");
	grid_init(map, t.x, t.y);
	f_strdel(&line);
	parse_map(map, hero, m_file);
	if (!hero->pos.x || !hero->pos.y)
		f_eexit(0, "no hero spawn");
	validate_map(map);
	f_closef(m_file);
}
