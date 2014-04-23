
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <SDL.h>

#include "video.h"

#define SDL_SUBSYSTEMS SDL_INIT_VIDEO|SDL_INIT_TIMER

#define WINDOW_TITLE "Window"
#define WIN_BPP 0
#define USR_EVT_TIMER 0

#define INTERVAL		50

static SDL_Surface *screen;
static Uint32 g_win_flags = 0;
static SDL_TimerID timer;

static Uint32 TimerCallback(Uint32 interval, void *param)
{
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = USR_EVT_TIMER;
	event.user.data1 = NULL;
	event.user.data2 = NULL;

	SDL_PushEvent(&event);

	return interval;
}

int video_init()
{
	if( SDL_Init(SDL_SUBSYSTEMS) == -1 )
	{
		fprintf(stderr, "ERROR SDL_Init %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	screen = SDL_SetVideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 0, g_win_flags);

	if (screen == NULL )
	{
		fprintf(stderr, "ERROR SDL_SetVideoMode %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	SDL_WM_SetCaption(WINDOW_TITLE, NULL);
	timer = SDL_AddTimer(INTERVAL, TimerCallback, NULL);

	return 0;
}

void video_clean()
{
	memset(screen->pixels, 0, screen->h*screen->pitch);
}

void video_put_pixel(int x, int y, int r, int g, int b)
{
	int bpp = screen->format->BytesPerPixel;
	Uint32 pixel = SDL_MapRGB(screen->format, r, g, b);
	Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;
	
	r = ( r < 0 ? 0 : r);
	g = ( g < 0 ? 0 : g);
	b = ( b < 0 ? 0 : b);

	r = ( r > 255 ? 255 : r);
	g = ( g > 255 ? 255 : g);
	b = ( b > 255 ? 255 : b);

	if( x < 0 || x >= WINDOW_SIZE_X || y < 0 || y >= WINDOW_SIZE_Y )
	{
		return;
	}

	switch(bpp)
	{
		case 1:
			*p = pixel;
			break;
		
		case 2:
			*(Uint16 *)p = pixel;
			break;
		
		case 3:
			if( SDL_BYTEORDER == SDL_BIG_ENDIAN )
			{
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;
		
		case 4:
			*(Uint32 *)p = pixel;
			break;
	}
}

void video_refresh()
{
	SDL_Flip(screen);
}

int video_event()
{
	SDL_Event event;

	while( SDL_WaitEvent(&event) )
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						video_quit();
						return -1;
					break;
		
					default:
					break;
				}
			break;

			case SDL_USEREVENT:
				switch(event.user.code)
				{
					case USR_EVT_TIMER:
						return 1;
					break;
	
					default:
					break;
				}
			break;
	
			case SDL_VIDEORESIZE:
			break;
	
			case SDL_QUIT:
				//video_quit();
				return -1;
			break;
	
			default:
			break;
		}
	}

	return 0;
}

void video_pause()
{
	while( 1 )
	{
		if ( video_event() == 1 )
		{
			return;
		}
	}
}

void video_quit()
{
	SDL_Quit();
	exit(0);
}
