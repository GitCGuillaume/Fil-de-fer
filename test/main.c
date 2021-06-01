#include "../minilibx-linux/mlx.h"

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

	buffer[pixel + 0] = (color) & 0xFF;
	buffer[pixel + 1] = (color >> 8) & 0xFF;
	buffer[pixel + 2] = (color >> 16) & 0xFF;
	buffer[pixel + 3] = (color >> 24) & 0xFF;
	
}
#include <stdio.h>
void	test(void *mlx_ptr, int lb, char *buffer, int x0, int y0, int x1, int y1, int colour)
{
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	deltaE = 2 * dy;
	int	deltaNE = 2 * (dy - dx);
	int	dp = 0;

	draw_pixel(buffer, lb, x0, y0, get_colour(mlx_ptr));
	if (x1 >= x0)
	{
		if (dx >= dy)
		{
			dp = 2 * dy - dx;
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
		dy = y0 - y1;
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
	test(mlx_ptr, lb, buffer, 250, 250, 250, 400, get_colour(mlx_ptr));
	mlx_put_image_to_window(mlx_ptr, mlx_win, mlx_img, 0, 0);
	mlx_loop(mlx_ptr);
	mlx_destroy_window(mlx_ptr, mlx_win);
	return (0);
}
