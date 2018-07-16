/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfx_get_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 14:39:16 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/15 20:14:28 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwtcfx.h"

t_mlx	wfx_get_mlx(void)
{
	static void	*mlx;

	if (!mlx)
		mlx = mlx_init();
	return (mlx);
}
