
#ifndef SCAN_LINE_H

#define SCAN_LINE_H

#include "zBuffer.h"
#include "render.h"

typedef struct
{
	int left;
	int right;

	float left_z;
	float right_z;
} scan_t;

void scan_init(scan_t *scan, int count);
void scan_line(polygon_t *polygon, scan_t *scan_line);
void scan_line_draw(polygon_t *polygon, scan_t *scan, int count, zBuffer_t *zBuffer);

#endif
