/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 12:14:33 by gchopin           #+#    #+#             */
/*   Updated: 2021/05/29 19:48:58 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_open_fd(char *path)
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

int		ft_close_fd(int fd)
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

int	main(int argc, char **argv)
{
	t_thread	thread;
	char	*result;

	thread.fd = -1;
	if (argc != 2)
		close_program_error(0, "Wrong number of parameter.\n", 2);
	result = ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1]));
	if (result == NULL)
		close_program_error(0, "File format is wrong.\n", 2);
	if (ft_strcmp(result, ".fdf") != 0)
		close_program_error(0, "File extension format is wrong", 2);
	thread.fd = ft_open_fd(argv[1]);
	if (thread.fd != -1)
		get_line_fd(&thread);
	thread.lines = ft_split(thread.line, '|');
	check_lines(&thread);
	return (0);
}
