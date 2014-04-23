
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "video.h"
#include "matrix.h"
#include "draw.h"
#include "transform.h"
#include "zBuffer.h"
#include "render.h"
#include "scan_line.h"

matrix_t matrix_main;

int list_point2d_count = 0;

polygon_t list_polygon[1000];
int list_polygon_count = 0;

void init()
{
	memset(list_polygon, 0, 1000*sizeof(polygon_t));

	list_polygon_count = 0;
	list_point2d_count = 0;
}

void glLoadIdentity()
{
	transform_frustrum(&matrix_main, -0.25, 0.25, -0.25, 0.25, 0.01, 100.0);
}

void glTransform3f(float x, float y, float z)
{
	matrix_t matrix_move;
	matrix_t matrix_res;

	transform_move(&matrix_move, x, y, z);
	matrix_mul(&matrix_main, &matrix_move, &matrix_res);
	matrix_clone(&matrix_main, &matrix_res);
}

void glRotate3f(float angle, float x, float y, float z)
{
	matrix_t matrix_rot_x;
	matrix_t matrix_rot_y;
	matrix_t matrix_rot_z;

	matrix_t matrix_res1;
	matrix_t matrix_res2;
	matrix_t matrix_res3;

	transform_rotate_x(&matrix_rot_x, (2*M_PI/360)*(x*angle));
	transform_rotate_y(&matrix_rot_y, (2*M_PI/360)*(y*angle));
	transform_rotate_z(&matrix_rot_z, (2*M_PI/360)*(z*angle));

	matrix_mul(&matrix_rot_x, &matrix_rot_y, &matrix_res1);
	matrix_mul(&matrix_res1, &matrix_rot_z, &matrix_res2);
	matrix_mul(&matrix_main, &matrix_res2, &matrix_res3);

	matrix_clone(&matrix_main, &matrix_res3);
}

void glScale3f(float x, float y, float z)
{
	matrix_t matrix_scale;
	matrix_t matrix_res;

	transform_scale(&matrix_scale, x, y, z);
	matrix_mul(&matrix_main, &matrix_scale, &matrix_res);
	matrix_clone(&matrix_main, &matrix_res);
}

void glColor3f(float r, float g, float b)
{
	polygon_t *polygon;

	polygon = &list_polygon[list_polygon_count];

	polygon->list[polygon->count].color.r = r;
	polygon->list[polygon->count].color.g = g;
	polygon->list[polygon->count].color.b = b;

	polygon->color.r = r;
	polygon->color.g = g;
	polygon->color.b = b;
}

void glBegin()
{
}

void glVertex3f(float x, float y, float z)
{
	polygon_t *polygon;
	float x_2d;
	float y_2d;
	float z_2d;

	polygon = &list_polygon[list_polygon_count];

	polygon->list[polygon->count].x_3d = x;
	polygon->list[polygon->count].y_3d = y;
	polygon->list[polygon->count].z_3d = z;

	transform(&matrix_main, x, y, z, &x_2d, &y_2d, &z_2d);

	//if( x_2d >= -1.0 && x_2d <= +1.0 && y_2d >= -1.0 && y_2d <= +1.0 )
	if( 1 )
	{
		int out_x;
		int out_y;

		out_x = WINDOW_SIZE_X/2*x_2d + WINDOW_SIZE_X/2;
		out_y = WINDOW_SIZE_Y/2*y_2d + WINDOW_SIZE_Y/2;

		polygon->list[polygon->count].x_2d = out_x;
		polygon->list[polygon->count].y_2d = out_y;
		polygon->list[polygon->count].z_2d = -z_2d;
		polygon->count++;
	}
}

void glEnd()
{
	list_polygon_count++;
}

void draw_polygon(polygon_t *polygon)
{
	int i;

	for(i = 0; i < polygon->count; i++)
	{
		int x1, y1;
		int x2, y2;

		int idx_a;
		int idx_b;

		idx_a = i;
		idx_b = i+1;

		if( i == polygon->count-1 )
		{
			idx_b = 0;
		}

		x1 = polygon->list[idx_a].x_2d;
		y1 = polygon->list[idx_a].y_2d;

		x2 = polygon->list[idx_b].x_2d;
		y2 = polygon->list[idx_b].y_2d;

		draw_line(x1, y1, x2, y2, 255, 255, 255);
	}
}

int glFlush()
{
	zBuffer_t zBuffer;
	scan_t scan[WINDOW_SIZE_Y];
	int i;

	zBuffer_init(&zBuffer);

	for(i = 0; i < list_polygon_count; i++)
	{
		scan_init((scan_t *) &scan, WINDOW_SIZE_Y);
		//draw_polygon(&list_polygon[i]);
		scan_line(&list_polygon[i], (scan_t *) &scan);
		scan_line_draw(&list_polygon[i], (scan_t *) &scan, WINDOW_SIZE_Y, &zBuffer);
	}

	zBuffer_render(&zBuffer);

	init();

	return 0;
}
