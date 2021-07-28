/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 14:51:17 by gchopin           #+#    #+#             */
/*   Updated: 2021/07/23 11:10:46 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fourth_segment(t_thread *thread, int *dp, t_segment *start, t_segment *end)
{
	int	dx;
	int	dy;

	dx = start->x - end->x;
	dy = end->y - start->y;
	*dp = 2 * dx - dy;
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

void	third_segment(t_thread *thread, int *dp, t_segment *start, t_segment *end)
{
	int	dx;
	int	dy;

	dx = start->x - end->x;
	dy = end->y - start->y;
	*dp = 2 * dy - dx;
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

void	second_segment(t_thread *thread, int *dp, t_segment *start, t_segment *end)
{
	int	dx;
	int	dy;

	dx = end->x - start->x;
	dy = end->y - start->y;
	*dp = 2 * dx - dy;
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

void	first_segment(t_thread *thread, int *dp, t_segment *start, t_segment *end)
{
	int	dx;
	int	dy;

	dx = end->x - start->x;
	dy = end->y - start->y;
	*dp = 2 * dy - dx;
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

void	bresenham_two(t_thread *thread, int *dp, t_segment *start, t_segment *end)
{
	int	dx;
	int	dy;

	dx = start->x - end->x;
	dy = end->y - start->y;
	if (dx >= dy)
		third_segment(thread, dp, start, end);
	else
		fourth_segment(thread, dp, start, end);
	
}
void	bresenham(t_thread *thread, t_segment start, t_segment end)
{
	int	dp;
	int	dx;
	int	dy;

	dp = 0;
	if (start.y > end.y)
	{
		ft_swap(&start.y, &end.y);
		ft_swap(&start.x, &end.x);
	}
	dy = end.y - start.y;
	if (end.x >= start.x)
	{
		dx = end.x - start.x;
		if (dx >= dy)
			first_segment(thread, &dp, &start, &end);
		else
			second_segment(thread, &dp, &start, &end);
	}
	else
	{
		dx = start.x - end.x;
		if (dx >= dy)
			third_segment(thread, &dp, &start, &end);
		else
			fourth_segment(thread, &dp, &start, &end);
	}
}
