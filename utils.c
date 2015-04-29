// ----------------------------------------------
// File Name		: utils.c
// Object		:
// Creation		: DENECHAUD / HERIN
// ----------------------------------------------

#include "utils.h"

void Read (char *url, char *val) 
{
	FILE *path=fopen(url,"r");
	fread(val,sizeof(char),1,path);
	fclose(path);
}

void Write (char *url, char *val) 
{
	FILE *path=fopen(url,"w");
	fwrite(val,1,sizeof(val),path);
	fclose(path);
}

void Blink (char *led_value, int delay) 
{ 
	int i;
	for (i=0;i<10;i++)
	{
		Write(led_value,"1");
		usleep(delay);
		Write(led_value,"0");
		usleep(delay);
	}
}

int updateVal ( const char *val1, const char *val2, const char *val3, const char *val4)
{
	int val;
	if ( (!strcmp(val1,"1")) && (!strcmp(val2,"1")) ) {val = BOTH;}
	else if ( !strcmp(val1,"1") ) {val = BUTTON_1;}
	else if ( !strcmp(val2,"1") ) {val = BUTTON_2;}
	else if ( !strcmp(val3,"1") ) {val = DIE_DUDE;}
	else if ( !strcmp(val4,"1") ) {val = LANG_CHOICE;}
	else val = 0;
	return val;
}
