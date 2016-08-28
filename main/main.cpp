
#define WIN32_LEAN_AND_MEAN  

#define INITGUID 

#include <windows.h>
#include <iostream>

#include <math.h>
#include <ctime> 
#include <ddraw.h> 
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "../t3dlib/t3dlib1.h"

#include "../bob/BlitterObject.h"

#include "../gameobjects/Player.h"


#include "../input/Keyboard.h"

#include "../universe/Point.h"
#include "../gamestate/Playing.h"



using namespace std;


extern HINSTANCE main_instance;
extern HWND      main_window_handle;

#include "../gameobjects/ControlEvent.h"


LPDIRECTINPUT8        lpdi      = NULL;    // dinput object
Playing * playingGameState;



#define TOTAL_NUM_ROWS 11
#define TOTAL_NUM_COLUMNS 13

Keyboard * theKeyboard;
Player * thePlayer;
int mapLeftX;
int mapTopY;


int Game_Init(void *parms,  int num_parms)
{

	int windowed = true;
	DDraw_Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, windowed);

	// first create the direct input object
	if (DirectInput8Create(main_instance,DIRECTINPUT_VERSION,IID_IDirectInput8, (void **)&lpdi,NULL)!=DI_OK)
		return(0);

	theKeyboard = new Keyboard(lpdi, main_window_handle);


	// set clipping rectangle to screen extents so mouse cursor
	// doens't mess up at edges
	RECT screen_rect = {0,0,screen_width,screen_height};
	lpddclipper = DDraw_Attach_Clipper(lpddsback,1,&screen_rect);

	// hide the mouse
	ShowCursor(FALSE);

	thePlayer = new Player(32, 32);
	thePlayer->SetController(theKeyboard);

	//int columnOffset = 13 * 32;
	//int rowOffset = 11 * 32;

	
	mapLeftX = 20;
	mapTopY = 50;

	thePlayer->SetInitialValuesForNewRound();


	playingGameState =  new Playing();


	return(1);

} // end Game_Init

///////////////////////////////////////////////////////////

int Game_Shutdown(void *parms,  int num_parms)
{

	lpdi->Release();
	DDraw_Shutdown();
	return(1);
} 

///////////////////////////////////////////////////////////



int Game_Main(void *parms, int num_parms)
{

	// check of user is trying to exit
	if (KEY_DOWN(VK_ESCAPE) )
		PostMessage(main_window_handle, WM_DESTROY,0,0);


	// start the timing clock
	Start_Clock();


	playingGameState->Update();


	// sync to 30 fps
//	Wait_Clock(30);
//	Wait_Clock(20);
	Wait_Clock(1);


	return(1);

} 


