
#include <math.h>

#include "scan_line.h"

int abs(int n)
{
	return ( n > 0 ? n : -n );
}

void scan_init(scan_t *scan, int count)
{
	int i;

	for(i = 0; i < count; i++)
	{
		scan[i].left  = +1000;
		scan[i].right = -1000;
	}
}

void scan_line(polygon_t *polygon, scan_t *scan_line)
{
	int i;

	for(i = 0; i < polygon->count; i++)
	{
		int start;
		int end;

		int x1, y1;
		int x2, y2;
		float z1, z2;

		int px, py;
		float pz;

		int idx_a;
		int idx_b;

		int dx, dy;
		float dz;

		float q;
		float q_z;
		int j;

		idx_a = i;
		idx_b = i+1;

		if( i == polygon->count-1 )
		{
			idx_b = 0;
		}

		if( polygon->list[idx_a].y_2d > polygon->list[idx_b].y_2d )
		{
			int z;

			z = idx_a;
			idx_a = idx_b;
			idx_b = z;
		}

		if( polygon->list[idx_a].y_2d == polygon->list[idx_b].y_2d )
		{
			continue;
		}

		x1 = polygon->list[idx_a].x_2d;
		y1 = polygon->list[idx_a].y_2d;
		z1 = polygon->list[idx_a].z_2d;

		x2 = polygon->list[idx_b].x_2d;
		y2 = polygon->list[idx_b].y_2d;
		z2 = polygon->list[idx_b].z_2d;

		dx = x1-x2;
		dy = y1-y2;
		dz = z1-z2;
	
		q = (float)dx / (float)dy;
		q_z = (double)dz / (double)dy;

		start = y1;
		end = y2;

		for(j = start; j <= end; j++)
		{
			py = j;
			px = x1+(j-y1)*q;
			pz = z1 + (j-y1)*q_z;

			if( py < 0 || py > 320-1 )
			{
				continue;
			}

			if( px > scan_line[py].right )
			{
				scan_line[py].right = px;
				scan_line[py].right_z = pz;
			}

			if( px-1 < scan_line[py].left )
			{
				scan_line[py].left = px-1;
				scan_line[py].left_z = pz;
			}
		}
	}
}

float get_distance(float x1, float y1, float x2, float y2)
{
	return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

void poor_color(color_t *color_a, float w1, color_t *color_b, float w2, color_t *color_c, float *w3)
{
	float r, g, b;
	float sum;
	float wn;

	sum = w1+w2;
	wn = w1/sum;

	r = (1.0-wn)*(color_a->r) + (wn)*(color_b->r);
	g = (1.0-wn)*(color_a->g) + (wn)*(color_b->g);
	b = (1.0-wn)*(color_a->b) + (wn)*(color_b->b);

	color_c->r = r;
	color_c->g = g;
	color_c->b = b;

	*w3 = sum;
}

void scan_line_draw(polygon_t *polygon, scan_t *scan, int count, zBuffer_t *zBuffer)
{
	int i;
	int j;
	
	for(i = 0; i < count; i++)
	{
		if( scan[i].left < scan[i].right )
		{
			float z;
			float dx;
			float dz;
			float grad_z;

			dx = scan[i].right - scan[i].left;
			dz = scan[i].right_z - scan[i].left_z;
			grad_z = dz / dx;

			for(j = scan[i].left; j < scan[i].right; j++)
			{
				z = scan[i].left_z + (j - scan[i].left) * grad_z;

				zBuffer_set_pixel(zBuffer, j, i, z, polygon->color.r*255, polygon->color.g*255, polygon->color.b*255);
			}
		}
	}
}

