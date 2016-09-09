
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
#include "../t3dlib/ddutil.h"



#define CONTROL_EVENT_MOVE_EAST 1
#define CONTROL_EVENT_MOVE_SOUTH 3
#define CONTROL_EVENT_MOVE_WEST 5
#define CONTROL_EVENT_MOVE_NORTH 7

#define CONTROL_EVENT_DO_NOTHING 10

#include "../t3dlib/t3dlib1.h"


using namespace std;


extern HINSTANCE main_instance;
extern HWND      main_window_handle;

LPDIRECTINPUTDEVICE8  lpdikey;
UCHAR keyboard_state[256];



LPDIRECTINPUT8        lpdi      = NULL;    // dinput object


//Keyboard * theKeyboard;
BOB * theBOB_;
int mapLeftX;
int mapTopY;

int moveIncrementAmount;
int initialX;
int initialY;





void CreateBlitterObject(int x, int y)
{
	x -= 6;
	y -= 12;

	initialX = x;
	initialY = y;

	moveIncrementAmount = 2;

	int playerWidth = 128;
	int playerHeight = 128;

	int totalNumFrames = 1;
	int transparentColorKey = RGB(0, 107, 0);

	
	theBOB_ = new BOB();
	if (!Create_BOB(theBOB_, x, y, playerWidth, playerHeight, totalNumFrames, BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM, DDSCAPS_VIDEOMEMORY, transparentColorKey, 8))
	{
		throw "Unable to create BOB";
	}


	int animations[] = { 0 };

	string shortFileName = "WhitePlayerMushroom.bmp";


	string pathPrefix = "";
	string longFilename = "bitmaps/" + shortFileName;

	// load in new bitmap file
	IDirectDrawSurface7 * dds = DDLoadBitmap(lpdd, longFilename.c_str(), 0, 0);
	if (dds == 0)
	{
		throw "Could not load bitmap";
	}


	Load_Frame_BOB(theBOB_, dds, 0, 0, 0, BITMAP_EXTRACT_MODE_CELL);

	Unload_Bitmap_File(&bitmap8bit);

	Load_Animation_BOB(theBOB_, 0, 1, animations);
	Set_Animation_BOB(theBOB_, 0);
	Set_Pos_BOB(theBOB_, initialX, initialY);
}





int Game_Init(void *parms,  int num_parms)
{

	int windowed = true;
	DDraw_Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, windowed);

	// first create the direct input object
	if (DirectInput8Create(main_instance,DIRECTINPUT_VERSION,IID_IDirectInput8, (void **)&lpdi,NULL)!=DI_OK)
		return(0);

//	theKeyboard = new Keyboard(lpdi, main_window_handle);

	if (lpdi->CreateDevice(GUID_SysKeyboard, &lpdikey, NULL) != DI_OK)
	{
		throw "Error initializing keyboard";
	}


	// set cooperation level
	if (lpdikey->SetCooperativeLevel(main_window_handle,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) != DI_OK)
	{
		throw "Error initializing keyboard";
	}


	if (lpdikey->SetDataFormat(&c_dfDIKeyboard) != DI_OK)
	{
		throw "Error initializing keyboard";
	}


	if (lpdikey->Acquire() != DI_OK)
	{
		throw "Error initializing keyboard";
	}



	// set clipping rectangle to screen extents so mouse cursor
	// doens't mess up at edges
	RECT screen_rect = {0,0,screen_width,screen_height};
	lpddclipper = DDraw_Attach_Clipper(lpddsback,1,&screen_rect);

	// hide the mouse
	ShowCursor(FALSE);

	CreateBlitterObject(32, 32);


	mapLeftX = 20;
	mapTopY = 50;

	return(1);

} // end Game_Init





int Game_Shutdown(void *parms,  int num_parms)
{

	lpdi->Release();
	DDraw_Shutdown();
	return(1);
} 


//Next:  Get rid of Keyboard class.  Just read keyboard directly.  Get rid of defines of control event
//	Then: start trimming down t3dlib code

void Mushroom_Update()
{

	lpdikey->GetDeviceState(256, (LPVOID)keyboard_state);


	if (keyboard_state[DIK_UP])
	{
		theBOB_->y -= moveIncrementAmount;
	}
	else
	if (keyboard_state[DIK_RIGHT])
	{
		theBOB_->x += moveIncrementAmount;
	}
	else
	if (keyboard_state[DIK_DOWN])
	{
		theBOB_->y += moveIncrementAmount;
	}
	else
	if (keyboard_state[DIK_LEFT])
	{
		theBOB_->x -= moveIncrementAmount;
	}

}




void Mushroom_Draw(LPDIRECTDRAWSURFACE7 dest)
{
	Draw_BOB_To_Relative_Coordinates(theBOB_, dest, mapLeftX, mapTopY);
}





void Update()
{
	// clear the drawing surface
	DWORD backgroundColor = _RGB32BIT(0, 0, 0, 0);
	DDraw_Fill_Surface(lpddsback, backgroundColor);
	Mushroom_Update();
	Mushroom_Draw(lpddsback);
	DDraw_Flip();
}



int Game_Main(void *parms, int num_parms)
{

	// check of user is trying to exit
	if (KEY_DOWN(VK_ESCAPE) )
		PostMessage(main_window_handle, WM_DESTROY,0,0);


	// start the timing clock
	Start_Clock();
	Update();

	// sync to 30 fps
//	Wait_Clock(30);
//	Wait_Clock(20);
	Wait_Clock(1);

	return(1);
} 

