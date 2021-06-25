/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:52:59 by gchopin           #+#    #+#             */
/*   Updated: 2021/06/24 22:17:17 by gchopin          ###   ########.fr       */
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
	if (segment)
		segment->altitude = nbr;
}

int	get_altitude(t_thread *thread, t_segment *segment, char *line, int j)
{
	char	*str;
	int	start;

	str = NULL;
	if  (line == NULL)
		close_program_error(thread, "Map must not be empty.", 2);
	//while (line[j] && ft_isprint(line[j]) == 0)
	//	j++;
	//	printf("j=%c ", line[j]);
	while (line[j] && ft_isdigit(line[j]) == 0)
	{
		j++;
	}
	if (ft_isdigit(line[j]))
	{
		start = j;
		while (line[j] && ft_isdigit(line[j]))
		{
			j++;
		}
		if (line[start - 1] == '-')
			str = ft_substr(line, (unsigned int)start - 1, j - (start - 1));
		else
			str = ft_substr(line, (unsigned int)start, j - start);
		if (str == NULL)
			close_program_error(thread, "No number returned\n", 2);
		if (line && line[j] == ',')
		{
			while (line[j] && line[j] != ' ')
				j++;
		}
		ft_min_max(thread, str);
		if (segment)
			segment->altitude = ft_atoi(str);
	}
	if (str)
		free(str);
	if (line[j])
		while (line[j] && ft_isdigit(line[j]) == 0)
			j++;
	return (j);
}

