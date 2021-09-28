/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 14:51:17 by gchopin           #+#    #+#             */
/*   Updated: 2021/09/28 11:26:38 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	bresenham_two(t_thread *thread, int *dp, t_segment *start, t_segment *end)
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

static void	reverse_values(t_segment *start, t_segment *end)
{
	if (start->y > end->y)
	{
		ft_swap(&start->y, &end->y);
		ft_swap(&start->x, &end->x);
	}
}

void	bresenham(t_thread *thread, t_segment start, t_segment end)
{
	int	dp;
	int	dx;
	int	dy;

	dp = 0;
	reverse_values(&start, &end);
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
