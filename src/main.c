/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 18:48:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/19 18:52:03 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "draw_map.h"

#define CELL 50

#define ROWS 24
#define COLS 24

#define WIDTH (ROWS * CELL)
#define HEIGHT (COLS * CELL)

void	get_map(t_grid *map)
{
	char MAP[ROWS][COLS] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,2,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	grid_init(map, COLS, ROWS);
	for (int y = 0; y < ROWS; y++)
		for (int x = 0; x < COLS; x++)
			grid_set(map, MAP[y][x], x, y);
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

int		main(void)
{
	t_env		env;
	t_window	window;
	t_hero		hero;
	t_state		splash;

	wfx_init_window(&window, WIDTH, HEIGHT, "2d Raytest");
	hero.pos = VEC2(COLS / 2, ROWS / 2);
	hero.velocity = 0;
	hero.direction = vec2_norm(VEC2(-1, 0));
	hero.rotation = 0;

	env.window = &window;
	env.hero = &hero;
	get_map(&env.map);

	hero.plane = VEC2(0, 0.65);
	
	splash.key_down = splash_key;
	splash.loop = draw_splash;

	env.game_state.loop = draw_fps;
	env.game_state.key_down = key_press;
	env.game_state.key_up = key_release;

	int size;
	int size2;
	//void *pic = mlx_xpm_file_to_image(window.mlx, "assets/noise.xpm", &size, &size2);
	
	t_image	*pic = wfx_xpm_file_to_image(wfx_get_mlx(), "assets/noise.xpm");
	mlx_put_image_to_window(window.mlx, window.ptr, pic->ptr, 10, 10);
	t_image *pic_b = wfx_resize_image_nn(pic, VEC2I(200, 400));
	wfx_image_to_window(&window, pic, VEC2I(500, 10));
	wfx_image_to_window(&window, pic_b, VEC2I(10, 10));
	wfx_blit(&window);
	invoke_state(&window, &env.game_state, &env);
	wfx_start(&window);
}