/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 14:51:17 by gchopin           #+#    #+#             */
/*   Updated: 2021/06/08 19:07:39 by gchopin          ###   ########.fr       */
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
	while (start->x > start->x)
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

void	bresenham(t_thread *thread, t_segment start, t_segment end)
{
	int	dp;
	int	dx;
	int	dy;

	dp = 0;
	dy = end.y - start.y;
	draw_pixel(thread, start.x, start.y);
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

/*
void	bresenham(t_thread *thread, t_segment start, t_segment end)
{
	int x0 = start.x;
	int x1 = end.x;
	int y0 = start.y;
	int y1 = end.y;
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	deltaE = 2 * dy;
	int	deltaNE = 2 * (dy - dx);
	int	dp = 0;

	draw_pixel(thread, x0, y0);
	printf("x1=%d x0=%d\n", x1, x0);
	if (x1 >= x0)
	{
		dx = x1 - x0;
		dy = y1 - y0;
		printf("allo");
		if (dx >= dy)
		{
			dp = 2 * dy - dx;
			printf("dp=%d\n", dp);
			while (x1 > x0)
			{
				if (dp > 0)
				{
					dp = dp + (2 * (dy - dx));
					y0++;
				}
				else
				{
					dp = dp + (2 * dy);
				}
				x0++;
				draw_pixel(thread, x0, y0);
			}
		}
		else
		{
			dp = 2 * dx - dy;
			while (y1 > y0)
			{
				if (dp > 0)
				{
					dp = dp + (2 * (dx - dy));
					x0++;
				}
				else
				{
					dp = dp + (2 * dx);
				}
				y0++;
				draw_pixel(thread, x0, y0);
			}
		}
	}
	else
	{
		dx = x0 - x1;
		dy = y1 - y0;
		if (dx >= dy)
		{
			dp = 2 * dy - dx;
			while (x0 > x1)
			{
				if (dp > 0)	
				{
					dp = dp + (2 * (dy - dx));
					y0++;
				}
				else
				{
					dp = dp + (2 * dy);
				}
				x0--;
				draw_pixel(thread, x0, y0);
			}
		}
		else
		{
			dp = 2 * dx - dy;
			while (x0 > x1)
			{
				if (dp > 0)
				{
					dp = dp + 2 * (dx - dy);
					x0--;
				}
				else
				{
					dp = dp + (2 * dx);
				}
				y0++;
				draw_pixel(thread, x0, y0);
			}
		}
	}
}
*/
