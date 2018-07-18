/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 18:48:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/18 02:02:26 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libwtcfx.h"
#include "hero.h"
#include "wfx_mac_keys.h"

#define CELL 50

#define ROWS 24
#define COLS 24

#define WIDTH (ROWS * CELL)
#define HEIGHT (COLS * CELL)

typedef struct	s_env
{
	t_window	*window;
	t_mlx		mlx;
	t_hero		*hero;
	t_grid		map;
}				t_env;

int		draw(void *p)
{
	t_env	*env = (t_env*)p;
	
	
	update_hero(env->hero);
	// for(int y = 0; y < ROWS; y++)
	// 	for(int x = 0; x < COLS; x++)
	// 	{
	// 		if (grid_get(&env->map, x, y))
	// 			wfx_rect(env->window, &VEC2I(x * CELL + 1, y * CELL + 1), &VEC2I(x * CELL + CELL, y * CELL + CELL), 0x00ff00ff, true);
	// 	}
	draw_camera(env->window, env->hero, env->map, CELL);
	//wfx_grid(env->window, &VEC2I(0, 0), COLS, ROWS, CELL);
	draw_hero(env->window, env->hero, CELL);
	wfx_blit(env->window);
	wfx_clear_window(env->window);
	return (0);
}

int	motion_hook(int x, int y, void *p)
{
	t_env	*env = (t_env*)p;

	env->hero->pos.x = x;
	env->hero->pos.y = y;

	return (0);
}

#define SPD 0.1

int	key_release(int key, void *p)
{
	t_env	*env = (t_env*)p;

	//printf("key: %d\n", key);
	if (key == 53)
		exit(0);
	else if (key == KEY_A)
		env->hero->rotation += 0.02 * M_PI;
	else if (key == KEY_W)
		env->hero->velocity -= SPD;
	else if (key == KEY_D)
		env->hero->rotation -= 0.02 * M_PI;
	else if (key == KEY_S)
		env->hero->velocity += SPD;
	return (0);
}

int	key_press(int key, void *p)
{
	t_env	*env = (t_env*)p;

	//printf("key: %d\n", key);
	if (key == 53)
		exit(0);
	else if (key == KEY_A)
		env->hero->rotation -= 0.02 * M_PI;
	else if (key == KEY_W)
		env->hero->velocity += SPD;
	else if (key == KEY_D)
		env->hero->rotation += 0.02 * M_PI;
	else if (key == KEY_S)
		env->hero->velocity -= SPD;
	return (0);
}

void	get_map(t_grid *map)
{
	char MAP[ROWS][COLS] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
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

int		main(void)
{
	t_env		env;
	t_mlx		mlx;
	t_window	window;
	t_hero		hero;

	mlx = wfx_get_mlx();
	wfx_init_window(&window, WIDTH, HEIGHT, "2d Raytest");
	hero.pos = VEC2(COLS / 2, ROWS / 2);
	hero.velocity = 0;
	hero.direction = vec2_norm(VEC2(-1, 0));
	hero.rotation = 0;

	env.mlx = mlx;
	env.window = &window;
	env.hero = &hero;
	get_map(&env.map);

	hero.plane = VEC2(0, 0.66);
	
	//mlx_hook(window.ptr, 2, 0, key_release_hook, &env);
	//mlx_key_hook(window.ptr, key_hook, &env);
	

	wfx_key_press_hook(&window, key_press, &env);
	wfx_key_release_hook(&window, key_release, &env);

	//mlx_hook(window.ptr, 6, 0, motion_hook, &env);
	wfx_loop_hook(&window, draw, &env);
	wfx_start(&window);
}