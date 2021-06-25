/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 11:07:15 by gchopin           #+#    #+#             */
/*   Updated: 2021/06/24 22:16:07 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_keypress(int keypress, void *param)
{
	t_thread *thread;

	thread = param;
	if (keypress == 65307)
		close_program_esc((t_thread *)param);
	if (keypress == 65361)
		thread->mov_lr -=1;
	else if (keypress == 65363)
		thread->mov_lr +=1;
	else if (keypress == 65362)
		thread->mov_ud -=1;
	else if (keypress == 65364)
		thread->mov_ud += 1;
	printf("lr=%d ud=%d\n", thread->mov_lr, thread->mov_ud);
	printf("keypress=%d\n",keypress);
	return (0);
}

int	render_wireframe(void *param)
{
	t_thread	*thread;
	int	size_x;
	int	size_y;

	thread = (t_thread *)param;
	if (thread->mlx.mlx_img)
		if (mlx_destroy_image(thread->mlx.mlx_ptr, thread->mlx.mlx_img))
			close_program_error(thread, "Couldn't destroy image\n", 2);
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

size_t	ratio_map(int number, int nb_segment, int multiply)
{
	double	scale_factor;

	scale_factor = number * multiply;
	printf("scale1=%f\n", scale_factor);
	scale_factor = scale_factor / nb_segment;
	printf("scale2=%f\n", scale_factor);
	scale_factor = 8 / scale_factor;
	printf("scale3=%f\n", scale_factor);
	scale_factor = scale_factor * multiply;
	printf("scale4=%f\n", scale_factor);
	scale_factor = ceil(scale_factor);
	printf("scale5=%f\n", scale_factor);
	//	if ((int)scale_factor == 0)
//		return (number / nb_segment);
	exit(0);
	return ((int)scale_factor);
}
double	div_math(double a, double b)
{
	double	value;

	value = a / b;
	return (value);
}

void	init_window(t_thread *thread)
{
	double	segment_size;
	size_t	nb_lines;
	int	size;
	nb_lines = ft_nb_lines(thread->lines);
	if (nb_lines == 0)
		close_program_error(thread, "Error\n", 2);
	thread->size_x = 0;
	thread->size_y = 0;
	thread->mlx.mlx_ptr = mlx_init();
	if (!mlx_get_screen_size(thread->mlx.mlx_ptr, &thread->size_x, &thread->size_y))
		close_program_error(thread, "Couldn't get resolution screen.\n", 2);
	if (thread->size_x <= 320 || thread->size_y <= 200)
		close_program_error(thread, "resolution must be at least 320x200.\n", 2);
	//thread->std_segment_x = ratio_map(thread->size_y, thread->nb_segment, 1);
	//thread->std_segment_y = ratio_map(thread->size_y, thread->nb_segment, 1);
	thread->mov_lr = 0;
	thread->mov_ud = 0;
	thread->std_segment_x = ((thread->size_x / thread->size_y)*2) + (nb_lines / thread->nb_segment);
	thread->std_segment_y = ((thread->size_x / thread->size_y)*2) + (nb_lines / thread->nb_segment);
	//thread->std_segment_x = (thread->size_x*0.4) / thread->nb_segment;
	//thread->std_segment_y = (thread->size_y*0.4) / nb_lines;
	thread->mlx.mlx_win = mlx_new_window(thread->mlx.mlx_ptr, thread->size_x, thread->size_y, "Wireframe");
	mlx_hook(thread->mlx.mlx_win, KEYPRESS,
			KEYPRESS_P_M, ft_keypress, (void *)thread);
	mlx_hook(thread->mlx.mlx_win, KEYRELEASE,
			KEYPRESS_R_M, ft_keypress, (void *)thread);
	mlx_loop_hook(thread->mlx.mlx_ptr, &render_wireframe, (void *)thread);
	mlx_hook(thread->mlx.mlx_win, CLIENT_MESSAGE,
			STRUCT_MASK, close_program_esc, (void *)thread);
	mlx_loop(thread->mlx.mlx_ptr);
}
