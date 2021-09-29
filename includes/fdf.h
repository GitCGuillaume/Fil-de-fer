#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <errno.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# define CLIENT_MESSAGE 33
# define STRUCT_MASK 1 << 17
# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESS_P_M 1L << 0
# define KEYPRESS_R_M 1L << 1

typedef	struct	s_segment
{
	int	altitude;
	int	x;
	int	y;
	int	z;
	int	save_x;
	int	save_y;
}	t_segment;

typedef struct	s_mlx_fdf
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*mlx_img;
	char	*mlx_get_data;
	int	bpp;
	int	size_line;
	int	endian;
}	t_mlx_fdf;

typedef struct	s_thread
{
	t_mlx_fdf mlx;
	t_segment segment[4];
	char	**lines;
	char	*line;
	int	mov_lr;
	int	mov_ud;
	int	fd;
	int	nb_segment;
	int	nb_lines;
	int	std_segment_x;
	int	std_segment_y;
	int	size_x;
	int	size_y;
	int	colour;
	int	save_x;
	int	save_y;
	char	start_one;
	char	start_two;
}	t_thread;

/*
 ** Parse map
*/

void	ft_min_max(t_thread *thread, char *str);
void	get_line_fd(t_thread *thread);
int	check_lines(t_thread *thread);

/*
 ** Window
*/

int	ft_keypress(int keypress, void *param);
void	init_window(t_thread *thread);
void	get_segment(t_thread *thread);
void	bresenham(t_thread *thread, t_segment start, t_segment end);

/*
 ** Segment
*/

void	set_row(t_thread *thread);
void	set_column(t_thread *thread);
void	draw_first_line(t_thread *thread);
void	draw_second_line(t_thread *thread);
void	draw_row_part_one(t_thread *thread);
void	draw_row_part_two(t_thread *thread);
void	start_draw_first_line(t_thread *thread);
void	start_draw_second_line(t_thread *thread);

/*
 ** Bresenham
*/

void	fourth_segment(t_thread *thread, int *dp, t_segment *start, t_segment *end);
void	third_segment(t_thread *thread, int *dp, t_segment *start, t_segment *end);
void	second_segment(t_thread *thread, int *dp, t_segment *start, t_segment *end);
void	first_segment(t_thread *thread, int *dp, t_segment *start, t_segment *end);

/*
 ** Bresenham tools
*/

char	*get_altitude_two(int *j, char *line, int start);
int	get_altitude(t_thread *thread, t_segment *segment, char *line, int j);

/*
 ** Tools
*/

void	draw_pixel(t_thread *thread, int x, int y);
int	get_colour(void *mlx_ptr);
void	close_program_error(t_thread *thread, char *str, int fd);
int	close_program_esc(t_thread *thread);
void	ft_swap(int *a, int *b);
int	is_tab(char c);
int	is_jump(char c);
int	is_other(char c);

#endif
