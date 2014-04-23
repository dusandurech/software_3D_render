
#include <stdlib.h>
#include <math.h>

#include "matrix.h"
#include "transform.h"

/*
void GLAPIENTRY
gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
gluPerspective(45.0f, (GLfloat)SIZE_X/(GLfloat)SIZE_Y, 0.1f, 100.0f);

GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar
   GLdouble xmin, xmax, ymin, ymax;

   ymax = zNear * tan(fovy * M_PI / 360.0);
   ymin = -ymax;

   xmin = ymin * aspect;
   xmax = ymax * aspect;

   glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}
*/

void transform_perspective(matrix_t *matrix)
{
	const float b = 10.0;
	const float f =  0.5;

	/*
		cot(u)	0	0		0
		0	cot(v)	0		0
		0	0	(B+F)/(B-F)	(-2*B*F)/(B-F)
		0	0	1		0
	*/

	matrix_init(matrix, 4, 4);

	matrix_set(matrix, 0, 0, 4.0*1.3);
	matrix_set(matrix, 1, 1, 4.0);
	matrix_set(matrix, 2, 2, (b+f)/(b-f));
	matrix_set(matrix, 3, 2, (-2.0*b*f)/(b-f));
	matrix_set(matrix, 2, 3, 1.0);
}

//http://samplecodebank.blogspot.sk/2011/05/glfrustum-example.html
//http://glprogramming.com/red/appendixf.html

void transform_frustrum(matrix_t *matrix, float left, float right, float bottom, float top, float near, float far)
{
	/*
		2*near/left-right	0			(right+left)/(right-left)	0
		0			2*near/(top-bottom)	(top+bottom)/(top-bottom)	0
		0			0			-(far+near)/(far-near)		(-2*far*near)/(far-near)
		0			0			-1				0
	*/

	matrix_init(matrix, 4, 4);

	matrix_set(matrix, 0, 0, 2*near/(left-right));
	matrix_set(matrix, 0, 2, (right+left)/(right-left));

	matrix_set(matrix, 1, 1, 2*near/(top-bottom));
	matrix_set(matrix, 1, 2, (top+bottom)/(top-bottom));
	matrix_set(matrix, 2, 2, -(far+near)/(far-near));
	matrix_set(matrix, 2, 3, (-2*far*near)/(far-near));
	matrix_set(matrix, 3, 2, -1);
}

void transform_move(matrix_t *matrix, float x, float y, float z)
{
	/*
		1	0	0	x
		0	1	0	y
		0	0	1	z
		0	0	0	1
	*/

	matrix_init(matrix, 4, 4);

	matrix_set(matrix, 0, 0, 1.0);
	matrix_set(matrix, 1, 1, 1.0);
	matrix_set(matrix, 2, 2, 1.0);
	matrix_set(matrix, 3, 3, 1.0);

	matrix_set(matrix, 3, 0, x);
	matrix_set(matrix, 3, 1, y);
	matrix_set(matrix, 3, 2, z);
}

void transform_rotate_x(matrix_t *matrix, float alpha)
{
	/*
		1	0	0	0
		0	cos(a)	-sin(a)	0
		0	sin(a)	cos(a)	0
		0	0	0	1
	*/

	matrix_init(matrix, 4, 4);

	matrix_set(matrix, 0, 0, 1.0);
	matrix_set(matrix, 1, 1, 1.0);
	matrix_set(matrix, 2, 2, 1.0);
	matrix_set(matrix, 3, 3, 1.0);

	matrix_set(matrix, 1, 1, cos(alpha));
	matrix_set(matrix, 2, 1, -sin(alpha));
	matrix_set(matrix, 1, 2, sin(alpha));
	matrix_set(matrix, 2, 2, cos(alpha));
}

void transform_rotate_y(matrix_t *matrix, float alpha)
{
	/*
		cos(a)	0	sin(a)	0
		0	1	0	0
		-sin(a)	0	cos(a)	0
		0	0	0	1
	*/

	matrix_init(matrix, 4, 4);

	matrix_set(matrix, 0, 0, 1.0);
	matrix_set(matrix, 1, 1, 1.0);
	matrix_set(matrix, 2, 2, 1.0);
	matrix_set(matrix, 3, 3, 1.0);

	matrix_set(matrix, 0, 0, cos(alpha));
	matrix_set(matrix, 2, 0, sin(alpha));
	matrix_set(matrix, 0, 2, -sin(alpha));
	matrix_set(matrix, 2, 2, cos(alpha));
}

void transform_rotate_z(matrix_t *matrix, float alpha)
{
	/*
		cos(a)	-sin(a)	0	0
		sin(a)	cos(a)	0	0
		0	0	1	0
		0	0	0	1
	*/

	matrix_init(matrix, 4, 4);

	matrix_set(matrix, 0, 0, 1.0);
	matrix_set(matrix, 1, 1, 1.0);
	matrix_set(matrix, 2, 2, 1.0);
	matrix_set(matrix, 3, 3, 1.0);

	matrix_set(matrix, 0, 0, cos(alpha));
	matrix_set(matrix, 1, 0, -sin(alpha));
	matrix_set(matrix, 0, 1, sin(alpha));
	matrix_set(matrix, 1, 1, cos(alpha));
}

void transform_scale(matrix_t *matrix, float x, float y, float z)
{
	/*
		x	0	0	0
		0	y	0	0
		0	0	z	0
		0	0	0	1
	*/

	matrix_init(matrix, 4, 4);

	matrix_set(matrix, 0, 0, x);
	matrix_set(matrix, 1, 1, y);
	matrix_set(matrix, 2, 2, z);
	matrix_set(matrix, 3, 3, 1.0);
}

void transform(matrix_t *matrix, float x, float y, float z, float *out_x, float *out_y, float *out_z)
{
	matrix_t matrix_3d;
	matrix_t matrix_2d;

	float x_2d;
	float y_2d;
	float z_2d;
	float w_2d;
	float n;

	matrix_init(&matrix_3d, 1, 4);

	matrix_set(&matrix_3d, 0, 0, x);
	matrix_set(&matrix_3d, 0, 1, y);
	matrix_set(&matrix_3d, 0, 2, z);
	matrix_set(&matrix_3d, 0, 3, 1);

	matrix_mul(matrix, &matrix_3d, &matrix_2d);

	x_2d = matrix_get(&matrix_2d, 0, 0);
	y_2d = matrix_get(&matrix_2d, 0, 1);
	z_2d = matrix_get(&matrix_2d, 0, 2);
	w_2d = matrix_get(&matrix_2d, 0, 3);

	n = 1.0/w_2d;
	x_2d *= n;
	y_2d *= n;
	z_2d *= n;
	w_2d *= n;

	if( out_x != NULL) *out_x = x_2d;
	if( out_y != NULL) *out_y = y_2d;
	if( out_z != NULL) *out_z = z_2d;
}
