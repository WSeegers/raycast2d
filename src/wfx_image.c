/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 19:20:40 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 14:08:28 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libwtcfx.h"

t_image		*wfx_create_image(void)
{
	return (f_memalloc(sizeof(t_image)));
}

void		wfx_init_image(t_image *image, int width, int height)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	if (!(image->ptr = mlx_new_image(wfx_get_mlx(), width, height)))
		f_eexit(0, "mlx_new_image failed");
	image->height = height;
	image->width = width;
	image->buffer = (int*)mlx_get_data_addr(image->ptr,
		&bits_per_pixel, &size_line, &endian);
	if (bits_per_pixel != 32 || endian != 0)
		f_eexit(0, "please debug window settings in wfx_init_image");
}

void		wfx_image_to_image(t_image *dst, t_image *src, t_vec2i pos)
{
	t_vec2i	i;
	int		col;

	i = VEC2I(-1, -1);
	while (++i.y < src->height && (i.x = -1))
		while (++i.x < src->width)
		{
			col = GET_IMAGE_PIXEL(src, i.x, i.y);
			SET_IMAGE_PIXEL(dst, i.x + pos.x, i.y + pos.y, col);
		}
}

t_image		*wfx_resize_image_nn(t_image *image, t_vec2i new_size)
{
	t_image *ret;
	t_vec2	ratio;
	t_vec2i	i;
	int		col;

	ret = wfx_create_image();
	wfx_init_image(ret, new_size.x, new_size.y);
	ratio.x = (double)image->width / (double)new_size.x;
	ratio.y = (double)image->height / (double)new_size.y;
	i = VEC2I(-1, -1);
	while (++i.y < new_size.y && (i.x = -1))
		while (++i.x < new_size.x)
		{
			col = GET_IMAGE_PIXEL(image, (int)(i.x * ratio.x),
												(int)(i.y * ratio.y));
			SET_IMAGE_PIXEL(ret, i.x, i.y, col);
		}
	return (ret);
}

void		wfx_destroy_image(t_image *image)
{
	if (!image)
		return ;
	image->buffer = NULL;
	mlx_destroy_image(wfx_get_mlx(), image->ptr);
}
