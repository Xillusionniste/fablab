#
# Makefile for Fabricarium Box
#

sdl_libs   := $(shell pkg-config --libs   sdl)
sdl_cflags := $(shell pkg-config --cflags sdl)
CFLAGS += -DUSE_SDL $(sdl_cflags)
theora_libs   := $(shell pkg-config --libs   theoraenc)
theora_cflags := $(shell pkg-config --cflags theoraenc)
vorbis_libs := $(shell pkg-config --libs vorbis vorbisenc)
alsa_libs := $(shell pkg-config --libs alsa)
jpeg_libs := -ljpeg
CFLAGS += $(theora_cflags)
CC = gcc

CFLAGS = -Wall -lSDL
LDFLAGS = -lSDL
EXEC = main

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o) ./cam/*.o

all: $(EXEC)

cam: ./cam/*.h ./cam/*.c
	cd ./cam; make

cleancam:
	cd ./cam; make clean

main: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(sdl_libs) $(theora_libs) $(vorbis_libs) $(alsa_libs) $(jpeg_libs)


%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o

debug: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) -DDEBUG
