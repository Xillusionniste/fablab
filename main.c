/* -----------------------------------------------
	File Name	: main.c
	Object		: Manages Fabricarium Box
	Creation	: DENECHAUD / HERIN
 -----------------------------------------------*/

#include "utils.h"
#include "SDL_functions.h"
#include "cam/hwebcam.h"

#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>

#define SCP_CMD		"scp -P 2222 ./pics/img* jherin12@portier.polytech-lille.fr:/home-www/ima4/jherin12/upload/images/"
#define SHIFT_VALUE	7

/*************************
** LOCAL VARIABLES
*************************/

int page_index; /*To know witch background picture to display*/
int page_indexTemp; /* When user change language */
char *picture[NB_PICTURES];
int english; // To display the right language on the interface

/*************************
**                      **
**     MAIN FUNCTION    **
**                      **
*************************/

int main(void)
{
	/** Variable declarations **/
	/* Pins setting */
	char *switch1_direction="/sys/class/gpio/gpio67/direction";
	char *switch2_direction="/sys/class/gpio/gpio68/direction";
	char *switch3_direction="/sys/class/gpio/gpio66/direction";
	char *switch4_direction="/sys/class/gpio/gpio44/direction";
	char *switch1_value="/sys/class/gpio/gpio67/value";
	char *switch2_value="/sys/class/gpio/gpio68/value";
	char *switch3_value="/sys/class/gpio/gpio66/value";
	char *switch4_value="/sys/class/gpio/gpio44/value";

	char *cmd_in="in";
	char *export="/sys/class/gpio/export";

	char val1[10] = {'\0'}, val2[10] = {'\0'}, val3[10] = {'\0'}, val4[10] = {'\0'};
	int val = 0;
	int flag = 0;
	char format[128]; //To change name of picture taken with date and time
	time_t temps;
	struct tm date;
	char commande[128] = {'\0'}; //Cmd used by function system()

	/** INITIALIZATION **/
	/* SDL INIT */
	SDL_Surface *screen = NULL, *backgroundPicture = NULL;
	int options = SDL_ANYFORMAT | SDL_HWSURFACE /*| SDL_DOUBLEBUF*/;
	/* End of declarations */

	/* Setting up pictures in picture[] table */

	/****** FRENCH ********************/
	picture[0]="./pics/Page_1_FR.bmp";
	picture[1]="./pics/Page_2_Photo_FR.bmp";
	picture[2]="./pics/Page_3_Photo_FR.bmp";
	picture[3]="./pics/Page_4_FR.bmp";
	picture[4]="./pics/image.bmp";
	picture[5]="./pics/Page_Switchoff_FR.bmp";
	picture[6]="./pics/Page_4_wait_FR.bmp";
	/****** ENGLISH ********************/
	picture[7] ="./pics/Page_1_EN.bmp";
	picture[8] ="./pics/Page_2_Photo_EN.bmp";
	picture[9] ="./pics/Page_3_Photo_EN.bmp";
	picture[10]="./pics/Page_4_EN.bmp";
	picture[11]="./pics/image.bmp";
	picture[12]="./pics/Page_Switchoff_EN.bmp";
	picture[13]="./pics/Page_4_wait_EN.bmp";
	/****** LANGUAGE MENU **************/
	picture[14]="./pics/Page_Lang.bmp";
	/***********************************/
	
	english = 0;

	/* BBB PIOs INIT */
	Write(export,"67");
	Write(export,"68");
	Write(export,"66");
	Write(export,"44");
	Write(switch1_direction,cmd_in);
	Write(switch2_direction,cmd_in);
	Write(switch3_direction,cmd_in);
	Write(switch4_direction,cmd_in);
	printf("Setup OK\n");

	/** FIRST DISPLAYING ON SCREEN **/
	/* Init SDL & Open a Window */
	screen = SDLOpenWindow ( options );
	if (screen == NULL)  /* if opening failed */
	{
		fprintf(stderr, "Unable to load video mode : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	else printf("SDL init OK\n");
	SDL_ShowCursor(SDL_DISABLE);
	page_index = 14; 
	// Display Language Menu
	SetBackgroundPicture ( backgroundPicture, screen, X_POSITION, Y_POSITION );

	while(1)
	{
		Read (switch1_value, val1);		/* Wait for value 1 on Button 1 */
		Read (switch2_value, val2);		/* Wait for value 1 on Button 2 */
		Read (switch3_value, val3);		/* Wait for value 1 on Button 3 */
		Read (switch4_value, val4);		/* Wait for value 1 on Button 3 */
		val = updateVal ( &val1[0], &val2[0], &val3[0], &val4[0] );

		switch (val)
		{
			case BOTH:
				if ( !flag )
				{
					flag = 1;
					SDL_FreeSurface(backgroundPicture);
					SDL_Quit(); /* Stop SDL & free memory */
					return EXIT_SUCCESS;
				}
				break;
			
			case BUTTON_1: //Left Button
				if ( !flag )
				{
					flag = 1;
					if (page_index == 14)
					{
						english = 0;
						if (page_indexTemp > 6)	page_index = page_indexTemp - SHIFT_VALUE;
						else page_index = page_indexTemp;
						SetBackgroundPicture ( backgroundPicture, screen, X_POSITION, Y_POSITION );
					}
					else if ((page_index == 0+english) || (page_index == 2+english))
					{
//						SDL_FreeSurface(backgroundPicture);
//						SDL_Quit(); /* Stop SDL & free memory */
						if (page_index == 2+english) page_index = 0+english;
						webcam(false, english, switch1_value, switch2_value);
						if (page_index == 2+english)
						{
							webcam(true, english, switch1_value, switch2_value);
							system("convert image.ppm image.bmp");
							system("rm image.ppm; mv image.bmp pics/");
							screen = SDLOpenWindow ( options );
							if (screen == NULL)  /* if opening failed */
							{
								fprintf(stderr, "Unable to load video mode : %s\n", SDL_GetError());
								exit(EXIT_FAILURE);
							}
							else printf("SDL init OK\n");
							SDL_ShowCursor(SDL_DISABLE);
							SetBackgroundPicture ( backgroundPicture, screen, X_POSITION, Y_POSITION );
							page_index = 4+english;
							SetBackgroundPicture ( backgroundPicture, screen, 320, 100); //Display image.bmp taken
							page_index = 2+english;
						}
						else if (page_index == 0+english)
							SetBackgroundPicture( backgroundPicture, screen, X_POSITION, Y_POSITION );
					}
					else if (page_index == 3+english) printf("Pas de fonction definie pour cette action\n"); 
				}
				break;

			case BUTTON_2: //Right Button
				if ( !flag )
				{
					flag = 1;
					if (page_index == 14)
					{
						english = SHIFT_VALUE;
						if (page_indexTemp < 7) page_index = page_indexTemp + SHIFT_VALUE;
						else page_index = page_indexTemp;
						SetBackgroundPicture ( backgroundPicture, screen, X_POSITION, Y_POSITION );

					}
					else if (page_index == 0+english) printf("No function set yet\n");
					else if (page_index == 2+english)
					{
						page_index = 6+english;
						SetBackgroundPicture ( backgroundPicture, screen, X_POSITION, Y_POSITION );
						
						// On recupere la date et l'heure actuelles.
						time(&temps);
						date=*localtime(&temps);
						
						// On remplit la chaine avec le format choisi
						strftime(format, 128, "%Y_%m_%d__%X", &date);
						sprintf(commande, "mv pics/image.bmp pics/img_%s_UTC.bmp", format);
						system(commande);
						system(SCP_CMD); //Defined at line 17
						system("rm pics/img*");
						
						page_index = 3+english;
						SetBackgroundPicture ( backgroundPicture, screen, X_POSITION, Y_POSITION );
					}

					else // if page_index == 3+english
					{
						page_index = 0+english;
						SetBackgroundPicture ( backgroundPicture, screen, X_POSITION, Y_POSITION );
					}
				}
				break;
				
			case LANG_CHOICE: //Language choice button
				if ( (!flag) && ((page_index == 0+english)||(page_index == 3+english)) )
				{
					flag = 1;
					page_indexTemp = page_index;
					page_index = 14;
					SetBackgroundPicture ( backgroundPicture, screen, X_POSITION, Y_POSITION );
				}
				break;


			case DIE_DUDE: //Switch-off button
				if ( (!flag) && ((page_index == 0+english)||(page_index == 3+english)||(page_index == 14)) )
				{
/*					flag = 1;
					SDL_FreeSurface(backgroundPicture);
					SDL_Quit(); // Stop SDL & free memory 
					return EXIT_SUCCESS;
*/				
					page_index = 5+english;
					SetBackgroundPicture ( backgroundPicture, screen, X_POSITION, Y_POSITION );
					flag = 1;
					system("shutdown -h now");
				
				}
				break;
			
			case 0:
				flag = 0;
				break;

			default:
				break;
		}//Switch
		
		usleep(20000);
	}//While(1)


	return EXIT_SUCCESS; /* Closing of the program */
}
