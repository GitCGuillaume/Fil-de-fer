/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 12:14:33 by gchopin           #+#    #+#             */
/*   Updated: 2021/11/08 12:14:27 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_open_fd(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\n", 2);
		perror("Can't open file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	ft_close_fd(int fd)
{
	int	quit;

	quit = -1;
	if (fd != -1)
		quit = close(fd);
	if (quit == -1)
	{
		ft_putstr_fd("Error\n", 2);
		perror("Can't close file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	init_null_struct(t_thread *thread)
{
	int	i;

	i = 0;
	thread->fd = -1;
	thread->nb_segment = 0;
	thread->nb_lines = 0;
	thread->line = NULL;
	thread->lines = NULL;
	thread->mlx.mlx_ptr = NULL;
	thread->mlx.mlx_win = NULL;
	thread->mlx.mlx_img = NULL;
	thread->mlx.mlx_get_data = NULL;
	thread->mlx.endian = 0;
	thread->size_x = 0;
	thread->size_y = 0;
	thread->mov_lr = 0;
	thread->mov_ud = 0;
	while (4 > i)
	{
		thread->segment[i].x = 100;
		thread->segment[i].y = 100;
		thread->segment[i].z = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_thread	thread;
	char		*result;

	init_null_struct(&thread);
	if (argc != 2)
		close_program_error(0, "Wrong number of parameter.\n", 2);
	result = ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1]));
	if (result == NULL)
		close_program_error(0, "File format is wrong.\n", 2);
	thread.fd = ft_open_fd(argv[1]);
	if (thread.fd != -1)
		get_line_fd(&thread);
	thread.lines = ft_split(thread.line, '|');
	parse_check_lines(&thread);
	init_window(&thread);
	close_program_error(&thread, "End of program", 2);
	return (0);
}
