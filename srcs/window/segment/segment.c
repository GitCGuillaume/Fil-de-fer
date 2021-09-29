/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:52:59 by gchopin           #+#    #+#             */
/*   Updated: 2021/09/28 20:07:07 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	print_grill_row(t_thread *thread, int j_one, int i)
{
	if (thread->lines[i][j_one])
	{
		get_altitude(thread, &thread->segment[1], thread->lines[i], j_one);
		draw_row_part_one(thread);
	}
}

static void	print_grill_column(t_thread *thread, int *j_two, int i)
{
	if (thread->lines[i + 1])
	{
		*j_two = get_altitude(thread,
				&thread->segment[2], thread->lines[i + 1], *j_two);
		if (thread->lines[i + 1][*j_two])
			get_altitude(thread,
				&thread->segment[3], thread->lines[i + 1], *j_two);
		draw_row_part_two(thread);
	}
}

static void	run_projection(t_thread *thread)
{
	int	i;
	int	j_one;
	int	j_two;

	i = 0;
	get_altitude(thread, &thread->segment[0], thread->lines[i], 0);
	while (thread->lines[i] != 0)
	{
		j_one = 0;
		j_two = 0;
		while (thread->lines[i][j_one])
		{
			j_one = get_altitude(thread,
					&thread->segment[0], thread->lines[i], j_one);
			print_grill_row(thread, j_one, i);
			print_grill_column(thread, &j_two, i);
			set_row(thread);
		}
		set_column(thread);
		i++;
	}
}

void	get_segment(t_thread *thread)
{
	thread->colour = get_colour(thread->mlx.mlx_ptr);
	if (mlx_get_screen_size(thread->mlx.mlx_ptr,
			&thread->segment[1].x, &thread->segment[0].y))
		close_program_error(thread, "Couldn't get resolution screen.\n", 2);
	thread->segment[0].y = 0 + thread->mov_ud;
	thread->segment[2].y = thread->segment[0].y;
	thread->segment[0].x = 0 + thread->mov_lr;
	thread->segment[1].x = thread->segment[0].x;
	thread->segment[2].x = thread->segment[1].x;
	thread->segment[3].x = thread->segment[1].x;
	thread->segment[1].y = thread->segment[0].y;
	thread->segment[3].y = thread->segment[2].y;
	thread->segment[3].z = thread->segment[3].y;
	thread->segment[1].z = thread->segment[1].y;
	thread->segment[3].z = thread->segment[3].y;
	thread->save_x = 0;
	thread->save_y = 0;
	thread->start_one = 0;
	thread->start_two = 0;
	run_projection(thread);
}
