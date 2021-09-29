#include "fdf.h"

void	set_row(t_thread *thread)
{
	thread->segment[0].y = thread->segment[1].y;
	thread->segment[2].y = thread->segment[3].y;
	thread->segment[1].y = thread->segment[1].z;
	thread->segment[3].y = thread->segment[3].z;
	thread->segment[0].x = thread->segment[1].x;
	thread->segment[2].x = thread->segment[3].x;
		
}

void	set_column(t_thread *thread)
{
	thread->start_one = 0;
	thread->start_two = 0;
	thread->segment[0].altitude = 0;
	thread->segment[1].altitude = 0;
	thread->segment[2].altitude = 0;
	thread->segment[3].altitude = 0;
	thread->segment[0].x = thread->save_x;
	thread->segment[1].x = thread->save_x;
	thread->segment[2].x = thread->save_x;
	thread->segment[3].x = thread->save_x;
	thread->segment[0].y = thread->save_y;
	thread->segment[1].y = thread->save_y;
}
