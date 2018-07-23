/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 18:48:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/23 15:22:47 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "draw_map.h"

#define CELL 50

#define ROWS 24
#define COLS 24


void	get_map(t_grid *map)
{
	char MAP[ROWS][COLS] = {
		{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
		{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  		{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
  		{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
  		{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  		{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
  		{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
  		{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
  		{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
  		{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
  		{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
  		{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
  		{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
  		{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
  		{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  		{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  		{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
  		{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
  		{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  		{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
  		{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  		{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  		{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
	};

	grid_init(map, COLS, ROWS);
	for (int y = 0; y < ROWS; y++)
		for (int x = 0; x < COLS; x++)
			grid_set(map, CLAMP(MAP[y][x], 0, 6), x, y);
}

int		draw_splash(void *p)
{
	t_env	*env;

	env = (t_env*)p;
	for (int y = 0; y < env->window->height; y++)
		for (int x = 0; x < env->window->width; x++)
	 		wfx_set_pixel(env->window, x, y, x * y + y + x);
	//wfx_blit(env->window);
	return (1);
}

int		splash_key(int key, void *p)
{
	t_env	*env;

	(void)key;
	env = (t_env*)p;
	invoke_state(env->window, &env->game_state, env);
	return (1);
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
		"assets/stone.xpm");
	env->hd_textures[1] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/ceiling.xpm");
	env->hd_textures[2] = wfx_xpm_file_to_image(wfx_get_mlx(),
		"assets/stone2.xpm");
}

int		main(void)
{
	t_env		env;
	t_window	window;
	t_hero		hero;
	t_state		splash;

	wfx_init_window(&window, WIDTH, HEIGHT, "2d Raytest");
	hero.pos = VEC2(13, 9.5);
	hero.velocity = 0;
	hero.direction = vec2_norm(VEC2(-1, 0));
	hero.rotation = 0;
	hero.strafe = 0;

	env.window = &window;
	env.hero = &hero;
	get_map(&env.map);

	hero.plane = VEC2(0, 0.66);

	splash.key_down = splash_key;
	splash.loop = draw_splash;

	wfx_init_state(&env.game_state);
	env.game_state.loop = fp_wolf_loop;
	env.game_state.key_down = key_press;
	env.game_state.key_up = key_release;
	env.game_state.mouse_move = NULL;
	load_textures(&env);

	wfx_blit(&window);
	invoke_state(&window, &env.game_state, &env);
	wfx_start(&window);
}