void	read_row(t_thread *thread)
{
	double	radian;
	int	i;
	int	j_one;
	int	j_two;
	int	j_mem;
	int	y;
	int	x;
	int	size_x;
	int	size_y;
	int	test = 0;
	int start = 0;
	int res;
int result;
res = 0;
result = 0;
int aya = 0;
i = 0;
int 	start_res_one=0;
int	start_res_two=0;
int	old_res_one=0;
int	old_res_two=0;
j_one = 0;
	j_two = 0;
	if (!mlx_get_screen_size(thread->mlx.mlx_ptr, &size_x, &size_y))
		close_program_error(thread, "Couldn't get resolution screen.\n", 2);
	thread->segment[0].y = size_y * 0.0 + thread->mov_ud;
	thread->segment[2].y = thread->segment[0].y;
	thread->segment[1].x = size_x * 0.50 + thread->mov_lr;
	thread->segment[0].x = thread->segment[1].x;
	thread->segment[2].x = thread->segment[1].x;
	thread->segment[3].x = thread->segment[1].x;
	thread->segment[1].y = thread->segment[0].y;
	thread->segment[3].y = thread->segment[2].y;
	thread->segment[3].z = thread->segment[3].y;
	radian = 0.61;
	thread->segment[1].z = thread->segment[1].y;
	thread->segment[3].z = thread->segment[3].y;
	/*thread->segment[2].altitude = 0;
	thread->segment[0].altitude = 0;
	thread->segment[3].altitude = 0;
	thread->segment[1].altitude = 0;
	*/
	start = 0;
	while (thread->lines[i] != 0)
	{
		//printf("i=%d\n", i);
		j_one = 0;
		j_two = 0;
		mlx_hook(thread->mlx.mlx_win, KEYPRESS,
			KEYPRESS_P_M, ft_keypress, (void *)thread);
		mlx_hook(thread->mlx.mlx_win, KEYRELEASE,
			KEYPRESS_R_M, ft_keypress, (void *)thread);
		while (thread->lines[i][j_one])
		{
			j_one = get_altitude(thread, &thread->segment[0], thread->lines[i], j_one);
			if (thread->lines[i][j_one])
			{
				j_mem = get_altitude(thread, &thread->segment[1], thread->lines[i], j_one);
				thread->segment[1].x = thread->segment[1].x + thread->std_segment_x;
				thread->segment[1].z = thread->segment[1].y + (tan(radian) * (thread->segment[1].x - thread->segment[0].x));
				if (test == 0)
				{
					thread->segment[2].y = thread->segment[1].z;
					thread->segment[3].y = thread->segment[1].z;
				}
				if (start == 0)
				{
					start = 1;
					if (thread->segment[0].altitude > 0)
					{
						if (thread->segment[0].altitude > old_res_one)
							start_res_one = start_res_one + 1;
						else if (old_res_one > thread->segment[0].altitude)
							start_res_one = start_res_one - 1;
						aya = (thread->segment[1].z - thread->segment[0].y) * start_res_one;
						thread->segment[0].y = thread->segment[0].y - (tan(radian) * (thread->segment[1].x - thread->segment[0].x));
				//		if (start_res_one < -1 || start_res_one > 1)
				//			thread->segment[0].y -= aya;
						thread->segment[0].y -= thread->segment[0].altitude;
						old_res_one = thread->segment[0].altitude;
						result = start_res_one;
					}
					else if (thread->segment[0].altitude < 0)
					{
						if (thread->segment[0].altitude < old_res_one)
							start_res_one -=1;
						else if (old_res_one < thread->segment[0].altitude)
							start_res_one += 1;
						aya = (thread->segment[1].z - thread->segment[0].y) * start_res_one;
						thread->segment[0].y = thread->segment[0].y - (tan(radian) / (thread->segment[1].x - thread->segment[0].x));
				//		if (start_res_one < -1 || start_res_one > 1)
				//			thread->segment[0].y -= aya;
						thread->segment[0].y -= thread->segment[0].altitude;
						old_res_one = thread->segment[0].altitude;
						result = start_res_one;
					}
					else
					{
						old_res_one = thread->segment[0].altitude;
						start_res_one = 0;
						result = start_res_one;
						thread->segment[0].y = thread->segment[0].y + (tan(radian) / (thread->segment[1].x - thread->segment[0].x));
					}
				}
				if (thread->segment[1].altitude > 0)
				{
					if (thread->segment[0].altitude > thread->segment[1].altitude)
						result = result - 1;
					else if (thread->segment[1].altitude > thread->segment[0].altitude)
						result = result + 1;
					aya = (thread->segment[1].z - thread->segment[1].y) * result;
					thread->segment[1].y = thread->segment[1].y + (tan(radian) / (thread->segment[1].x - thread->segment[0].x));
				//	if (result < -1 || result > 1)
				//		thread->segment[1].y -= aya;
					thread->segment[1].y -= thread->segment[1].altitude;
					bresenham(thread, thread->segment[0], thread->segment[1]);
				}
				else if (thread->segment[1].altitude < 0)
				{
					if (thread->segment[0].altitude > thread->segment[1].altitude)
					{
						result = result - 1;
					}
					else if (thread->segment[1].altitude > thread->segment[0].altitude)
					{
						result = result + 1;
					}
					aya = (thread->segment[1].z - thread->segment[1].y) * result;
					thread->segment[1].y = thread->segment[1].y + (tan(radian) * (thread->segment[1].x - thread->segment[0].x));
				//	if (result < -1 || result > 1)
				//		thread->segment[1].y -= aya;
					thread->segment[1].y -= thread->segment[1].altitude;
					bresenham(thread, thread->segment[0], thread->segment[1]);
				}
				else
				{
					result = 0;
					thread->segment[1].y = thread->segment[1].y + (tan(radian) * (thread->segment[1].x - thread->segment[0].x));
					bresenham(thread, thread->segment[0], thread->segment[1]);
				}
			}
			if (thread->lines[i + 1])
			{
				j_two = get_altitude(thread, &thread->segment[2], thread->lines[i + 1], j_two);
				if (thread->lines[i + 1][j_two])
				{
					j_mem = get_altitude(thread, &thread->segment[3], thread->lines[i + 1], j_two);
				}
				if (test == 0)
				{
					x = thread->segment[2].x - thread->std_segment_x;
					thread->segment[2].x = x;
					thread->segment[3].x -= thread->std_segment_x;					
				}
				thread->segment[3].x = thread->segment[3].x + thread->std_segment_x;
				thread->segment[3].z = thread->segment[3].y + (tan(radian) * (thread->segment[3].x - thread->segment[2].x));
				if (test == 0)
				{
					test = 1;
					y = thread->segment[1].z;
					if (i == 0 && thread->segment[0].altitude != 0)
						start_res_two = 1;
					if (thread->segment[2].altitude > 0)
					{
						if (thread->segment[2].altitude > thread->segment[0].altitude)
							start_res_two = start_res_two + 1;
						else if (thread->segment[2].altitude < thread->segment[0].altitude)
							start_res_two = start_res_two - 1;
						aya = (thread->segment[3].z - thread->segment[2].y) * start_res_two;
						thread->segment[2].y = thread->segment[2].y - (tan(radian) * (thread->segment[3].x - thread->segment[2].x));
				//		if (start_res_two < -1 || start_res_two > 1)
				//			thread->segment[2].y -= aya;
						thread->segment[2].y -= thread->segment[2].altitude;
						res = start_res_two;
					}
					else if (thread->segment[2].altitude < 0)
					{
						if (thread->segment[2].altitude < thread->segment[0].altitude)
						{
							start_res_two -= 1;
						}
						else if (thread->segment[0].altitude < thread->segment[2].altitude)
						{
							start_res_two += 1;
						}
						aya = (thread->segment[3].z - thread->segment[2].y) * start_res_two;
						thread->segment[2].y = thread->segment[2].y - (tan(radian) / (thread->segment[1].x - thread->segment[0].x));
				//		if (start_res_two < -1 || start_res_two > 1)
				//			thread->segment[2].y -= aya;
						thread->segment[2].y -= thread->segment[2].altitude;
						res = start_res_two;
					}
					else
					{
						start_res_two = 0;
						res = start_res_two;
						thread->segment[2].y = thread->segment[2].y + (tan(radian) / (thread->segment[3].x - thread->segment[2].x));
					}
				}
				if (thread->segment[3].altitude > 0)
				{
					if (thread->segment[2].altitude == thread->segment[3].altitude)
					{
						//if (res == 0)
						//	res = 1;
					}
					if (thread->segment[2].altitude > thread->segment[3].altitude)
						res = res - 1;
					if (thread->segment[3].altitude > thread->segment[2].altitude)
						res = res + 1;
					aya = (thread->segment[3].z - thread->segment[3].y) * res;
					thread->segment[3].y = thread->segment[3].y + (tan(radian) / (thread->segment[3].x - thread->segment[2].x));
				//	if (res < -1 || res > 1)
				//		thread->segment[3].y -= aya;
					thread->segment[3].y -= thread->segment[3].altitude;
					bresenham(thread, thread->segment[0], thread->segment[2]);
				}
				else if (thread->segment[3].altitude < 0)
				{
					if (thread->segment[2].altitude > thread->segment[3].altitude)
					{
						res = res - 1;
					}
					else if (thread->segment[3].altitude > thread->segment[2].altitude)
					{
						res = res + 1;
					}
					aya = (thread->segment[3].z - thread->segment[3].y) * res;
					thread->segment[3].y = thread->segment[3].y + (tan(radian) * (thread->segment[3].x - thread->segment[2].x));
				//	if (res < -1 || res > 1)
				//		thread->segment[3].y -= aya;
					thread->segment[3].y -= thread->segment[3].altitude;
					bresenham(thread, thread->segment[0], thread->segment[2]);
				}
				else
				{
					res = 0;
					thread->segment[3].y = thread->segment[3].y + (tan(radian) * (thread->segment[3].x - thread->segment[2].x));
					bresenham(thread, thread->segment[0], thread->segment[2]);
				}
			}
			j_mem = 0;
			thread->segment[0].y = thread->segment[1].y;
			thread->segment[2].y = thread->segment[3].y;
			thread->segment[1].y = thread->segment[1].z;
			thread->segment[3].y = thread->segment[3].z;
			thread->segment[0].x = thread->segment[1].x;
			thread->segment[2].x = thread->segment[3].x;
		}
		result = 0;
		res = 0;
		start = 0;
		thread->segment[0].altitude = 0;
		thread->segment[1].altitude = 0;
		thread->segment[2].altitude = 0;
		thread->segment[3].altitude = 0;
		test=0;
		thread->segment[0].x = x;
		thread->segment[1].x = x;
		thread->segment[2].x = x;
		thread->segment[3].x = x;
		thread->segment[0].y = y;
		thread->segment[1].y = y;
		i++;
	}
}

void	get_segment(t_thread *thread)
{
	/*thread->segment[0].altitude = 0;
	thread->segment[0].x = 0;
	thread->segment[0].y = 0;
	thread->segment[0].z = 0;
	thread->segment[1].altitude = 0;
	//thread->segment[1].x = 0;
	//thread->segment[1].y = 0;
	thread->segment[1].z = 0;
	thread->segment[2].altitude = 0;
	thread->segment[2].x = 0;
	thread->segment[2].y = 0;
	thread->segment[2].z = 0;
	thread->segment[3].altitude = 0;
	thread->segment[3].x = 0;
	thread->segment[3].y = 0;
	thread->segment[3].z = 0;
	*/
	thread->colour = get_colour(thread->mlx.mlx_ptr);
	read_row(thread);
}
