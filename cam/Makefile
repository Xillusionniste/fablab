CC = gcc
CFLAGS = -W -Wall 
USE_SDL = 1
ARCH = generic

  sdl_libs   := $(shell pkg-config --libs   sdl)
  sdl_cflags := $(shell pkg-config --cflags sdl)
  CFLAGS += -DUSE_SDL $(sdl_cflags)
theora_libs   := $(shell pkg-config --libs   theoraenc)
theora_cflags := $(shell pkg-config --cflags theoraenc)
vorbis_libs := $(shell pkg-config --libs vorbis vorbisenc)
alsa_libs := $(shell pkg-config --libs alsa)
jpeg_libs := -ljpeg
CFLAGS += $(theora_cflags)

ifeq ($(ARCH),X86_64)
  objects = hwebcam.o common.o video.o audio.o jpeg.o x86.o
  CFLAGS += -DARCH_X86_64
else ifeq ($(ARCH),X86_32)
  objects = hwebcam.o common.o video.o audio.o jpeg.o x86.o
  CFLAGS += -DARCH_X86_32
else
  objects = hwebcam.o common.o video.o audio.o jpeg.o
endif

all: $(objects)
#	$(CC) $(CFLAGS) -c $(objects) $(sdl_libs) $(theora_libs) $(vorbis_libs) $(alsa_libs) $(jpeg_libs)

#main: $(objects)
#	$(CC) $(CFLAGS) -o main $(objects) $(sdl_libs) $(theora_libs) $(vorbis_libs) $(alsa_libs) $(jpeg_libs)

debug: $(objects)
	$(CC) $(CFLAGS) -o main_debug $(objects) $(sdl_libs) $(theora_libs) $(vorbis_libs) $(alsa_libs) $(jpeg_libs) -DDEBUG

#ifeq ($(ARCH),X86_64)
#main.o: main.c hwebcam.h common.h video.h audio.h jpeg.h x86.h
#else ifeq ($(ARCH),X86_32)
#main.o: main.c hwebcam.h common.h video.h audio.h jpeg.h x86.h
#else
#main.o: main.c hwebcam.h common.h video.h audio.h jpeg.h
#endif
#	$(CC) $(CFLAGS) -c main.c

hwebcam.o: hwebcam.c hwebcam.h common.h
	$(CC) $(CFLAGS) -c hwebcam.c

video.o: video.c video.h huffman_tables.h common.h
	$(CC) $(CFLAGS) -c video.c

audio.o: audio.c audio.h common.h
	$(CC) $(CFLAGS) -c audio.c

jpeg.o: jpeg.c jpeg.h common.h
	$(CC) $(CFLAGS) -c jpeg.c

ifeq ($(ARCH),X86_64)
x86.o: x86.c x86.h common.h
	$(CC) $(CFLAGS) -c x86.c
endif
ifeq ($(ARCH),X86_32)
x86.o: x86.c x86.h common.h
	$(CC) $(CFLAGS) -c x86.c
endif

common.o: common.c common.h
	$(CC) $(CFLAGS) -c common.c

clean:
	rm -f $(objects) *~

.PHONY: clean
