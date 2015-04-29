/* ----------------------------------------------
	 File Name	: utils.h
 	Object		:
	Creation	: DENECHAUD / HERIN
 ----------------------------------------------*/

#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <sys/ioctl.h>

#define BOTH		3
#define BUTTON_1	1
#define BUTTON_2	2
#define DIE_DUDE	666
#define LANG_CHOICE	555

void Read (char *switch_value, char *val);
void Write (char *switch_value, char *val);
void Blink (char *led_value, int delay);
int updateVal (const char *val1, const char *val2, const char *val3, const char *val4);

#endif
