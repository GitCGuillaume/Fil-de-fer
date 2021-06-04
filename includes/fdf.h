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
	char	**lines;
	char	*line;
	int	fd;
	int	nb_segment;
	int	std_segment_x;
	int	std_segment_y;
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

void	init_window(t_thread *thread);
void	get_segment(t_thread *thread);

/*
 ** Tools
*/

void	draw_pixel(t_thread *thread, int x, int y, int colour);
int	get_colour(void *mlx_ptr);
void	close_program_error(t_thread *thread, char *str, int fd);
int	close_program_esc(t_thread *thread);

#endif
