/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 12:38:58 by gchopin           #+#    #+#             */
/*   Updated: 2021/05/29 19:23:38 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_lines(t_thread *thread)
{
	int	i;

	i = 0;
	if (thread->lines)
	{
		while (thread->lines[i])
		{
			free(thread->lines[i]);
			i++;
		}
		free(thread->lines);
	}
}

void	close_program_error(t_thread *thread, char *str, int fd)
{
	ft_putstr_fd("Error\n", 2);
	if (str != NULL)
		ft_putstr_fd(str, fd);
	if (thread == NULL)
		exit(EXIT_FAILURE);
	if (thread->line != NULL)
		free(thread->line);
	clear_lines(thread);
	exit(EXIT_FAILURE);
}
