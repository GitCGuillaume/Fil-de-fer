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

typedef struct s_thread
{
	char	**lines;
	char	*line;
	int	fd;

}	t_thread;

/*
 ** Parse map
*/

void	get_line_fd(t_thread *thread);
int	check_lines(t_thread *thread);

/*
 ** Tools
*/

void	close_program_error(t_thread *thread, char *str, int fd);

#endif
