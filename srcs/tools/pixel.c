/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:30:58 by gchopin           #+#    #+#             */
/*   Updated: 2021/11/16 21:02:14 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 ** Need to align width offset to put a pixel into the image
 ** Then just put rgb into the img addr
*/

void	draw_pixel(t_thread *thread, int x, int y)
{
	int	offset;
	int	colour;

	if (x < 0 || y < 0
		|| x > thread->size_x || y > thread->size_y)
		return ;
	offset = (y * thread->mlx.size_line) + (x * thread->mlx.bpp / 8);
	colour = thread->colour;
	if (!thread->mlx.mlx_get_data[offset + 0])
		thread->mlx.mlx_get_data[offset + 0] = colour;
	if (!thread->mlx.mlx_get_data[offset + 1])
		thread->mlx.mlx_get_data[offset + 1] = colour >> 8;
	if (!thread->mlx.mlx_get_data[offset + 2])
		thread->mlx.mlx_get_data[offset + 2] = colour >> 16;
}

int	get_colour(void *mlx_ptr)
{
	int	colour;
	int	r;
	int	g;
	int	b;

	colour = 0;
	r = 255;
	g = 0;
	b = 0;
	if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255)
		&& (b >= 0 && b <= 255))
	{
		colour = r << 16;
		colour += g << 8;
		colour += b;
		return (mlx_get_color_value(mlx_ptr, colour));
	}
	return (0);
}
