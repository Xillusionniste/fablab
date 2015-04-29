/** IMPORTATIONS **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <poll.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <theora/theoraenc.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include "common.h"
#include "video.h"
#include "audio.h"
#include "jpeg.h"
#include "../utils.h"
#include <SDL/SDL.h>

/** CONSTANTES **/

#if defined(ARCH_X86_32) || defined(ARCH_X86_64)
#include "x86.h"
#endif

#define VERSION "0.48"
#define DEBUG   0

#define CLIPRGB(x) if (x < 0) x = 0; else if (x > 255) x = 255;
#define COMPUTE_RGB(y, cb, cr) r = (256 * y +          + 359 * cr + 128) >> 8;\
                               g = (256 * y -  88 * cb - 183 * cr + 128) >> 8;\
                               b = (256 * y + 454 * cb +          + 128) >> 8;
static volatile sig_atomic_t keep_going = 1;

/** STRUCTURES **/
struct ppm_st {
	unsigned int   width;
	unsigned int   height;
	unsigned int   max;
	unsigned char *data;
};

enum muxer_page_type {
	AUDIO,
	VIDEO
};

struct muxer_page_st {
	ogg_page              opage;
	struct muxer_page_st *next;
};

struct muxer_st {
	FILE                 *fpvideo;

	th_enc_ctx           *tctx;
	struct muxer_page_st *vq_head;
	struct muxer_page_st *vq_tail;

	int                   haveaudio;
	vorbis_dsp_state     *vds;
	struct muxer_page_st *aq_head;
	struct muxer_page_st *aq_tail;
};

/** FONCTIONS **/
void signal_handler(int sig);
void yuyv422_to_rgb24(const unsigned char *src, struct ppm_st *frame);
void yuyv422_to_y8_c(const unsigned char *src, th_ycbcr_buffer ycbcrbuf);
void yuyv422_to_yuv420p_c(const unsigned char *src, th_ycbcr_buffer ycbcrbuf);
void muxer_add_page(struct muxer_st *muxer, ogg_page *opage, enum muxer_page_type type);
void muxer_write(struct muxer_st *muxer, int flush);
char *pixelformat_to_str(unsigned int pixelformat);
void usage(void);

void webcam(bool capture_picture, int english, char *bouton1, char *bouton2);

