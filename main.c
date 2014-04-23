
#include <stdio.h>
#include <math.h>

#include "video.h"
#include "render.h"

extern int transform(float x, float y, float z, int *out_x, int *out_y);

void draw_cube()
{
	static int rot_y = 0;

	const float points_cube[] =
	{
		-0.5, +0.5, +0.5, +0.5, +0.5, +0.5,
		+0.5, -0.5, +0.5, -0.5, -0.5, +0.5,

		-0.5, +0.5, -0.5, +0.5, +0.5, -0.5,
		+0.5, -0.5, -0.5, -0.5, -0.5, -0.5,

		+0.5, +0.5, -0.5, +0.5, +0.5, +0.5,
		+0.5, -0.5, +0.5, +0.5, -0.5, -0.5,

		-0.5, +0.5, -0.5, -0.5, +0.5, +0.5,
		-0.5, -0.5, +0.5, -0.5, -0.5, -0.5
	};

	int i;
	int j;
	int n;

	glLoadIdentity();

	glTransform3f(0.0, 0.0, -3.0);

	//glRotate3f(90, 1.0, 0.0, 0.0);
	glRotate3f(rot_y/2, 1.0, 0.0, 0.0);
	glRotate3f(rot_y/1, 0.0, 1.0, 0.0);
	//glRotate3f(rot_y/3, 0.0, 0.0, 1.0);
	//glTransform3f(0.0, 0.0, 0.5);
	//glRotate3f(2*rot_y, 0.0, 1.0, 0.0);
	//glScale3f(0.5, 0.5, 0.5);

	n = 0;

	for(j = 0; j < 4; j++)
	{
		if( j == 0 ) glColor3f(1.0, 0.0, 0.0);
		if( j == 1 ) glColor3f(0.0, 1.0, 0.0);
		if( j == 2 ) glColor3f(0.0, 0.0, 1.0);
		if( j == 3 ) glColor3f(1.0, 0.0, 1.0);

		glBegin();
	
		for(i = 0; i < 4; i++)
		{
			glVertex3f(points_cube[n+0], points_cube[n+1], points_cube[n+2]);
			n += 3;
		}
	
		glEnd();
	}

	glFlush();

	rot_y += 1;

#if 0
	if( rot_y > 360 )
	{
		rot_y = 0;
	}
#endif
}

int main()
{
	video_init();

	while( 1 )
	{
		video_clean();
		draw_cube();
		video_refresh();
		video_pause();
	}

	video_quit();

	return 0;
}
