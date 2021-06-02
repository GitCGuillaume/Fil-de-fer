/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 14:02:41 by gchopin           #+#    #+#             */
/*   Updated: 2021/06/02 10:33:52 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
int	start_digit(char **lines)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (lines)
	{
		while (lines[i])
		{
			j = 0;
			if (lines[i][j] != '\0' && lines[i][j] == '-')
				j++;
			if (lines[i][j] != '\0' && ft_isdigit(lines[i][j]) == 0)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}*/

void	ft_min_max(t_thread *thread, char *str)
{
	if (str == NULL)
		close_program_error(thread, "Line NULL\n", 2);
	if (str[0] == '-')
		if (ft_isdigit(str[1]) == 0)
			close_program_error(thread, "Number must have 0 or 1 minus.", 2);
	if (ft_atoi(str) > 2147483647 || ft_atoi(str) < -2147483648)
		close_program_error(thread, "Number must be between -2147483648 and 2147483647", 2);
}

void	convert_hexa(t_thread *thread, char *str, char **leak)
{
	double	power;
	double	nbr;
	char	*convert;
	int	max;

	max = ft_strlen(str) - 1;
	nbr = 0;
	if (str == NULL)
	{
		if (*leak != NULL)
			free(*leak);
		close_program_error(thread, "Hexa is NULL\n", 2);
	}
	if (str[0] == '0' && str[1] == 'x' && str[2] == '\0')
	{
		if (*leak != NULL)
			free(*leak);
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
				if (*leak != NULL)
					free(*leak);
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
				if (*leak != NULL)
					free(*leak);
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
				if (*leak != NULL)
					free(*leak);
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
}

int	check_lines(t_thread *thread)
{
	char	*str;
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	if  (thread->lines == NULL)
		close_program_error(thread, "Map must not be empty.", 2);
	while (thread->lines[i])
	{
		j = 0;
		while (thread->lines[i][j] != '\0')
		{
			str = NULL;
			while (ft_isdigit(thread->lines[i][j]) == 0)
				j++;
			start = j;
			while (thread->lines[i][j] >= '0' && thread->lines[i][j] <= '9')
				j++;
			if (thread->lines[i][j] == 'x')
			{
				j++;
				while ((thread->lines[i][j] >= 'A' && thread->lines[i][j] <= 'F')
						|| (thread->lines[i][j] >= 'a' && thread->lines[i][j] <= 'f')
						|| (thread->lines[i][j] >= '0' && thread->lines[i][j] <= '9'))
					j++;
				convert_hexa(thread, ft_substr(thread->lines[i], (unsigned int)start, j - start), &str);
			}
			if (thread->lines[i][start - 1] == '-')
				str = ft_substr(thread->lines[i], (unsigned int)start - 1, j - (start - 1));
			else
				str = ft_substr(thread->lines[i], (unsigned int)start, j - start);
			if (str == NULL)
				close_program_error(thread, "No number returned\n", 2);
			ft_min_max(thread, str);
			free(str);
			if (thread->lines[i][j] != '\0' && thread->lines[i][j] == ' ')
				j++;
			if (thread->lines[i][j] != '\0' && thread->lines[i][j] == ' ')
				close_program_error(thread, "Must have only 1 space after number", 2);
			thread->nb_segment = thread->nb_segment + 1;
		}
		i++;
	}
	return (0);
}

char	*split_line(t_thread *thread, char *str)
{
	char	*line;

	line = NULL;
	if (str && thread->line)
		line =	ft_strjoin(thread->line, str);
	free(thread->line);
	thread->line = NULL;
	free(str);
	if (line == NULL)
		close_program_error(thread, "An error occured while reading the map.", 2);
	str = ft_strjoin(line, "|");
	free(line);
	line = NULL;
	if (str == NULL)
		close_program_error(thread, "An error occured while reading the map.", 2);
	line = str;
	return (line);
}

void	get_line_fd(t_thread *thread)
{
	char	*tmp;
	int	ret;

	ret = 1;
	thread->line = ft_strdup("");
	tmp = NULL;
	if  (thread == NULL)
		close_program_error(thread, "Map is empty", 2);
	while (ret > 0)
	{
		ret = get_next_line(thread->fd, &tmp);
		if (tmp == NULL)
			close_program_error(thread, "Engine couldn't get the map's lines.", 2);
		if (ret > 0)
			thread->line = split_line(thread, tmp);
	}
	free(tmp);
}
