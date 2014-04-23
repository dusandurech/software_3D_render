
#include <stdio.h>
#include <assert.h>

#include "matrix.h"

void matrix_init(matrix_t *matrix, int w, int h)
{
	int i;
	int j;

	matrix->w = w;
	matrix->h = h;

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			matrix->m[j][i] = 0.0;
		}
	}
}

void matrix_clone(matrix_t *matrix_dst, matrix_t *matrix_src)
{
	int i;
	int j;

	matrix_dst->w = matrix_src->w;
	matrix_dst->h = matrix_src->h;

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			matrix_dst->m[j][i] = matrix_src->m[j][i];
		}
	}
}

void matrix_set(matrix_t *matrix, int x, int y, float n)
{
	matrix->m[x][y] = n;
}

float matrix_get(matrix_t *matrix, int x, int y)
{
	return matrix->m[x][y];
}

void matrix_print(matrix_t *matrix)
{
	int i;
	int j;

	for(i = 0; i < matrix->h; i++)
	{
		for(j = 0; j < matrix->w; j++)
		{
			printf("%2.2f ", matrix->m[j][i]);
		}

		putchar('\n');
	}
}

void matrix_mul(matrix_t *a, matrix_t *b, matrix_t *c)
{
	int i;
	int j;
	int k;

	assert( a->w == b->h );

	c->w = b->w;
	c->h = a->h;

	for(i = 0; i < c->h; i++)
		for(j = 0; j < c->w; j++)
		{
			float z = 0.0;

			for(k = 0; k < a->w; k++)
				z += a->m[k][i] * b->m[j][k];

			c->m[j][i] = z;
		}
}
