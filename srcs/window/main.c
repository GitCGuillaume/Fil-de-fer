/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 11:07:15 by gchopin           #+#    #+#             */
/*   Updated: 2021/11/17 11:08:25 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_keypress(int keypress, void *param)
{
	t_thread	*thread;

	thread = param;
	if (keypress == 65307)
		close_program_esc((t_thread *)param);
	if (keypress == 65361)
		thread->mov_lr += 15;
	else if (keypress == 65363)
		thread->mov_lr -= 15;
	else if (keypress == 65362)
		thread->mov_ud += 15;
	else if (keypress == 65364)
		thread->mov_ud -= 15;
	return (0);
}

int	render_wireframe(void *param)
{
	t_thread	*thread;
	int			size_x;
	int			size_y;

	thread = (t_thread *)param;
	if (thread->mlx.mlx_img)
		if (mlx_destroy_image(thread->mlx.mlx_ptr, thread->mlx.mlx_img))
			close_program_error(thread, "Couldn't destroy image\n", 2);
	thread->mlx.mlx_img = NULL;
	mlx_get_screen_size(thread->mlx.mlx_ptr, &size_x, &size_y);
	//	close_program_error(thread, "Couldn't get resolution screen.\n", 2);
	if (size_x <= 320 || size_y <= 200)
		close_program_error(thread, "resolution must be at least 320x200.\n", 2);
	thread->mlx.mlx_img = mlx_new_image(thread->mlx.mlx_ptr, size_x, size_y);
	if (thread->mlx.mlx_img == NULL)
		close_program_error(thread, "Couldn't create image.\n", 2);
	thread->mlx.mlx_get_data = mlx_get_data_addr(thread->mlx.mlx_img,
			&thread->mlx.bpp, &thread->mlx.size_line, &thread->mlx.endian);
	if (thread->mlx.mlx_get_data == NULL)
		close_program_error(thread, "Can't draw in image's data.\n", 2);
	get_segment(thread);
	mlx_put_image_to_window(thread->mlx.mlx_ptr, thread->mlx.mlx_win,
		thread->mlx.mlx_img, 0, 0);
	return (0);
}

size_t	ft_nb_lines(char **lines)
{
	size_t	i;

	i = 0;
	if (lines == NULL)
		return (0);
	while (lines[i])
	{
		i++;
	}
	return (i);
}

void	wait_mlx_hook(t_thread *thread)
{
	mlx_hook(thread->mlx.mlx_win, KEYPRESS,
		1L << 0, ft_keypress, (void *)thread);
	mlx_hook(thread->mlx.mlx_win, KEYRELEASE,
		1L << 1, ft_keypress, (void *)thread);
	mlx_loop_hook(thread->mlx.mlx_ptr, &render_wireframe, (void *)thread);
	mlx_hook(thread->mlx.mlx_win, CLIENT_MESSAGE,
		1 << 17, close_program_esc, (void *)thread);
	mlx_loop(thread->mlx.mlx_ptr);
}

void	init_window(t_thread *thread)
{
	size_t	nb_lines;

	nb_lines = ft_nb_lines(thread->lines);
	if (nb_lines == 0)
		close_program_error(thread, "Error\n", 2);
	thread->mlx.mlx_ptr = mlx_init();
	if (thread->mlx.mlx_ptr == NULL)
		close_program_error(thread,
			"Couldn't init minilibx42.\n", 2);
	mlx_get_screen_size(thread->mlx.mlx_ptr,
			&thread->size_x, &thread->size_y);
	//close_program_error(thread,
	//	"Couldn't get resolution screen.\n", 2);
	if (thread->size_x <= 320 || thread->size_y <= 200)
		close_program_error(thread,
			"resolution must be at least 320x200.\n", 2);
	thread->std_segment_x = (thread->size_x) / thread->nb_segment;
	thread->mlx.mlx_win = mlx_new_window(thread->mlx.mlx_ptr,
			thread->size_x, thread->size_y, "Wireframe");
	if (thread->mlx.mlx_win == NULL)
		close_program_error(thread,
			"Couldn't display the wireframe.\n", 2);
	thread->colour = get_colour(thread->mlx.mlx_ptr);
	wait_mlx_hook(thread);
}
