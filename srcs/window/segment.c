/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:52:59 by gchopin           #+#    #+#             */
/*   Updated: 2021/07/28 23:00:06 by gchopin          ###   ########.fr       */
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

char	*get_altitude_two(int *j, char *line, int start)
{
	char	*str;

	str = NULL;
	if (line)
	{
		while (line[*j] && ft_isdigit(line[*j]))
			(*j)++;
		if (line[start - 1] == '-')
			str = ft_substr(line, (unsigned int)start - 1, *j - (start - 1));
		else
			str = ft_substr(line, (unsigned int)start, *j - start);
		if (line && line[*j] == ',')
			while (line[*j] && line[*j] != ' ')
				(*j)++;
	}
	return (str);
}
int	get_altitude(t_thread *thread, t_segment *segment, char *line, int j)
{
	char	*str;
	int	start;

	str = NULL;
	if  (line == NULL)
		close_program_error(thread, "Map must not be empty.", 2);
	while (line[j] && ft_isdigit(line[j]) == 0)
		j++;
	if (ft_isdigit(line[j]))
	{
		start = j;
		str = get_altitude_two(&j, line, start);
		if (str == NULL)
			close_program_error(thread, "No number returned\n", 2);
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

int	which_altitude(int altitude_one, int altitude_two, int *result)
{
	
		*result = 1;
	return (0);
}

void	start_draw_first_line(t_thread *thread, int *result, int *old_res_one)
{
	double	radian;
	int	add_altitude;

	radian = 0.61;
	/*add_altitude =*/ which_altitude(thread->segment[0].altitude, *old_res_one, result);
	/*if (add_altitude > 0)
		*result += (thread->segment[1].z - thread->segment[0].y);
	else if (add_altitude < 0)
		*result -= (thread->segment[1].z - thread->segment[0].y);
	*/if (thread->segment[0].altitude > 0)
	{
	//	thread->segment[0].y -= (thread->segment[0].altitude) + tan(radian)  * (thread->segment[1].x - thread->segment[0].x);
		thread->segment[0].y -= thread->segment[0].altitude * (sin(radian) * ((thread->segment[1].x - thread->segment[0].x) + (thread->segment[1].z - thread->segment[1].y))); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		//thread->segment[0].y -= thread->segment[0].altitude + tan(radian);
		//add_altitude = (thread->segment[1].z - thread->segment[0].y) * *result; //thread->segment[0].altitude;
		//thread->segment[0].y -= *result; //add_altitude;
		//thread->segment[0].y -= (thread->segment[0].altitude) / sin(radian);
		*old_res_one = thread->segment[0].altitude;
	}
	else if (thread->segment[0].altitude < 0)
	{
		//add_altitude = (thread->segment[1].z - thread->segment[0].y) * *result; //thread->segment[0].altitude;
		//thread->segment[0].y -= (thread->segment[0].altitude) + tan(radian)  * (thread->segment[1].x - thread->segment[0].x);
		thread->segment[0].y -= thread->segment[0].altitude * (sin(radian) * ((thread->segment[1].x - thread->segment[0].x) + (thread->segment[1].z - thread->segment[1].y))); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		//thread->segment[0].y -= *result; //add_altitude;
		//thread->segment[0].y -= (thread->segment[0].altitude) / sin(radian);
		*old_res_one = thread->segment[0].altitude;
	}
	else
	{
		//add_altitude = (thread->segment[1].z - thread->segment[0].y) * *result; //thread->segment[0].altitude;
		//thread->segment[0].y -= /*(thread->segment[0].altitude) + tan(radian)  **/ (thread->segment[1].x - thread->segment[0].x);
		//thread->segment[0].y -= *result; //add_altitude;
	//	thread->segment[0].y -= (thread->segment[0].altitude) / sin(radian);
		*old_res_one = thread->segment[0].altitude;
	}
}

void	start_draw_second_line(t_thread *thread, int *result)
{
	double	radian;
	int	add_altitude;

	radian = 0.61;
	/*add_altitude =*/ which_altitude(thread->segment[2].altitude, thread->segment[0].altitude, result);
	/*if (add_altitude > 0)
		*result += (thread->segment[3].z - thread->segment[2].y);
	else if (add_altitude < 0)
		*result -= (thread->segment[3].z - thread->segment[2].y);
	*/if (thread->segment[2].altitude > 0)
	{
		//thread->segment[2].y -= (thread->segment[2].altitude) + tan(radian)  * (thread->segment[3].x - thread->segment[2].x);
		//thread->segment[2].y -= (thread->segment[3].z - thread->segment[3].y);
		thread->segment[2].y -= thread->segment[2].altitude * (sin(radian) * ((thread->segment[3].x - thread->segment[2].x) + (thread->segment[3].z - thread->segment[3].y))); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		//add_altitude = (thread->segment[3].z - thread->segment[2].y) * *result; //thread->segment[2].altitude;
		//thread->segment[2].y -= add_altitude;
		//thread->segment[2].y -= (thread->segment[2].altitude) / sin(radian);
	}
	else if (thread->segment[2].altitude < 0)
	{
		//thread->segment[2].y += (thread->segment[3].z - thread->segment[3].y);
		thread->segment[2].y -= thread->segment[2].altitude * (sin(radian) * ((thread->segment[3].x - thread->segment[2].x) + (thread->segment[3].z - thread->segment[3].y))); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		//add_altitude = (thread->segment[3].z - thread->segment[2].y) * *result; //thread->segment[2].altitude;
		//add_altitude = (thread->segment[3].z - thread->segment[2].y) * *result; //thread->segment[2].altitude;
		//thread->segment[2].y -= add_altitude;
	//	thread->segment[2].y -= (thread->segment[2].altitude) / sin(radian);
	}
	else
	{
		//thread->segment[2].y -= /*(thread->segment[2].altitude) + tan(radian)  **/ (thread->segment[3].x - thread->segment[2].x);
		//add_altitude = (thread->segment[3].z - thread->segment[2].y) * *result; //thread->segment[2].altitude;
		//thread->segment[2].y = (thread->segment[2].altitude) + (tan(radian));// * (thread->segment[3].x - thread->segment[2].x));
		//thread->segment[2].y -= add_altitude;
	//	thread->segment[2].y -= (thread->segment[2].altitude) / sin(radian);
	}
}

void	draw_first_line(t_thread *thread, int *result)
{
	int	add_altitude;
	double	radian;

	radian = 0.61;
	/*add_altitude =*/ which_altitude(thread->segment[1].altitude, thread->segment[0].altitude, result);
	/*if (add_altitude > 0)
		*result += (thread->segment[1].z - thread->segment[1].y);
	else if (add_altitude < 0)
		*result -= (thread->segment[1].z - thread->segment[1].y);
	*/
	if (thread->segment[1].altitude > 0)
	{
		//add_altitude = (thread->segment[1].z - thread->segment[1].y) * *result;
		thread->segment[1].y -= thread->segment[1].altitude * (sin(radian) * ((thread->segment[1].x - thread->segment[0].x) + (thread->segment[1].z - thread->segment[1].y))); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		//thread->segment[1].y -= add_altitude;
		//thread->segment[1].y -= thread->segment[1].altitude / sin(0.61);
		bresenham(thread, thread->segment[0], thread->segment[1]);
	}
	else if (thread->segment[1].altitude < 0)
	{
		//add_altitude = (thread->segment[1].z - thread->segment[1].y) * *result;
		//thread->segment[1].y -= thread->segment[1].altitude;// + tan(radian); /// (thread->segment[1].x + thread->segment[0].x));
		//thread->segment[1].y -= thread->segment[1].altitude + (cos(radian) * (thread->segment[1].z - thread->segment[1].y)); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		thread->segment[1].y -= thread->segment[1].altitude * (sin(radian) * ((thread->segment[1].x - thread->segment[0].x) + (thread->segment[1].z - thread->segment[1].y))); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		//thread->segment[1].y -= add_altitude;
		//thread->segment[1].y -= (thread->segment[1].altitude) / sin(0.52);
		bresenham(thread, thread->segment[0], thread->segment[1]);
	}
	else
	{
		//add_altitude = (thread->segment[1].z - thread->segment[1].y) * *result;
		//thread->segment[1].y -= thread->segment[1].altitude; //+ tan(radian);// / (thread->segment[1].x + thread->segment[0].x));
		//thread->segment[1].y -= thread->segment[1].altitude; //+ (cos(radian) * (thread->segment[1].z - thread->segment[1].y)); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		//thread->segment[1].y -= thread->segment[1].altitude + (tan(radian) * ((thread->segment[1].x - thread->segment[0].x) + thread->segment[1].z - thread->segment[1].y)); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		//thread->segment[1].y -= add_altitude;
	//	thread->segment[1].y -= add_altitude;
	//	thread->segment[1].y -= (thread->segment[1].altitude) / sin(0.52);
		bresenham(thread, thread->segment[0], thread->segment[1]);
	}
}

void	draw_second_line(t_thread *thread, int *result)
{
	double	radian;
	int	add_altitude;

	radian = 0.61;
	/*add_altitude =*/ which_altitude(thread->segment[3].altitude, thread->segment[2].altitude, result);
	/*if (add_altitude > 0)
		*result += (thread->segment[3].z - thread->segment[3].y);
	else if (add_altitude < 0)
		*result -= (thread->segment[3].z - thread->segment[3].y);
	*/
	if (thread->segment[3].altitude > 0)
	{
		//thread->segment[3].y -= (thread->segment[3].altitude); //+ tan(radian); /// (thread->segment[3].x - thread->segment[2].x));
		//thread->segment[3].y -= thread->segment[3].altitude + (cos(radian) * ((thread->segment[3].z - thread->segment[3].y))); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		thread->segment[3].y -= thread->segment[3].altitude * (sin(radian) * ((thread->segment[3].x - thread->segment[2].x) + (thread->segment[3].z - thread->segment[3].y))); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		//add_altitude = (thread->segment[3].z - thread->segment[3].y) * *result;
		//thread->segment[3].y -= add_altitude;
		//thread->segment[3].y -= (thread->segment[3].altitude) / (sin(0.52));
		bresenham(thread, thread->segment[0], thread->segment[2]);
	}
	else if (thread->segment[3].altitude < 0)
	{
		//add_altitude = (thread->segment[3].z - thread->segment[3].y) * *result;
		//thread->segment[3].y -= (thread->segment[3].altitude);// + tan(radian); /// (thread->segment[3].x - thread->segment[2].x));
		//thread->segment[3].y -= thread->segment[3].altitude + (cos(radian) * ((thread->segment[3].z - thread->segment[3].y))); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		thread->segment[3].y -= thread->segment[3].altitude * (sin(radian) * ((thread->segment[3].x - thread->segment[2].x) + (thread->segment[3].z - thread->segment[3].y))); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		//thread->segment[3].y -= add_altitude;
		//thread->segment[3].y -= (thread->segment[3].altitude) / sin(0.52);
		bresenham(thread, thread->segment[0], thread->segment[2]);
	}
	else
	{
		//add_altitude = (thread->segment[3].z - thread->segment[3].y) * *result;
		//thread->segment[3].y -= (thread->segment[3].altitude); //+ tan(radian); /// (thread->segment[3].x - thread->segment[2].x));
		//thread->segment[3].y -= thread->segment[3].altitude; //+ (cos(radian) * ((thread->segment[3].z - thread->segment[3].y))); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		//thread->segment[3].y -= thread->segment[3].altitude + (tan(radian) * ((thread->segment[3].x - thread->segment[2].x) + thread->segment[3].z - thread->segment[3].y)); //+ tan(radian); /// (thread->segment[1].x + thread->segment[0].x);
		//thread->segment[3].y -=itude;
		//thread->segment[3].y -= (thread->segment[3].altitude) / sin(0.52);
		bresenham(thread, thread->segment[0], thread->segment[2]);
	}
}

void	draw_row_part_one(t_thread *thread, int *result_one, int *old_res_one, int *result)
{
	thread->segment[1].x = (thread->segment[1].x + thread->std_segment_x);
	thread->segment[1].z = thread->segment[1].y + (tan(0.61) * (thread->segment[1].x - thread->segment[0].x));
	if (thread->start_two == 0)
	{
		thread->segment[2].y = thread->segment[1].z;
		thread->segment[3].y = thread->segment[1].z;
	}
	if (thread->start_one == 0)
	{
		thread->start_one = 1;
		thread->segment[0].y -= (thread->segment[1].z - thread->segment[0].y);
		start_draw_first_line(thread, result_one, old_res_one);
		*result = *result_one;
	}
	draw_first_line(thread, result);
}

void	draw_row_part_two(t_thread *thread, int *result_two, int *result, int *start_value)
{
	if (thread->start_two == 0)
	{
		thread->save_x = (thread->segment[2].x - thread->std_segment_x);
		thread->segment[2].x = thread->save_x;
		thread->segment[3].x -= thread->std_segment_x;
	}
	thread->segment[3].x = thread->segment[3].x + thread->std_segment_x;
	thread->segment[3].z = thread->segment[3].y + (tan(0.61) * (thread->segment[3].x - thread->segment[2].x));
	if (thread->start_two == 0)
	{
		thread->start_two = 1;
		thread->save_y = thread->segment[1].z;
		thread->segment[2].y -= (thread->segment[3].z - thread->segment[2].y);
		start_draw_second_line(thread, result_two);
		*result = *result_two;
	}
	draw_second_line(thread, result);
}

void	read_row(t_thread *thread)
{
	int	i;
	int	j_one;
	int	j_two;
	int	j_mem;
	int	result_one;
	int	result_two;
	int	result_three;
	int	result_four;
	int	old_res_one;
	int	keep;

	keep = 0;
	i = 0;
	result_one = 0;
	result_two = 0;
	result_three = 0;
	result_four = 0;
	get_altitude(thread, &thread->segment[0], thread->lines[i], 0);
	old_res_one = thread->segment[0].altitude;
	while (thread->lines[i] != 0)
	{
		j_one = 0;
		j_two = 0;
		while (thread->lines[i][j_one])
		{
			j_one = get_altitude(thread, &thread->segment[0], thread->lines[i], j_one);
			if (thread->lines[i][j_one])
			{
				j_mem = get_altitude(thread, &thread->segment[1], thread->lines[i], j_one);
				draw_row_part_one(thread, &result_one, &old_res_one, &result_three);
			}
			if (thread->lines[i + 1])
			{
				j_two = get_altitude(thread, &thread->segment[2], thread->lines[i + 1], j_two);
				if (thread->lines[i + 1][j_two])
					j_mem = get_altitude(thread, &thread->segment[3], thread->lines[i + 1], j_two);
				draw_row_part_two(thread, &result_two, &result_four, &keep);
			}
			j_mem = 0;
			thread->segment[0].y = thread->segment[1].y;
			thread->segment[2].y = thread->segment[3].y;
			thread->segment[1].y = thread->segment[1].z;
			thread->segment[3].y = thread->segment[3].z;
			thread->segment[0].x = thread->segment[1].x;
			thread->segment[2].x = thread->segment[3].x;
		}
		//result_one = 0;
		//result_two = 0;
		thread->start_one = 0;
		thread->start_two = 0;
		thread->segment[0].altitude = 0;
		thread->segment[1].altitude = 0;
		thread->segment[2].altitude = 0;
		thread->segment[3].altitude = 0;
		thread->segment[0].x = thread->save_x;
		thread->segment[1].x = thread->save_x;
		thread->segment[2].x = thread->save_x;
		thread->segment[3].x = thread->save_x;
		thread->segment[0].y = thread->save_y;
		thread->segment[1].y = thread->save_y;
		i++;
	}
}

void	get_segment(t_thread *thread)
{
	thread->colour = get_colour(thread->mlx.mlx_ptr);
	if (!mlx_get_screen_size(thread->mlx.mlx_ptr, &thread->segment[1].x, &thread->segment[0].y))
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
	read_row(thread);
}
