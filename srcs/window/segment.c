/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:52:59 by gchopin           #+#    #+#             */
/*   Updated: 2021/06/10 11:16:15 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	convert_hexa(t_thread *thread, t_segment *segment, char *str)
{
	double	power;
	double	nbr;
	char	*convert;
	int	max;

	max = ft_strlen(str) - 1;
	nbr = 0;
	if (str == NULL)
		close_program_error(thread, "Hexa is NULL\n", 2);
	if (str[0] == '0' && str[1] == 'x' && str[2] == '\0')
	{
		if (str)
			free(str);
		close_program_error(thread, "Hexa is wrong.\n", 2);
	}
	power = 0.0;
	while (max > 1)
	{
		if (str[max] >= 'A' && str[max] <= 'F')
		{
			convert = ft_itoa((int)str[max] - 55);
			if (convert == NULL)
			{
				if (str)
					free(str);
				close_program_error(thread, "Convert hexa failed.\n", 2);
			}
			nbr += (double)ft_atoi(convert) * pow(16.0, power);
			free(convert);
		}
		else if (str[max] >= 'a' && str[max] <= 'f')
		{
			convert = ft_itoa((int)str[max] - 87);
			if (convert == NULL)
			{
				if (str)
					free(str);
				close_program_error(thread, "Convert hexa failed.\n", 2);
			}
			nbr += (double)ft_atoi(convert) * pow(16.0, power);
			free(convert);
		}
		else if (ft_isdigit(str[max]))
		{
			convert = ft_itoa((int)str[max] - 48);
			if (convert == NULL)
			{
				if (str)
					free(str);
				close_program_error(thread, "Convert hexa failed.\n", 2);
			}
			nbr += (double)ft_atoi(convert) * pow(16.0, power);
			free(convert);
		}
		power = power + 1.0;
		max--;
	}
	free(str);
	segment->altitude = nbr;
}

int	get_altitude(t_thread *thread, t_segment *segment, char *line, int j)
{
	char	*str;
	int	start;

	str = NULL;
	if  (line == NULL)
		close_program_error(thread, "Map must not be empty.", 2);
	while (ft_isdigit(line[j]) == 0)
		j++;
	start = j;
	while (line[j] >= '0' && line[j] <= '9')
		j++;
	if (line[j] == 'x')
	{
		j++;
		while ((line[j] >= 'A' && line[j] <= 'F')
			|| (line[j] >= 'a' && line[j] <= 'f')
			|| (line[j] >= '0' && line[j] <= '9'))
			j++;
		convert_hexa(thread, segment, ft_substr(line, (unsigned int)start, j - start));
		if (str)
			free(str);
		return (j);
	}
	if (line[start - 1] == '-')
		str = ft_substr(line, (unsigned int)start - 1, j - (start - 1));
	else
		str = ft_substr(line, (unsigned int)start, j - start);
	if (str == NULL)
		close_program_error(thread, "No number returned\n", 2);
	ft_min_max(thread, str);
	segment->altitude = ft_atoi(str);
	free(str);
	if (line[j])
		while (line[j] && ft_isdigit(line[j]) == 0)
			j++;
	return (j);
}

void	read_row(t_thread *thread, t_segment *start_hor, t_segment *end_hor)
{
	t_segment	start_ver;
	t_segment	end_ver;
	t_segment	a;
	int	i;
	int	j_one;
	int	j_two;
	int	y;
	int	x;
	int	size_x;
	int	size_y;
	int	test = 0;
	i = 0;
	j_one = 0;
	j_two = 0;
	if (!mlx_get_screen_size(thread->mlx.mlx_ptr, &size_x, &size_y))
		close_program_error(thread, "Couldn't get resolution screen.\n", 2);
	start_hor->y = 0;
	start_ver.y = 0;
	end_hor->y = start_hor->y;
	end_ver.y = start_ver.y;
	start_hor->x = size_x * 0.25;
	end_hor->x = size_x * 0.25;
	start_ver.x = size_x * 0.25;
	end_ver.x = size_x * 0.25;
	x = start_hor->x;
	a.x = end_ver.x;
	a.y = start_ver.y;
	y = end_ver.y;
	while (thread->lines[i] != 0)
	{
	//	start_hor->x = size_x * 0.25;
	//	end_hor->x = size_x * 0.25;
		j_one = 0;
		j_two = 0;
		while (thread->lines[i][j_one])
		{
			j_one = get_altitude(thread, start_hor, thread->lines[i], j_one);
			if (thread->lines[i][j_one])
			{
				end_hor->x += thread->std_segment_x;
				end_hor->y = end_hor->y + (tan(0.61) * (end_hor->x - start_hor->x));
			}
			bresenham(thread, *start_hor, *end_hor);
			start_hor->altitude = end_hor->altitude;
			if (thread->lines[i + 1] && thread->lines[i + 1][j_two])
			{
				start_ver.x = start_hor->x;
				start_ver.y = start_hor->y;
				j_two = get_altitude(thread, &start_ver, thread->lines[i + 1], j_two);
				end_ver.x = start_ver.x - thread->std_segment_x;
				if (x > end_ver.x)
					x = end_ver.x;
				if (test == 0)
				{
					test = 1;
					//y += (tan(0.61) * (start_ver.x - end_ver.x));
					y += (tan(0.61) * (start_ver.x - end_ver.x));
				}
				//end_ver.y = end_ver.y + (tan(0.61) * (start_ver.x - end_ver.x));
				a.x = end_ver.x;
				a.y = start_ver.y + (tan(0.61) * (start_ver.x - end_ver.x));
				bresenham(thread, start_ver, a);
			}
			start_hor->x = end_hor->x;
			start_hor->y = end_hor->y;
		}
		test=0;
		start_hor->altitude = 0;
		end_hor->altitude = 0;
	//	y += thread->std_segment_y;
	//	start_hor->y = y;
		start_hor->x = x;
		end_hor->x = x;
	//	start_hor->x = end_ver.x;
//		end_hor->x = end_ver.x;
			start_hor->y = y;
			end_hor->y = y;
		//	start_hor->y = end_ver.y;
		//	end_hor->y = end_ver.y;
		i++;
	}
}

void	read_column(t_thread *thread, t_segment *start, t_segment *end)
{
	int	i;
	int	j_one;
	int	j_two;
	int	x_one;
	int	x_two;
	int	y_one;
	int	y_two;
	int	size_x;
	int	size_y;
	int	y;
	if (!mlx_get_screen_size(thread->mlx.mlx_ptr, &size_x, &size_y))
		close_program_error(thread, "Couldn't get resolution screen.\n", 2);
	i = 0;
	j_one = 0;
	j_two = 0;
	/*start->x = thread->std_segment_x;
	end->x = thread->std_segment_x;
	start->y = thread->std_segment_y;
	end->y = thread->std_segment_y;
	*/
	start->x = size_x * 0.25;
	end->x = size_x * 0.25;
	start->y = 0;
	end->y = start->y;
	y = start->y;
	//y_one = 0;
	while (thread->lines[i])
	{
		j_one = 0;
		j_two = 0;
		//start->x = thread->std_segment_x;
		start->x = size_x * 0.25;
		//end->x = thread->std_segment_x;
		end->x = size_x * 0.25;
		while (thread->lines[i][j_one])
		{
			if (thread->lines[i][j_one])
			{
				j_one = get_altitude(thread, start, thread->lines[i], j_one);
			}
			if (thread->lines[i + 1])
			{
				if (thread->lines[i + 1][j_two])
				{
					j_two = get_altitude(thread, end, thread->lines[i + 1], j_two);
					//bresenham(thread, *start, *end);
				}
			}
			start->x += thread->std_segment_x;
		}
		//y_one += thread->std_segment_y;
		y += thread->std_segment_y;
		start->y = y;
		end->y = start->y;
		//start->y = y_one;
		i++;
	}
}

void	get_segment(t_thread *thread)
{
	t_segment	seg_start;
	t_segment	seg_end;
	//int	colour;

	thread->colour = get_colour(thread->mlx.mlx_ptr);
	read_row(thread, &seg_start, &seg_end);
	//read_column(thread, &seg_start, &seg_end);
}
