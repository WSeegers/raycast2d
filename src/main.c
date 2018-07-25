/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 18:48:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/25 14:27:49 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "draw_map.h"

static void	load_textures(t_env *env, t_mlx mlx)
{
	env->wolf3d_textures[0] = wfx_xpm_file_to_image(mlx,
		"assets/wolf3d/bluestone.xpm");
	env->wolf3d_textures[1] = wfx_xpm_file_to_image(mlx,
		"assets/wolf3d/wood.xpm");
	env->wolf3d_textures[3] = wfx_xpm_file_to_image(mlx,
		"assets/wolf3d/eagle.xpm");
	env->wolf3d_textures[2] = wfx_xpm_file_to_image(mlx,
		"assets/wolf3d/greystone.xpm");
	env->wolf3d_textures[4] = wfx_xpm_file_to_image(mlx,
		"assets/wolf3d/purplestone.xpm");
	env->wolf3d_textures[5] = wfx_xpm_file_to_image(mlx,
		"assets/wolf3d/redbrick.xpm");
	env->wolf3d_textures[6] = wfx_xpm_file_to_image(mlx,
		"assets/wolf3d/mossy.xpm");
	env->wolf3d_textures[7] = wfx_xpm_file_to_image(mlx,
		"assets/wolf3d/colorstone.xpm");
	env->hd_textures[0] = wfx_xpm_file_to_image(mlx,
		"assets/hd_texture/stone.xpm");
	env->hd_textures[1] = wfx_xpm_file_to_image(mlx,
		"assets/hd_texture/ceiling.xpm");
	env->hd_textures[2] = wfx_xpm_file_to_image(mlx,
		"assets/hd_texture/stone2.xpm");
}

static void	init_env(t_env *env, t_window *window, t_hero *hero)
{
	f_bzero(env, sizeof(*env));
	f_bzero(window, sizeof(*window));
	f_bzero(hero, sizeof(*hero));
	env->game_state.loop = fp_basic_loop;
	env->game_state.key_down = key_press;
	env->game_state.key_up = key_release;
	hero->pos = VEC2(0, 0);
	hero->velocity = 0;
	hero->direction = vec2_norm(VEC2(-1, 0));
	hero->rotation = 0;
	hero->strafe = 0;
	hero->plane = VEC2(0, 0.66);
}

int			main(void)
{
	t_env		env;
	t_window	window;
	t_hero		hero;

	init_env(&env, &window, &hero);
	wfx_init_window(&window, WIDTH, HEIGHT, "2d Raytest");
	env.window = &window;
	env.hero = &hero;
	get_map(&env.map, env.hero);
	load_textures(&env, window.mlx);
	wfx_blit(&window);
	invoke_state(&window, &env.game_state, &env);
	wfx_start(&window);
}
