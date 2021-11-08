/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 14:02:41 by gchopin           #+#    #+#             */
/*   Updated: 2021/11/08 14:01:48 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_parse_min_max(t_thread *thread, char *str)
{
	if (str == NULL)
		close_program_error(thread, "Line NULL\n", 2);
	if (str[0] == '-')
		if (ft_isdigit(str[1]) == 0)
			close_program_error(thread, "Number must have 0 or 1 minus.", 2);
	if (ft_atoi(str) > 2147483647 || ft_atoi(str) < -2147483648)
		close_program_error(thread,
			"Number must be between -2147483648 and 2147483647", 2);
}

static void	get_number(t_thread *thread, int *i, int *j, int *current_nb)
{
	if (thread->lines[*i][*j] && ft_isdigit(thread->lines[*i][*j]) == 1)
	{
		while (thread->lines[*i][*j] && thread->lines[*i][*j] >= '0'
			&& thread->lines[*i][*j] <= '9')
			(*j)++;
		(*current_nb)++;
		if (thread->lines[*i][*j] && thread->lines[*i][*j] == ',')
			while (thread->lines[*i][*j] && thread->lines[*i][*j] != ' ')
				(*j)++;
	}
}

int	parse_check_lines(t_thread *thread)
{
	int	i;
	int	j;
	int	current_nb;

	i = 0;
	current_nb = 0;
	if (thread->lines == NULL)
		close_program_error(thread, "Map must not be empty.", 2);
	while (thread->lines[i])
	{
		j = 0;
		while (thread->lines[i][j] != '\0')
		{
			while (thread->lines[i][j] && ft_isprint(thread->lines[i][j]) == 0)
				j++;
			while (thread->lines[i][j] && ft_isdigit(thread->lines[i][j]) == 0)
				j++;
			get_number(thread, &i, &j, &current_nb);
		}
		if (current_nb >= thread->nb_segment)
			thread->nb_segment = current_nb;
		current_nb = 0;
		i++;
	}
	return (i);
}

char	*split_line(t_thread *thread, char *str)
{
	char	*line;

	line = NULL;
	if (str && thread->line)
		line = ft_strjoin(thread->line, str);
	free(thread->line);
	thread->line = NULL;
	free(str);
	if (line == NULL)
		close_program_error(thread,
			"An error occured while reading the map.", 2);
	str = ft_strjoin(line, "|");
	free(line);
	line = NULL;
	if (str == NULL)
		close_program_error(thread,
			"An error occured while reading the map.", 2);
	line = str;
	return (line);
}

void	get_line_fd(t_thread *thread)
{
	char	*tmp;
	int		ret;

	ret = 1;
	thread->line = ft_strdup("");
	tmp = NULL;
	if (thread == NULL)
		close_program_error(thread, "Map is empty", 2);
	while (ret > 0)
	{
		ret = get_next_line(thread->fd, &tmp);
		if (tmp == NULL)
			close_program_error(thread,
				"Engine couldn't get the map lines.", 2);
		if (ret > 0)
			thread->line = split_line(thread, tmp);
	}
	free(tmp);
}
