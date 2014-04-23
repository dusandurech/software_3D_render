
#ifndef TRANSFORM_H

#define TRANSFORM_H

#include "matrix.h"

void transform_perspective(matrix_t *matrix);
void transform_frustrum(matrix_t *matrix, float left, float right, float bottom, float top, float near, float far);
void transform_move(matrix_t *matrix, float x, float y, float z);
void transform_rotate_x(matrix_t *matrix, float alpha);
void transform_rotate_y(matrix_t *matrix, float alpha);
void transform_rotate_z(matrix_t *matrix, float alpha);
void transform_scale(matrix_t *matrix, float x, float y, float z);
void transform(matrix_t *matrix, float x, float y, float z, float *out_x, float *out_y, float *out_z);

#endif
