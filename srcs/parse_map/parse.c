/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 14:02:41 by gchopin           #+#    #+#             */
/*   Updated: 2021/05/30 12:32:01 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
}

void	ft_min_max(t_thread *thread, char *str)
{
	printf("str=%s\n", str);
	if (str == NULL)
		close_program_error(thread, "Line NULL\n", 2);
	if (str[0] == '-')
		if (ft_isdigit(str[1]) == 0)
			close_program_error(thread, "Number must have 0 or 1 minus.", 2);
	if (ft_atoi(str) > 2147483647 || ft_atoi(str) < -2147483648)
		close_program_error(thread, "Number must be between -2147483648 and 2147483647", 2);
}

int	check_lines(t_thread *thread)
{
	char	*str;
	int	result;
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	if  (thread->lines == NULL)
		close_program_error(thread, "Map must not be empty.", 2);
	result = start_digit(thread->lines);
	if (result == 0)
		close_program_error(thread, "Line must start with a digit or negative.", 2);
	while (thread->lines[i])
	{
		while (thread->lines[i][j] != '\0')
		{
			if (thread->lines[i][j] == '-')
				j++;
			start = j;
			printf("?=%c\n", thread->lines[i][j]);
			if (thread->lines[i][j] == '-')
				close_program_error(thread, "Number must have 0 or 1 minus.", 2);
			while (thread->lines[i][j] >= '0' && thread->lines[i][j] <= '9')
				j++;
			if (thread->lines[i][start - 1] == '-')
				str = ft_substr(thread->lines[i], (unsigned int)start - 1, j - (start - 1));
			else
				str = ft_substr(thread->lines[i], (unsigned int)start, j - start);
			if (str == NULL)
				close_program_error(thread, "No number returned\n", 2);
			ft_min_max(thread, str);
			if (thread->lines[i][j] != '\0' && thread->lines[i][j] == ' ')
				j++;
			if (thread->lines[i][j] != '\0' && thread->lines[i][j] == ' ')
				close_program_error(thread, "Must have only 1 space after number", 2);
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
