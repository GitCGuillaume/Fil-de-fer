/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:55:10 by gchopin           #+#    #+#             */
/*   Updated: 2021/09/28 19:57:01 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	int		start;

	str = NULL;
	if (line == NULL)
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
