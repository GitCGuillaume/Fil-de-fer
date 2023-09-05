/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:25:30 by gchopin           #+#    #+#             */
/*   Updated: 2021/11/17 17:25:49 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 ** S / SW
*/

void	fourth_segment(t_thread *thread,
	int *dp, t_segment *start, t_segment *end)
{
	int	dx;
	int	dy;

	dx = start->x - end->x;
	dy = end->y - start->y;
	*dp = 2 * dx - dy;
	draw_pixel(thread, start->x, start->y);
	while (end->y > start->y)
	{
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
		draw_pixel(thread, start->x, start->y);
	}
}

/*
 ** W / SW
*/

void	third_segment(t_thread *thread,
	int *dp, t_segment *start, t_segment *end)
{
	int	dx;
	int	dy;

	dx = start->x - end->x;
	dy = end->y - start->y;
	*dp = 2 * dy - dx;
	draw_pixel(thread, start->x, start->y);
	while (start->x > end->x)
	{
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
		draw_pixel(thread, start->x, start->y);
	}
}

/*
 ** SE / N
*/

void	second_segment(t_thread *thread,
	int *dp, t_segment *start, t_segment *end)
{
	int	dx;
	int	dy;

	dx = end->x - start->x;
	dy = end->y - start->y;
	*dp = 2 * dx - dy;
	draw_pixel(thread, start->x, start->y);
	while (end->y > start->y)
	{
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
		draw_pixel(thread, start->x, start->y);
	}
}

/*
 ** SE / E
*/

void	first_segment(t_thread *thread,
	int *dp, t_segment *start, t_segment *end)
{
	int	dx;
	int	dy;

	dx = end->x - start->x;
	dy = end->y - start->y;
	*dp = 2 * dy - dx;
	draw_pixel(thread, start->x, start->y);
	while (end->x > start->x)
	{
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
		draw_pixel(thread, start->x, start->y);
	}
}
