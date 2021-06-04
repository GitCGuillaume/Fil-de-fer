/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:52:59 by gchopin           #+#    #+#             */
/*   Updated: 2021/06/04 22:59:25 by gchopin          ###   ########.fr       */
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

	if  (line == NULL)
		close_program_error(thread, "Map must not be empty.", 2);
	while (line[j] != '\0')
	{
		str = NULL;
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
		return (j);
	}
	return (j);
}


void	get_segment(t_thread *thread)
{
	t_segment	seg_start;
	t_segment	seg_end;
	int	i;
	int	j;
	int	colour;
int x;
int y;
	i = 0;
	j = 0;
	x = thread->std_segment_x;
	y = thread->std_segment_y;
	colour = get_colour(thread->mlx.mlx_ptr);
	if (thread->lines[i])
		j = get_altitude(thread, &seg_start, thread->lines[i], j);
	while (thread->lines[i] != 0)
	{
		j = 0;
		while (thread->lines[i][j])
		{
			if (thread->lines[i][j])
				j = get_altitude(thread, &seg_end, thread->lines[i], j);
			draw_pixel(thread, x, y, colour);
			//DRAW
			seg_start.altitude = seg_end.altitude;
			x += thread->std_segment_x;
			//exit(0);
			//j++;
		}
		seg_start.altitude = 0;
		seg_end.altitude = 0;
		i++;
		x = thread->std_segment_x;
		y += thread->std_segment_y;
	}
}
