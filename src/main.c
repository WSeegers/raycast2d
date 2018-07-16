/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 18:48:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/16 13:15:49 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libwtcfx.h"

#define WIDTH 1200
#define HEIGHT 800

typedef struct	s_env
{
	t_window	*window;
	t_mlx		mlx;
}				t_env;

int		draw(void *p)
{
	t_env	*env;
	static int offset = 0;

	env = (t_env*)p;
	offset = (offset + 1) % (HEIGHT / 2);
	wfx_clear_window(env->window);
	wfx_grid(env->window, &VEC2I(10, 10), 5, 6, 50);
	wfx_circle(env->window, &VEC2I(70, 100), 50, 0x00ffffff);
	//wfx_line(env->window, &VEC2I(0, 0), &VEC2I(420, 350), 0x00ffff00);
	wfx_blit(env->mlx, env->window);
	return (0);
}

int	key_hook(int key, void *p)
{
	printf("key: %d\n", key);
	(void)p;
	return (0);
}

int		main(void)
{
	t_env		env;
	t_mlx		mlx;
	t_window	window;


	mlx = wfx_get_mlx();
	wfx_init_window(&window, WIDTH, HEIGHT, "2d Raytest");

	env.mlx = mlx;
	env.window = &window;
	mlx_loop_hook(mlx, draw, &env);
	mlx_key_hook(window.ptr, key_hook, &env);
	mlx_loop(mlx);
}