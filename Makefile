
CC = gcc
#CC = /opt/gcc/bin/gcc

CFLAGS = -g -O0 -I. `sdl-config --cflags` -Wall
LIBS = `sdl-config --libs` -lm

FILES = main.o video.c matrix.o render.o draw.o transform.o zBuffer.o scan_line.o

main: $(FILES)
	$(CC) $(CFLAGS) $(LIBS) -o main $(FILES)

video.o: video.c video.h
	$(CC) $(CFLAGS) -o video.o -c video.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -o matrix.o -c matrix.c

render.o: render.c render.h
	$(CC) $(CFLAGS) -o render.o -c render.c

draw.o: draw.c draw.h
	$(CC) $(CFLAGS) -o draw.o -c draw.c

zBuffer.o: zBuffer.c zBuffer.h
	$(CC) $(CFLAGS) -o zBuffer.o -c zBuffer.c

transform.o: transform.c transform.h
	$(CC) $(CFLAGS) -o transform.o -c transform.c

scan_line.o: scan_line.c scan_line.h
	$(CC) $(CFLAGS) -o scan_line.o -c scan_line.c

main.o: main.c
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -rf *.o
	rm -rf *.so
	rm -rf *.c~ *.h~
	rm -rf Makefile~ rpg

