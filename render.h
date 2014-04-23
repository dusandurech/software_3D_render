
#ifndef RENDER_H

#define RENDER_H

typedef struct
{
	float r;
	float g;
	float b;
} color_t;

typedef struct
{
	color_t color;

	float x_3d;
	float y_3d;
	float z_3d;

	int x_2d;
	int y_2d;
	float z_2d;
} point_t;

typedef struct
{
	color_t color;
	point_t list[8];
	int count;
} polygon_t;

void glLoadIdentity();
void glTransform3f(float x, float y, float z);
void glRotate3f(float angle, float x, float y, float z);
void glScale3f(float x, float y, float z);
void glColor3f(float r, float g, float b);
void glBegin();
void glVertex3f(float x, float y, float z);
void glEnd();
int glFlush();

#endif
