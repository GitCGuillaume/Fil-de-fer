/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:52:59 by gchopin           #+#    #+#             */
/*   Updated: 2021/06/02 15:09:19 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	draw_pixel(t_thread *thread, int x, int y, int colour)
{
	int	pixel;

	pixel = (y * thread.mlx->size_line) + (x * 4);
	thread->mlx.mlx_get_data[pixel + 0] = color;
	thread->mlx.mlx_get_data[pixel + 1] = color >> 8;
	thread->mlx.mlx_get_data[pixel + 2] = color >> 16;
}

void	draw_bresenham(t_thread *thread)
{
	int	dx;
	int	dy;
	int	dp;

	draw_pixel(thread, );
}
