/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:12:06 by gchopin           #+#    #+#             */
/*   Updated: 2021/11/05 14:12:07 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_first_line(t_thread *thread)
{
	double	radian;

	radian = 0.61;
	thread->segment[1].y -= thread->segment[1].altitude
		* (sin(radian) * ((thread->segment[1].x
					- thread->segment[0].x)
				+ (thread->segment[1].z - thread->segment[1].y)));
	bresenham(thread, thread->segment[0], thread->segment[1]);
}

void	draw_second_line(t_thread *thread)
{
	double	radian;

	radian = 0.61;
	thread->segment[3].y -= thread->segment[3].altitude
		* (sin(radian) * ((thread->segment[3].x
					- thread->segment[2].x)
				+ (thread->segment[3].z - thread->segment[3].y)));
	bresenham(thread, thread->segment[0], thread->segment[2]);
}

void	draw_row_part_one(t_thread *thread)
{
	thread->segment[1].x = (thread->segment[1].x + thread->std_segment_x);
	thread->segment[1].z = thread->segment[1].y
		+ (tan(0.61) * (thread->segment[1].x - thread->segment[0].x));
	if (thread->start_two == 0)
	{
		thread->segment[2].y = thread->segment[1].z;
		thread->segment[3].y = thread->segment[1].z;
	}
	if (thread->start_one == 0)
	{
		thread->start_one = 1;
		thread->segment[0].y -= (thread->segment[1].z - thread->segment[0].y);
		start_draw_first_line(thread);
	}
	draw_first_line(thread);
}

void	draw_row_part_two(t_thread *thread)
{
	if (thread->start_two == 0)
	{
		thread->save_x = (thread->segment[2].x - thread->std_segment_x);
		thread->segment[2].x = thread->save_x;
		thread->segment[3].x -= thread->std_segment_x;
	}
	thread->segment[3].x = thread->segment[3].x + thread->std_segment_x;
	thread->segment[3].z = thread->segment[3].y
		+ (tan(0.61) * (thread->segment[3].x - thread->segment[2].x));
	if (thread->start_two == 0)
	{
		thread->start_two = 1;
		thread->save_y = thread->segment[1].z;
		thread->segment[2].y -= (thread->segment[3].z - thread->segment[2].y);
		start_draw_second_line(thread);
	}
	draw_second_line(thread);
}
