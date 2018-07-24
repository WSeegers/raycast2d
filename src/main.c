/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 18:48:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 10:28:57 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "draw_map.h"
#include "f_io.h"

void	validate_map(t_grid *map)
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

void	parse_map(t_grid *map, t_hero *hero, t_file *m_file)
{
	char	*line;
	char	*line_ptr;
	t_vec2i	pos;

	pos = VEC2I(0, 0);
	while (f_next_line(&line, m_file))
	{
		pos.x = 0;
		line_ptr = line;
		while (*line)
		{
			if (*line == 'x' && line[1] == ' ')
			{
				hero->pos = VEC2(pos.x + 0.5, pos.y + 0.5);
				grid_set(map, 0, pos.x++, pos.y);
			}
			else if (!f_isdigit(line[0]) || !((line[1] == ' ') || !line[1]))
				f_eexit(0,
			"Map must be single digits only followed by space");
			else
				grid_set(map, f_atoi(line), pos.x++, pos.y);
			line += 2;
		}
		pos.y++;
	}
}

void	get_map(t_grid *map, t_hero *hero)
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
}

static void	load_textures(t_env *env)
{
	env->wolf3d_textures[0] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/wolf3d/bluestone.xpm");
	env->wolf3d_textures[1] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/wolf3d/wood.xpm");
	env->wolf3d_textures[3] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/wolf3d/eagle.xpm");
	env->wolf3d_textures[2] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/wolf3d/greystone.xpm");
	env->wolf3d_textures[4] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/wolf3d/purplestone.xpm");
	env->wolf3d_textures[5] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/wolf3d/redbrick.xpm");
	env->wolf3d_textures[6] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/wolf3d/mossy.xpm");
	env->wolf3d_textures[7] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/wolf3d/colorstone.xpm");
	env->hd_textures[0] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/hd_texture/stone.xpm");
	env->hd_textures[1] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/hd_texture/ceiling.xpm");
	env->hd_textures[2] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/hd_texture/stone2.xpm");
	env->ui[0] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/ui-background.xpm");
}

int		main(void)
{
	t_env		env;
	t_window	window;
	t_hero		hero;
	t_state		splash;

	wfx_init_window(&window, WIDTH, HEIGHT, "2d Raytest");
	hero.pos = VEC2(0, 0);
	hero.velocity = 0;
	hero.direction = vec2_norm(VEC2(-1, 0));
	hero.rotation = 0;
	hero.strafe = 0;
	hero.plane = VEC2(0, 0.66);

	env.window = &window;
	env.hero = &hero;
	get_map(&env.map, env.hero);

	wfx_init_state(&env.game_state);
	env.game_state.loop = fp_basic_loop;
	env.game_state.key_down = key_press;
	env.game_state.key_up = key_release;
	env.game_state.mouse_move = NULL;
	load_textures(&env);

	wfx_blit(&window);
	invoke_state(&window, &env.game_state, &env);
	wfx_start(&window);
}
