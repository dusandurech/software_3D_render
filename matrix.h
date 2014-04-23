
#ifndef MATRIX_H

#define MATRIX_H

typedef struct
{
	float m[4][4];
	int w;
	int h;
} matrix_t;

extern void matrix_init(matrix_t *matrix, int w, int h);
extern void matrix_clone(matrix_t *matrix_dst, matrix_t *matrix_src);
extern void matrix_set(matrix_t *matrix, int x, int y, float n);
extern float matrix_get(matrix_t *matrix, int x, int y);
extern void matrix_print(matrix_t *matrix);
extern void matrix_mul(matrix_t *a, matrix_t *b, matrix_t *c);

#endif
