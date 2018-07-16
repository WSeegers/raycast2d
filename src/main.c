/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 18:48:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/15 22:23:00 by wseegers         ###   ########.fr       */
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
	for (int y = 0; y < 50; y++)
		for (int x = 0; x < 50; x++)
		{
			wfx_set_pixel(env->window, x + offset, y + offset, 0x00ffffff);
		}
	wfx_line(env->window, &NEW_VEC2I(0, 0), &NEW_VEC2I(420, 350), 0x00ffff00);
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
	mlx_key_hook(mlx, key_hook, &env);
	mlx_loop(mlx);
}