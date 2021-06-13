#include "../minilibx-linux/mlx.h"
#include "math.h"

int	get_colour(void *mlx_ptr)
{
	int	colour;
	int	r;
	int	g;
	int	b;

	colour = 0;
	r = 255;
	g = 0;
	b = 0;
	if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255)
			&& (b >= 0 && b <= 255))
	{
		colour = r << 16;
		colour += g << 8;
		colour += b;
		return (mlx_get_color_value(mlx_ptr, colour));
	}
	return (0);
}

void	draw_pixel(char *buffer, int lb, int x, int y, int color)
{
	int	pixel;
	pixel = (y * lb) + (x * 4);

	buffer[pixel + 0] = (color);
	buffer[pixel + 1] = (color >> 8);
	buffer[pixel + 2] = (color >> 16);
	//buffer[pixel + 3] = (color >> 24) & 0xFF;
	
}

/*
 ** bresenham algorithm, will draw a line, with integer values with the help of equation, will test if dp is below or above the segment, incrementes or decrementes values
 ** , then draw a pixel on the center of this vertical segment
 ** (to the nearest of the segment)
 ** this algorith will allow to draw a line from 180 degrees to 360
 ** SW, S, SE
*/
#include <stdio.h>
void	test(void *mlx_ptr, int lb, char *buffer, int x0, int y0, int x1, int y1, int colour)
{

	int tmp;
	if (y0 > y1)
	{
		tmp = y0;
		y0 = y1;
		y1 = tmp;
		tmp = x0;
		x0 = x1;
		x1 = tmp;

	}
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	deltaE = 2 * dy;
	int	deltaNE = 2 * (dy - dx);
	int	dp = 0;
	draw_pixel(buffer, lb, x0, y0, get_colour(mlx_ptr));
	printf("x1=%d x0=%d\n", x1, x0);
	if (x1 >= x0)
	{
		dx = x1 - x0;
		dy = y1 - y0;
		printf("allo");
		if (dx >= dy)
		{
			dp = 2 * dy - dx;
			printf("dp=%d\n", dp);
			while (x1 > x0)
			{
				if (dp > 0)
				{
					dp = dp + (2 * (dy - dx));
					y0++;
				}
				else
				{
					dp = dp + (2 * dy);
				}
				x0++;
				draw_pixel(buffer, lb, x0, y0, get_colour(mlx_ptr));
			}
		}
		else
		{
			dp = 2 * dx - dy;
			while (y1 > y0)
			{
				if (dp > 0)
				{
					dp = dp + (2 * (dx - dy));
					x0++;
				}
				else
				{
					dp = dp + (2 * dx);
				}
				y0++;
				draw_pixel(buffer, lb, x0, y0, get_colour(mlx_ptr));
			}
		}
	}
	else
	{
		dx = x0 - x1;
		dy = y1 - y0;
		if (dx >= dy)
		{
			dp = 2 * dy - dx;
			while (x0 > x1)
			{
				if (dp > 0)	
				{
					dp = dp + (2 * (dy - dx));
					y0++;
				}
				else
				{
					dp = dp + (2 * dy);
				}
				x0--;
				draw_pixel(buffer, lb, x0, y0, get_colour(mlx_ptr));
			}
		}
		else
		{
			dp = 2 * dx - dy;
			while (x0 > x1)
			{
				if (dp > 0)
				{
					dp = dp + 2 * (dx - dy);
					x0--;
				}
				else
				{
					dp = dp + (2 * dx);
				}
				y0++;
				draw_pixel(buffer, lb, x0, y0, get_colour(mlx_ptr));
			}
		}
	}
}

int	main(void)
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*mlx_img;
	char	*buffer;
	int	pix;
	int	lb;
	int	edn;

	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, 500, 500, "Test");
	mlx_img = mlx_new_image(mlx_ptr, 500, 500);
	buffer = mlx_get_data_addr(mlx_img, &pix, &lb, &edn);
	//X
	//test(mlx_ptr, lb, buffer, 100, 100, 100 , 300, get_colour(mlx_ptr));
	//Y
	//test(mlx_ptr, lb, buffer, 100, 100, 300, 100, get_colour(mlx_ptr));
printf("atan=%f\n", atan(300/200));
	//printf("sin=%f sin * oppo=%f", sin(0.61), sin(0.61)*300);
	printf("300*tan(0.61)=%f", 300*tan(0.61));
	//test(mlx_ptr, lb, buffer, 0, 0, 300*0.82, 209*0.82, get_colour(mlx_ptr));
	//(x - y) = res * tan(0.61)
	
	//test(mlx_ptr, lb, buffer, 0, 0, 100, (100*tan(0.61)), get_colour(mlx_ptr));

	//x0-y1
	printf("sin(35)=%f cos(35)=%f\n", sin(0.61), cos(0.61));
	//cos(35)*hypotenuse(105-100)=81
	test(mlx_ptr, lb, buffer, 150, 150, 150+100, 150+(tan(0.61)*100), get_colour(mlx_ptr));
	test(mlx_ptr, lb, buffer, 150, 150, 150-10, 150+(tan(0.61)*100), get_colour(mlx_ptr));
	test(mlx_ptr, lb, buffer, 150, 150, 150, 250, get_colour(mlx_ptr));
	
	test(mlx_ptr, lb, buffer, 150, 150, 150+100, 150-(tan(0.61)*100), get_colour(mlx_ptr));
	test(mlx_ptr, lb, buffer, 150, 150, 150-10, 150-(tan(0.61)*100), get_colour(mlx_ptr));
	test(mlx_ptr, lb, buffer, 150, 150, 150, 0, get_colour(mlx_ptr));
	
	//test(mlx_ptr, lb, buffer, 0, 0, 150, 150+(tan(0.61)), get_colour(mlx_ptr));
	//test(mlx_ptr, lb, buffer, 150, 150, 150, 50, get_colour(mlx_ptr));
	//test(mlx_ptr, lb, buffer, 0, 0, 0, 300, get_colour(mlx_ptr));
	
	//x0= 200 x1=300 300-200=100 100*tan(0.61)=69
	//test(mlx_ptr, lb, buffer, 200, 200, 300, 200+(((300-200)*tan(0.61)))*0.82, get_colour(mlx_ptr));
	//y0 = 200 y1=300 300-200=100 
	//test(mlx_ptr, lb, buffer, 200, 200, (((300-200)*tan(0.61)))*0.82, 300, get_colour(mlx_ptr));
	
	//test(mlx_ptr, lb, buffer, 200, 200, 200/atan(35.26), 300, get_colour(mlx_ptr));
	//test(mlx_ptr, lb, buffer, 200, 200, 200, 409, get_colour(mlx_ptr));
	//test(mlx_ptr, lb, buffer, 200, 200, (100 * 0.82) *atan(0.52), (300 * 0.82)*atan(0.52), get_colour(mlx_ptr));
	mlx_put_image_to_window(mlx_ptr, mlx_win, mlx_img, 0, 0);
	mlx_loop(mlx_ptr);
	mlx_destroy_window(mlx_ptr, mlx_win);
	return (0);
}
