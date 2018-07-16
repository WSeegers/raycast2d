/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libwtcfx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 18:47:21 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/16 13:14:39 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBWTCFX_H
# define LIBWTCFX_H

# include <math.h>
# include <mlx.h>
# include <stddef.h>
# include <time.h>
# include <stdbool.h>
# include "f_memory.h"
# include "f_cntl.h"
# include "f_math.h"

# define MAX_FPS 60

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
t_vec2i		*vec2i_copy(t_vec2i *v);
void		vec2i_add(t_vec2i *v1, t_vec2i *v2);
void		vec2i_sub(t_vec2i *v1, t_vec2i *v2);
void		vec2i_scale(t_vec2i *v1, int scalar);

# define VEC2I(x, y)		(t_vec2i){(int)(x), (int)(y)}
# define SET_VEC2I(v, x, y)	(v.x = (int)(x); v.y = (int)(y))
# define ADD_VEC2I(v1, v2)	(NEW_VEC2I(v1.x + v2.x, v1.y + v2.y))
# define SUB_VEC2I(v1, v2)	(NEW_VEC2I(v1.x - v2.x, v1.y - v2.y))

typedef struct	s_vec2
{
	double x;
	double y;
}				t_vec2;

t_vec2		*vec2_create();
void		vec2_init(t_vec2 *v2, double x, double y);
t_vec2		*vec2_copy(t_vec2 *v);
void		vec2_add(t_vec2 *v1, t_vec2 *v2);
void		vec2_sub(t_vec2 *v1, t_vec2 *v2);
void		vec2_scale(t_vec2 *v1, double scalar);
double		vec2_len(t_vec2 *v);

# define VEC2(x, y)			(t_vec2i){(double)(x), (double)(y)}
# define VEC2_TO_I(v)		(VEC2I((int)v.x, (int)v.y))
# define SET_VEC2(v, x, y)	(v.x = (double)(x); v.y = (double)(y))
# define ADD_VEC2(v1, v2)	(NEW_VEC2I(v1.x + v2.x, v1.y + v2.y))
# define SUB_VEC2(v1, v2)	(NEW_VEC2I(v1.x - v2.x, v1.y - v2.y))
# define LEN_VEC2(v)		(sqrt(v.x * v.x + v.y * v.y))

typedef	struct	s_window
{
	t_mlx			mlx;
	void			*ptr;
	int				width;
	int				height;
	t_image			*front;
	t_image			*back;
	clock_t			last_blit;
	//clock_t			last_fps;
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
void		wfx_rect(t_window *window, t_vec2i *p1, t_vec2i *p2, int colour, bool fill);
void		wfx_circle(t_window *window, t_vec2i *v, int radius, int colour);
void		wfx_grid(t_window *window, t_vec2i *origin, int rows, int cols, int size);

#endif