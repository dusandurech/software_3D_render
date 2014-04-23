
#include <stdio.h>
#include <math.h>

#include "video.h"

int sgn(int a, int b)
{
	if( a > b )
	{
		return +1;
	}

	if( a < b )
	{
		return -1;
	}

	return +1;
}

int my_abs(int n)
{
	if( n < 0 )
	{
		return -1 * n;
	}
	
	return n;
}

void draw_line(int x1, int y1, int x2, int y2, int r, int g, int b)
{
	int dx;
	int dy;
	int i;
	float q;
	int sx;
	int sy;

	//printf("%d %d %d %d\n", x1, y1, x2, y2);

	if( x1 == x2 && y1 == y2 )
	{
		video_put_pixel(x1, y1, r, g, b);
		return;
	}

	dx = my_abs(x1-x2);
	dy = my_abs(y1-y2);

	sy = sgn(y2, y1);
	sx = sgn(x2, x1);

	q = (float)dy / (float)dx;

	if( q < 1.0 )
	{

		for(i = 0; i <= dx; i++)
		{
			video_put_pixel(x1+sx*i, y1+sy*i*(q/1.0), r, g, b);
		}
	}
	else
	{
		for(i = 0; i <= dy; i++)
		{
			video_put_pixel(x1+sx*i*(1.0/q), y1+sy*i, r, g, b);
		}
	}
}

