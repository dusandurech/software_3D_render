
#ifndef VIDEO_H

#define VIDEO_H

#define WINDOW_SIZE_X	320
#define WINDOW_SIZE_Y	320

int video_init();
void video_clean();
void video_put_pixel(int x, int y, int r, int g, int b);
void video_refresh();
int video_event();
void video_pause();
void video_quit();

#endif
