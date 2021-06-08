/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:30:58 by gchopin           #+#    #+#             */
/*   Updated: 2021/06/08 10:05:42 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pixel(t_thread *thread, int x, int y)
{
	int	pixel;
	int	colour;

	pixel = (y * thread->mlx.size_line) + (x * 4);
	colour = thread->colour;
	thread->mlx.mlx_get_data[pixel + 0] = colour;
	thread->mlx.mlx_get_data[pixel + 1] = colour >> 8;
	thread->mlx.mlx_get_data[pixel + 2] = colour >> 16;
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
