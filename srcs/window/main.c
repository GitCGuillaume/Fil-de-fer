/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 11:07:15 by gchopin           #+#    #+#             */
/*   Updated: 2021/06/02 16:20:37 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_keypress(int keypress, void *param)
{
	if (keypress == 65307)
		close_program_esc((t_thread *)param);
	return (0);
}

int	render_wireframe(void *param)
{
	t_thread	*thread;
	int	size_x;
	int	size_y;

	thread = (t_thread *)param;
	thread->mlx.mlx_img = NULL;
	if (!mlx_get_screen_size(thread->mlx.mlx_ptr, &size_x, &size_y))
		close_program_error(thread, "Couldn't get resolution screen.\n", 2);
	if (size_x <= 320 || size_y <= 200)
		close_program_error(thread, "resolution must be at least 320x200.\n", 2);
	thread->mlx.mlx_img = mlx_new_image(thread->mlx.mlx_ptr, size_x, size_y);
	if (thread->mlx.mlx_img == NULL)
		close_program_error(thread, "Couldn't create image.\n", 2);
	thread->mlx.mlx_get_data = mlx_get_data_addr(thread->mlx.mlx_img,
			&thread->mlx.bpp, &thread->mlx.size_line, &thread->mlx.endian);
	if (thread->mlx.mlx_get_data == NULL)
	close_program_error(thread, "Can't draw in image's data.\n", 2);
	mlx_put_image_to_window(thread->mlx.mlx_ptr, thread->mlx.mlx_win,
			thread->mlx.mlx_img, size_x, size_y);
	return (0);
}

void	init_window(t_thread *thread)
{
	int	size_x;
	int	size_y;

	size_x = 0;
	size_y = 0;
	thread->mlx.mlx_ptr = mlx_init();
	if (!mlx_get_screen_size(thread->mlx.mlx_ptr, &size_x, &size_y))
		close_program_error(thread, "Couldn't get resolution screen.\n", 2);
	if (size_x <= 320 || size_y <= 200)
		close_program_error(thread, "resolution must be at least 320x200.\n", 2);
	thread->std_segment_x = size_y / thread->nb_segment;
	thread->std_segment_y = size_y / thread->nb_segment;
	thread->mlx.mlx_win = mlx_new_window(thread->mlx.mlx_ptr, size_x, size_y, "Wireframe");
	mlx_hook(thread->mlx.mlx_win, KEYPRESS,
			KEYPRESS_P_M, ft_keypress, (void *)thread);
	mlx_hook(thread->mlx.mlx_win, KEYRELEASE,
			KEYPRESS_R_M, ft_keypress, (void *)thread);
	mlx_hook(thread->mlx.mlx_win, CLIENT_MESSAGE,
			STRUCT_MASK, close_program_esc, (void *)thread);
	mlx_loop_hook(thread->mlx.mlx_win, render_wireframe, (void *)thread);
	mlx_loop(thread->mlx.mlx_ptr);
}