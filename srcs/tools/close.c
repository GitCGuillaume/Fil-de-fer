/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 12:38:58 by gchopin           #+#    #+#             */
/*   Updated: 2021/11/08 11:02:30 by gchopin          ###   ########.fr       */
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

int	close_program_esc(t_thread *thread)
{
	ft_putstr_fd("Close OK\n", 1);
	if (thread == NULL)
		exit(EXIT_FAILURE);
	if (thread->line != NULL)
		free(thread->line);
	clear_lines(thread);
	if (thread->mlx.mlx_img)
		mlx_destroy_image(thread->mlx.mlx_ptr, thread->mlx.mlx_img);
	if (thread->mlx.mlx_win)
		mlx_destroy_window(thread->mlx.mlx_ptr, thread->mlx.mlx_win);
	if (thread->mlx.mlx_ptr)
		free(thread->mlx.mlx_ptr);
	exit(0);
	return (0);
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
	if (thread->mlx.mlx_img)
		mlx_destroy_image(thread->mlx.mlx_ptr, thread->mlx.mlx_img);
	if (thread->mlx.mlx_win)
		mlx_destroy_window(thread->mlx.mlx_ptr, thread->mlx.mlx_win);
	if (thread->mlx.mlx_ptr)
		free(thread->mlx.mlx_ptr);
	exit(EXIT_FAILURE);
}
