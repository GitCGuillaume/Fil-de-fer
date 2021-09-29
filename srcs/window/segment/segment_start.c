#include "fdf.h"

void	start_draw_first_line(t_thread *thread)
{
	double	radian;

	radian = 0.61;
	if (thread->segment[0].altitude != 0)
	{
		thread->segment[0].y -= thread->segment[0].altitude
			* (sin(radian) * ((thread->segment[1].x
						- thread->segment[0].x)
					+ (thread->segment[1].z - thread->segment[1].y)));
	}
}

void	start_draw_second_line(t_thread *thread)
{
	double	radian;

	radian = 0.61;
	if (thread->segment[2].altitude != 0)
	{
		thread->segment[2].y -= thread->segment[2].altitude
			* (sin(radian) * ((thread->segment[3].x
						- thread->segment[2].x)
					+ (thread->segment[3].z - thread->segment[3].y)));
	}
}
