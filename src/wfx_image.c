/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 19:20:40 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/15 21:32:36 by wseegers         ###   ########.fr       */
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
	image->buffer = (int*)mlx_get_data_addr(image->ptr, &bits_per_pixel, &size_line, &endian);
	if (bits_per_pixel != 32 || endian != 0)
		f_eexit(0, "please debug window settings in wfx_init_image");
}

void		wfx_destroy_image(t_image *image)
{
	if (!image)
		return ;
	image->buffer = NULL;
	mlx_destroy_image(wfx_get_mlx(), image->ptr);
}