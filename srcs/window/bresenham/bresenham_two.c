/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:25:30 by gchopin           #+#    #+#             */
/*   Updated: 2021/11/17 11:00:33 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fourth_segment(t_thread *thread,
	int *dp, t_segment *start, t_segment *end)
{
	int	dx;
	int	dy;

	dx = start->x - end->x;
	dy = end->y - start->y;
	*dp = 2 * dx - dy;
	while (end->y >= start->y)
	{
		draw_pixel(thread, start->x, start->y);
		if (*dp > 0)
		{
			*dp = *dp + 2 * (dx - dy);
			start->x = start->x - 1;
		}
		else
		{
			*dp = *dp + (2 * dx);
		}
		start->y = start->y + 1;
	}
}

void	third_segment(t_thread *thread,
	int *dp, t_segment *start, t_segment *end)
{
	int	dx;
	int	dy;

	dx = start->x - end->x;
	dy = end->y - start->y;
	*dp = 2 * dy - dx;
	while (start->x >= end->x)
	{
		draw_pixel(thread, start->x, start->y);
		if (*dp > 0)
		{
			*dp = *dp + (2 * (dy - dx));
			start->y = start->y + 1;
		}
		else
		{
			*dp = *dp + (2 * dy);
		}
		start->x = start->x - 1;
	}
}

void	second_segment(t_thread *thread,
	int *dp, t_segment *start, t_segment *end)
{
	int	dx;
	int	dy;

	dx = end->x - start->x;
	dy = end->y - start->y;
	*dp = 2 * dx - dy;
	while (end->y >= start->y)
	{
		draw_pixel(thread, start->x, start->y);
		if (*dp > 0)
		{
			*dp = *dp + (2 * (dx - dy));
			start->x = start->x + 1;
		}
		else
		{
			*dp = *dp + (2 * dx);
		}
		start->y = start->y + 1;
	}
}

void	first_segment(t_thread *thread,
	int *dp, t_segment *start, t_segment *end)
{
	int	dx;
	int	dy;

	dx = end->x - start->x;
	dy = end->y - start->y;
	*dp = 2 * dy - dx;
	while (end->x >= start->x)
	{
		draw_pixel(thread, start->x, start->y);
		if (*dp > 0)
		{
			*dp = *dp + (2 * (dy - dx));
			start->y = start->y + 1;
		}
		else
		{
			*dp = *dp + (2 * dy);
		}
		start->x = start->x + 1;
	}
}
