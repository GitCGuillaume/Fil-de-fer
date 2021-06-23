/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:52:59 by gchopin           #+#    #+#             */
/*   Updated: 2021/06/23 15:03:22 by gchopin          ###   ########.fr       */
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

void	read_row(t_thread *thread, t_segment *start_hor, t_segment *end_hor)
{
	t_segment	start_ver;
	t_segment	end_ver;
	t_segment	a;
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
	start_hor->y = size_y * 0.20;
	start_ver.y = start_hor->y;
	end_hor->x = size_x * 0.50;
	start_hor->x = end_hor->x;
	start_ver.x = end_hor->x;
	end_ver.x = end_hor->x;
	end_hor->y = start_hor->y;
	end_ver.y = start_ver.y;
	end_ver.z = end_ver.y;
	radian = 0.61;
	end_hor->z = end_hor->y;
	end_ver.z = end_ver.y;
	start_ver.altitude = 0;
	start_hor->altitude = 0;
	end_ver.altitude = 0;
	end_hor->altitude = 0;
	start = 0;
	while (thread->lines[i] != 0)
	{
		printf("i=%d\n", i);
		j_one = 0;
		j_two = 0;
		while (thread->lines[i][j_one])
		{
			j_one = get_altitude(thread, start_hor, thread->lines[i], j_one);
			if (thread->lines[i][j_one])
			{
				j_mem = get_altitude(thread, end_hor, thread->lines[i], j_one);
				end_hor->x = end_hor->x + thread->std_segment_x;
				end_hor->z = end_hor->y + (tan(radian) * (end_hor->x - start_hor->x));
				if (test == 0)
				{
					start_ver.y = end_hor->z;
					end_ver.y = end_hor->z;
				}
				if (start == 0)
				{
					start = 1;
					/*aya = end_hor->z - start_hor->y;
					if (start_hor->altitude > 0)
						start_hor->y = start_hor->y - (tan(radian) * (end_hor->x - start_hor->x));
					else if (start_hor->altitude < 0)
						start_hor->y = start_hor->y - (tan(radian) / (end_hor->x - start_hor->x));
					else
						start_hor->y = start_hor->y - (tan(radian) / (end_hor->x - start_hor->x));
					if (start_hor->altitude != 0)
					{
						start_hor->y -= aya;
						start_hor->y -= start_hor->altitude;
					}*/
					
					
					if (start_hor->altitude > 0)
					{
						if (start_hor->altitude == old_res_one)
						{
							//if (start_res_one == 0)
							//	start_res_one = 1;
						}
						else if (start_hor->altitude > old_res_one)
							start_res_one = start_res_one + 1;
						else if (old_res_one > start_hor->altitude)
							start_res_one = start_res_one - 1;
						aya = (end_hor->z - start_hor->y) * start_res_one;
						start_hor->y = start_hor->y - (tan(radian) * (end_hor->x - start_hor->x));
					//	if (start_res_one < -1 || start_res_one > 1)
							start_hor->y -= aya;
						start_hor->y -= start_hor->altitude;
						old_res_one = start_hor->altitude;
						result = start_res_one;
					}
					else if (start_hor->altitude < 0)
					{
						if (start_hor->altitude < old_res_one)
						{
							start_res_one -=1;
						}
						else if (old_res_one < start_hor->altitude)
						{
							start_res_one += 1;
						}
						aya = (end_hor->z - start_hor->y) * start_res_one;
						start_hor->y = start_hor->y + (tan(radian) / (end_hor->x - start_hor->x));
						//if (result < -1 || result > 1)
							start_hor->y -= aya;
						start_hor->y -= start_hor->altitude;
						old_res_one = start_hor->altitude;
						result = start_res_one;
					}
					else
					{
						old_res_one = start_hor->altitude;
						start_res_one = 0;
						result = start_res_one;
						start_hor->y = start_hor->y + (tan(radian) / (end_hor->x - start_hor->x));
					}
				}
				if (end_hor->altitude > 0)
				{
					if (start_hor->altitude == end_hor->altitude)
					{
					//	if (result == 0)
					//		result = 1;
					}
					else if (start_hor->altitude > end_hor->altitude)
						result = result - 1;
					else if (end_hor->altitude > start_hor->altitude)
						result = result + 1;
					aya = (end_hor->z - end_hor->y) * result;
					end_hor->y = end_hor->y - (tan(radian) / (end_hor->x - start_hor->x));
				//	if (result < -1 || result > 1)
						end_hor->y -= aya;
					end_hor->y -= end_hor->altitude;
					bresenham(thread, *start_hor, *end_hor);
				}
				else if (end_hor->altitude < 0)
				{
					if (start_hor->altitude > end_hor->altitude && end_hor->altitude < 0)
					{
						result = result - 1;
					}
					else if (end_hor->altitude > start_hor->altitude && end_hor->altitude < 0)
					{
						result = result + 1;
					}
					else if (end_hor->altitude == start_hor->altitude && end_hor->altitude < 0)
					{
					//	if (result == 0)
					//		result = 1;
					}
					printf("end_hor->altitude=%d < start_hor->altitude=%d result=%d\n", end_hor->altitude, start_hor->altitude, result);
					aya = (end_hor->z - end_hor->y) * result;
					end_hor->y = end_hor->y + (tan(radian) * (end_hor->x - start_hor->x));
					//if (result < -1 || result > 1)
						end_hor->y -= aya;
					end_hor->y -= end_hor->altitude;
					bresenham(thread, *start_hor, *end_hor);
				}
				else
				{
					result = 0;
					end_hor->y = end_hor->y + (tan(radian) * (end_hor->x - start_hor->x));;
					bresenham(thread, *start_hor, *end_hor);
				}
			}
			if (thread->lines[i + 1])
			{
				j_two = get_altitude(thread, &start_ver, thread->lines[i + 1], j_two);
				if (thread->lines[i + 1][j_two])
				{
					j_mem = get_altitude(thread, &end_ver, thread->lines[i + 1], j_two);
				}
				if (test == 0)
				{
					x = start_ver.x - thread->std_segment_x;
					start_ver.x = x;
					end_ver.x -= thread->std_segment_x;					
				}
				end_ver.x = end_ver.x + thread->std_segment_x;
				end_ver.z = end_ver.y + (tan(radian) * (end_ver.x - start_ver.x));
				if (test == 0)
				{
					test = 1;
					y = end_hor->z;
					if (i == 0 && start_hor->altitude != 0)
						start_res_two = 1;
					if (start_ver.altitude > 0)
					{
						if (start_ver.altitude == start_hor->altitude)
						{
						//	if (start_res_two == 0)
						//		start_res_two = 1;
						}
						else if (start_ver.altitude > start_hor->altitude)
							start_res_two = start_res_two + 1;
						else if (start_ver.altitude < start_hor->altitude)
							start_res_two = start_res_two - 1;
						aya = (end_ver.z - start_ver.y) * start_res_two;
						start_ver.y = start_ver.y - (tan(radian) * (end_ver.x - start_ver.x));
						//if (start_res_two < -1 || start_res_two > 1)
							start_ver.y -= aya;
						start_ver.y -= start_ver.altitude;
						res = start_res_two;
					}
					else if (start_ver.altitude < 0)
					{
						if (start_ver.altitude < start_hor->altitude)
						{
							start_res_two -=1;
						}
						else if (start_hor->altitude < start_ver.altitude)
						{
							start_res_two += 1;
						}
						aya = (end_ver.z - start_ver.y) * start_res_two;
						start_ver.y = start_ver.y + (tan(radian) / (end_hor->x - start_hor->x));
						//if (result < -1 || result > 1)
							start_ver.y -= aya;
						start_ver.y -= start_ver.altitude;
						res = start_res_two;
					}
					else
					{
						start_res_two = 0;
						res = start_res_two;
						start_ver.y = start_ver.y + (tan(radian) / (end_ver.x - start_ver.x));
					}
					/*aya = end_ver.z - start_ver.y;
					if (start_ver.altitude > 0)
						start_ver.y = start_ver.y - (tan(radian) * (end_ver.x - start_ver.x));
					else if (start_hor->altitude < 0)
						start_ver.y = start_ver.y - (tan(radian) / (end_ver.x - start_ver.x));
					else
						start_ver.y = start_ver.y - (tan(radian) / (end_ver.x - start_ver.x));
					if (start_ver.altitude != 0)
					{
						start_ver.y -= aya;
						start_ver.y -= start_ver.altitude;
					}*/
					/*if (start_ver.altitude > 0)
					{
						if (start_ver.altitude == old_res_two)
						{
							if (start_res_two == 0)
								start_res_two = 1;
						}
						if (start_ver.altitude > old_res_two)
							start_res_two = start_res_two + 1;
						if (start_ver.altitude < old_res_two)
							start_res_two = start_res_two - 1;
						aya = (end_ver.z - start_ver.y) * start_res_two;
						start_ver.y = start_ver.y - (tan(radian) * (end_ver.x - start_ver.x));
						if (start_res_two > 1)
							start_ver.y -= aya;
						start_ver.y -= start_ver.altitude;
						old_res_two = start_ver.altitude;
					}*/
				}
				if (end_ver.altitude > 0)
				{
					if (start_ver.altitude == end_ver.altitude)
					{
						//if (res == 0)
						//	res = 1;
					}
					if (start_ver.altitude > end_ver.altitude)
						res = res - 1;
					if (end_ver.altitude > start_ver.altitude)
						res = res + 1;
					aya = (end_ver.z - end_ver.y) * res;
					end_ver.y = end_ver.y + (tan(radian) / (end_ver.x - start_ver.x));
					//if (res < -1 || res > 1)
						end_ver.y -= aya;
					end_ver.y -= end_ver.altitude;
					bresenham(thread, *start_hor, start_ver);
				}
				else if (end_ver.altitude < 0)
				{
					if (start_ver.altitude > end_ver.altitude)
					{
						res = res - 1;
					}
					else if (end_ver.altitude > start_ver.altitude)
					{
						res = res + 1;
					}
					else if (end_ver.altitude == start_ver.altitude)
					{
						//if (res == 0)
						//	res = 1;
					}
					aya = (end_ver.z - end_ver.y) * res;
					end_ver.y = end_ver.y + (tan(radian) * (end_ver.x - start_ver.x));
					//if (res < -1 || res > 1)
						end_ver.y -= aya;
					end_ver.y -= end_ver.altitude;
					bresenham(thread, *start_hor, start_ver);
				}
				else
				{
					res = 0;
					end_ver.y = end_ver.y + (tan(radian) * (end_ver.x - start_ver.x));;
					bresenham(thread, *start_hor, start_ver);
				}
			}
			j_mem = 0;
			start_hor->y = end_hor->y;
			start_ver.y = end_ver.y;
			end_hor->y = end_hor->z;
			end_ver.y = end_ver.z;
			start_hor->x = end_hor->x;
			start_ver.x = end_ver.x;
		}
		result = 0;
		res = 0;
		start = 0;
		start_hor->altitude = 0;
		end_hor->altitude = 0;
		start_ver.altitude = 0;
		end_ver.altitude = 0;
		test=0;
		start_hor->x = x;
		end_hor->x = x;
		start_ver.x = x;
		end_ver.x = x;
		start_hor->y = y;
		end_hor->y = y;
		i++;
	}
}

void	get_segment(t_thread *thread)
{
	t_segment	seg_start;
	t_segment	seg_end;

	seg_start.altitude = 0;
	seg_start.x = 0;
	seg_start.y = 0;
	seg_start.z = 0;
	seg_end.altitude = 0;
	seg_end.x = 0;
	seg_end.y = 0;
	seg_end.z = 0;
	thread->colour = get_colour(thread->mlx.mlx_ptr);
	read_row(thread, &seg_start, &seg_end);
}
