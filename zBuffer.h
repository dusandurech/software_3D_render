
#ifndef Z_BUFFER_H

#define Z_BUFFER_H

typedef struct
{
	float z;
	int r;
	int g;
	int b;
} pixel_t;

#include "video.h"

#define Z_BUFFER_WIDTH		WINDOW_SIZE_X
#define Z_BUFFER_HEIGHT		WINDOW_SIZE_Y

typedef struct
{
	pixel_t pixel[Z_BUFFER_WIDTH][Z_BUFFER_HEIGHT];
} zBuffer_t;

void zBuffer_init(zBuffer_t *zBuffer);
void zBuffer_set_pixel(zBuffer_t *zBuffer, int x, int y, float z, int r, int g, int b);
void zBuffer_render(zBuffer_t *zBuffer);

#endif
