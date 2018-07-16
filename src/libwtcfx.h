/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libwtcfx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 18:47:21 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/15 22:18:28 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBWTCFX_H
# define LIBWTCFX_H

# include <math.h>
# include <mlx.h>
# include <stddef.h>
# include <time.h>
#include "f_memory.h"
#include "f_cntl.h"

typedef	void*	t_mlx;

t_mlx		wfx_get_mlx(void);

typedef	struct	s_image
{
	void	*ptr;
	int		width;
	int		height;
	int		*buffer;
}				t_image;

t_image		*wfx_create_image(void);
void		wfx_init_image(t_image *image, int width, int height);
void		wfx_destroy_image(t_image *image);

# define GET_IMAGE_PIXEL(i, x, y)		(i->buffer[(i->width * (y)) + (x)])
# define SET_IMAGE_PIXEL(i, x, y, col)	(GET_IMAGE_PIXEL(i, x, y) = col)

typedef	struct	s_vec2i
{
	int x;
	int y;
}				t_vec2i;

t_vec2i		*vec2i_create();
void		vec2i_init(t_vec2i *v2, int x, int y);

# define NEW_VEC2I(x, y) (t_vec2i){(int)(x), (int)(y)}
# define SET_VEC2I(v, x, y)	(v.x = (int)(x); v.y = (int)(y))

typedef	struct	s_window
{
	t_mlx			mlx;
	void			*ptr;
	int				width;
	int				height;
	t_image			*front;
	t_image			*back;
	clock_t			last_blit;
	clock_t			last_fps;
	unsigned long	frame_count;
	long			fps;
}				t_window;

t_window	*wfx_create_window(void);
void		wfx_init_window(t_window *window, int width, int height, char *title);
void		wfx_destroy_window(t_window *window);
void		wfx_blit(t_mlx mlx, t_window *window);
void		wfx_set_pixel(t_window *window, int x, int y, int col);
void		wfx_clear_window(t_window *window);

void		wfx_line(t_window *window, t_vec2i *p1, t_vec2i *p2, int colour);

#endif