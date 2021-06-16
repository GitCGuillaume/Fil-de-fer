/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:52:59 by gchopin           #+#    #+#             */
/*   Updated: 2021/06/16 20:58:02 by gchopin          ###   ########.fr       */
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
	while (line[j] && ft_isprint(line[j]) == 0)
		j++;
	while (line[j] && ft_isdigit(line[j]) == 0)
		j++;
/*	if (line[j] && ft_isdigit(line[j]) == 1)
	{
	}*/
	if (ft_isdigit(line[j]))
	{
		start = j;
		while (line[j] && ft_isdigit(line[j]))
			j++;
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
	double	radian_hor;
	double	radian_ver;
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
int result;
result = 0;
	i = 0;
	j_one = 0;
	j_two = 0;
	if (!mlx_get_screen_size(thread->mlx.mlx_ptr, &size_x, &size_y))
		close_program_error(thread, "Couldn't get resolution screen.\n", 2);
	start_hor->y = size_y * 0.25;
	start_ver.y = size_y * 0.25;
	end_hor->x = size_x * 0.25;
	start_hor->x = size_x * 0.25;
	end_hor->y = start_hor->y;
	end_ver.y = start_ver.y;
	start_ver.x = size_x * 0.25;
	end_ver.x = size_x * 0.25;
	x = start_hor->x;
	a.x = end_ver.x;
	a.y = start_ver.y;
	end_ver.z = end_ver.y;
	y = end_ver.y;
	radian_hor = 0.61;
	radian_ver = 0.61;
	end_hor->z = end_hor->y;
	start_ver.altitude = 0;
	start_hor->altitude = 0;
	end_ver.altitude = 0;
	end_hor->altitude = 0;
	start = 0;
	while (thread->lines[i] != 0)
	{
		j_one = 0;
		j_two = 0;
		while (thread->lines[i][j_one])
		{
			j_one = get_altitude(thread, start_hor, thread->lines[i], j_one);
			if (thread->lines[i][j_one])
			{
				j_mem = j_one;
				j_mem = get_altitude(thread, end_hor, thread->lines[i], j_mem);
				end_hor->x = end_hor->x + thread->std_segment_x;
				end_hor->z = end_hor->y + (tan(radian_hor) * (end_hor->x - start_hor->x)); //- end_hor->altitude;
				/*if (start == 0)
				{
					start = 1;
					printf("start=%d end=%d", start_hor->altitude, end_hor->altitude);
					{
						start_hor->y -= start_hor->altitude;
						start_hor->y = start_hor->y + (tan(radian_hor) / (end_hor->x - start_hor->x)); //- start_hor->altitude;
					}
					{
						start_hor->y -= start_hor->altitude;
						start_hor->y = start_hor->y + (tan(radian_hor) * (end_hor->x - start_hor->x)); //- start_hor->altitude;
					}
					else
					{
						start_hor->y = start_hor->y + (tan(radian_hor) * (end_hor->x - start_hor->x));//  - start_hor->altitude;
					}
				}
				*/
				if (start == 0)
				{
					start = 1;
					if (start_hor->altitude > 0) //&& start_hor->altitude != end_hor->altitude)
						start_hor->y = end_hor->y - (tan(radian_hor) * (end_hor->x - start_hor->x)) - start_hor->altitude;
					else if (start_hor->altitude < 0) //&& start_hor->altitude != end_hor->altitude)
						start_hor->y = end_hor->y - (tan(radian_hor) / (end_hor->x - start_hor->x)) - start_hor->altitude;
					else
						start_hor->y = end_hor->y - (tan(radian_hor) / (end_hor->x - start_hor->x));// - start_hor->altitude;
				}
				if (start_hor->altitude == end_hor->altitude && end_hor->altitude > 0)
				{
					end_hor->y = end_hor->y + (tan(radian_hor) / (end_hor->x - start_hor->x)) - end_hor->altitude;
				}
				else if (start_hor->altitude > end_hor->altitude && end_hor->altitude > 0)
				{
					end_hor->y = end_hor->y + (tan(radian_hor) / (end_hor->x - start_hor->x)) - end_hor->altitude;
				}
				else if (end_hor->altitude > start_hor->altitude && end_hor->altitude > 0)
				{
					end_hor->y = end_hor->y + (tan(radian_hor) / (end_hor->x - start_hor->x)) - end_hor->altitude;
				}
				else if (start_hor->altitude > end_hor->altitude && end_hor->altitude < 0)
				{
					end_hor->y = end_hor->y + (tan(radian_hor) * (end_hor->x - start_hor->x)) - end_hor->altitude;
				}
				else if (end_hor->altitude > start_hor->altitude && end_hor->altitude < 0)
				{
					end_hor->y = end_hor->y + (tan(radian_hor) * (end_hor->x - start_hor->x)) - end_hor->altitude;
				}
				else if (end_hor->altitude == start_hor->altitude && end_hor->altitude < 0)
				{
					end_hor->y = end_hor->y + (tan(radian_hor) * (end_hor->x - start_hor->x)) - end_hor->altitude;
				}
				else
					end_hor->y = end_hor->y + (tan(radian_hor) * (end_hor->x - start_hor->x));
				bresenham(thread, *start_hor, *end_hor);
			}
			if (thread->lines[i + 1] /*&& thread->lines[i + 1][j_one]*/)
			{
				start_ver.altitude = start_hor->altitude;
				start_ver.x = start_hor->x;
				start_ver.y = start_hor->y;
				end_ver.x = start_ver.x - thread->std_segment_x;
				j_two = get_altitude(thread, &end_ver, thread->lines[i + 1], j_two);
				//end_ver.y = start_hor->y + (tan(radian_hor) * (start_ver.x - end_ver.x)); //- end_ver.altitude;
				//j_mem = j_two;
				//j_mem = get_altitude(thread, &end_ver, thread->lines[i + 1], j_mem);
				if (x > end_ver.x)
					x = end_ver.x;
				int height;
				if (end_ver.altitude >= start_ver.altitude)
					height = end_ver.altitude - start_ver.altitude;
				else
					height = start_ver.altitude - end_ver.altitude;
				if (test == 0)
				{
					test = 1;
					y = end_hor->z;// - end_ver.altitude;
					/*if (start_ver.altitude == end_ver.altitude)
					{
						end_ver.y = end_ver.y + (tan(radian_ver) * (start_ver.x - end_ver.x)); //- end_ver.altitude;
						bresenham(thread, start_ver, end_ver);
					}
					else */
					/*if (end_ver.altitude > 0) //&& start_hor->altitude != end_hor->altitude)
					{
						end_ver.y = end_hor->z - (tan(radian_ver) * (start_ver.x - end_ver.x)) - end_ver.altitude;
						bresenham(thread, start_ver, end_ver);
					}
					else if (end_ver.altitude < 0) //&& start_hor->altitude != end_hor->altitude)
					{
						end_ver.y = end_hor->z - (tan(radian_ver) / (start_ver.x - end_ver.x)) - end_ver.altitude;
						bresenham(thread, start_ver, end_ver);
					}
					else
					{
						end_ver.y = end_hor->z - (tan(radian_ver) / (start_ver.x - end_ver.x)) - end_ver.altitude;
						bresenham(thread, start_ver, end_ver);
					}*/
				}
				if (thread->lines[i + 1][j_two])
				{
					if (end_ver.altitude > 0) //&& start_hor->altitude != end_hor->altitude)
					{
						end_ver.y = end_hor->z - (tan(radian_ver) * (start_ver.x - end_ver.x)) - end_ver.altitude;
					}
					else if (end_ver.altitude < 0) //&& start_hor->altitude != end_hor->altitude)
					{
						end_ver.y = end_hor->z - (tan(radian_ver) / (start_ver.x - end_ver.x)) - end_ver.altitude;
					}
					else
					{
						end_ver.y = end_hor->z - (tan(radian_ver) / (start_ver.x - end_ver.x)); //- end_ver.altitude;
					}
					bresenham(thread, start_ver, end_ver);
				}
				else
				{
					if (end_ver.altitude > 0) //&& start_hor->altitude != end_hor->altitude)
					{
						end_ver.y = end_hor->z + (tan(radian_ver) / (start_ver.x - end_ver.x)) - end_ver.altitude;
					}
					else if (end_ver.altitude < 0) //&& start_hor->altitude != end_hor->altitude)
					{
						end_ver.y = end_hor->z + (tan(radian_ver) * (start_ver.x - end_ver.x)) - end_ver.altitude;
					}
					else
					{
						end_ver.y = end_hor->z + (tan(radian_ver) * (start_ver.x - end_ver.x)); //- end_ver.altitude;
					}
					bresenham(thread, start_ver, end_ver);
				}
					//
				//		bresenham(thread, start_ver, end_ver);
				//	start_ver.altitude = end_ver.altitude;
				
				//end_ver.y = end_ver.z;
				//result = start_ver.altitude - end_ver.altitude;
				//if (0>result)
				/*if (end_ver.altitude > start_ver.altitude)
					end_ver.y = end_hor->y - end_ver.altitude; //+ tan(radian_ver) * (start_ver.x - end_ver.x);// - end_ver.altitude;
				else if (start_ver.altitude > end_ver.altitude)
					end_ver.y = end_hor->y - end_ver.altitude; //+ tan(radian_ver) * (start_ver.x - end_ver.x);// - end_ver.altitude;
				else
					end_ver.y += tan(radian_ver) * (start_ver.x - end_ver.x);
				bresenham(thread, start_ver, end_ver);
				*/
			//	if (end_ver.altitude > start_ver.altitude)
			//		end_ver.y = tan(radian_ver) * (start_ver.x - end_ver.x) - end_ver.altitude;
				/*else if (start_ver.altitude > end_ver.altitude)
					end_ver.y = end_hor->y - end_ver.altitude; //+ tan(radian_ver) * (start_ver.x - end_ver.x);// - end_ver.altitude;
				else
					end_ver.y += tan(radian_ver) * (start_ver.x - end_ver.x);
				*/
				//result = 0;
				//end_ver.y = start_ver.y + (tan(radian_ver) * (start_ver.x - end_ver.x)); //- end_ver.altitude;
			
					//	end_ver.z = start_ver.y + (tan(radian_ver) * (start_ver.x - end_ver.x));
			}
			j_mem = 0;
			start_hor->y = end_hor->y;
			end_hor->y = end_hor->z;
			start_hor->x = end_hor->x;
		}
		start = 0;
		start_hor->altitude = 0;
		end_hor->altitude = 0;
		start_ver.altitude = 0;
		end_ver.altitude = 0;
		test=0;
		//start_hor->altitude = 0;
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

	thread->colour = get_colour(thread->mlx.mlx_ptr);
	read_row(thread, &seg_start, &seg_end);
	//read_column(thread, &seg_start, &seg_end);
}
