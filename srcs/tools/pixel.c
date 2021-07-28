/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:30:58 by gchopin           #+#    #+#             */
/*   Updated: 2021/07/28 15:31:38 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_colour_2(void *mlx_ptr)
{
	int	colour;
	int	r;
	int	g;
	int	b;

	colour = 0;
	r = 0;
	g = 0;
	b = 255;
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
void	draw_pixel_test(t_thread *thread, int x, int y)
{
	int	pixel;
	int	colour;

	if (x < 0 || y < 0 
			|| x > thread->size_x || y > thread->size_y)
		return ;
	pixel = (y * thread->mlx.size_line) + (x * 4);
	colour = get_colour_2(thread->mlx.mlx_ptr);
	thread->mlx.mlx_get_data[pixel + 0] = colour;
	thread->mlx.mlx_get_data[pixel + 1] = colour >> 8;
	thread->mlx.mlx_get_data[pixel + 2] = colour >> 16;
}

void	draw_pixel(t_thread *thread, int x, int y)
{
	int	pixel;
	int	colour;

	if (x < 0 || y < 0 
			|| x >= thread->size_x || y >= thread->size_y)
		return ;
	pixel = (y * thread->mlx.size_line) + (x * 4);
	colour = thread->colour;
	if (!thread->mlx.mlx_get_data[pixel + 0])
		thread->mlx.mlx_get_data[pixel + 0] = colour;
	if (!thread->mlx.mlx_get_data[pixel + 1])
		thread->mlx.mlx_get_data[pixel + 1] = colour >> 8;
	if (!thread->mlx.mlx_get_data[pixel + 2])
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
