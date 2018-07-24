/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_xpm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 08:31:55 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/24 14:13:09 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

t_image		*wfx_xpm_file_to_image(t_mlx mlx, char *path_name)
{
	t_image *image;
	t_vec2i	size;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	image = wfx_create_image();
	image->ptr = mlx_xpm_file_to_image(mlx, path_name, &size.x, &size.y);
	if (!image->ptr)
		f_eexit(0, path_name);
	image->buffer = (int*)mlx_get_data_addr(image->ptr, &bits_per_pixel,
		&size_line, &endian);
	if (bits_per_pixel != 32 || endian != 0)
		f_eexit(0, "please debug window settings in wfx_init_image");
	image->width = size.x;
	image->height = size.y;
	return (image);
}
