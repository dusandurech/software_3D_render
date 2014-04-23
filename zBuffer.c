
#include <string.h>

#include "video.h"
#include "zBuffer.h"

void zBuffer_init(zBuffer_t *zBuffer)
{
	int i;
	int j;

	memset(zBuffer, 0, sizeof(zBuffer_t));

	for(i = 0; i < Z_BUFFER_HEIGHT; i++)
	{
		for(j = 0; j < Z_BUFFER_WIDTH; j++)
		{
			zBuffer->pixel[j][i].z = -1024;
		}
	}
}

void zBuffer_set_pixel(zBuffer_t *zBuffer, int x, int y, float z, int r, int g, int b)
{
	if( x >= 0 && x < Z_BUFFER_WIDTH && y >= 0 && y < Z_BUFFER_HEIGHT && z > zBuffer->pixel[x][y].z )
	{
		zBuffer->pixel[x][y].z = z;

		zBuffer->pixel[x][y].r = r;
		zBuffer->pixel[x][y].g = g;
		zBuffer->pixel[x][y].b = b;
	}
}

void zBuffer_render(zBuffer_t *zBuffer)
{
	int i;
	int j;

	for(i = 0; i < Z_BUFFER_HEIGHT; i++)
	{
		for(j = 0; j < Z_BUFFER_WIDTH; j++)
		{
			if( zBuffer->pixel[j][i].z > -1000 )
			{
				video_put_pixel(j, i, zBuffer->pixel[j][i].r, zBuffer->pixel[j][i].g, zBuffer->pixel[j][i].b);
			}
		}
	}
}
