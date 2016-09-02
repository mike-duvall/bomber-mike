
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



#include "../input/Keyboard.h"
#include "../universe/Point.h"

#include "../gameobjects/ControlEvent.h"

#include "../t3dlib/t3dlib1.h"

#include "../bob/BlitterObject.h"


using namespace std;


extern HINSTANCE main_instance;
extern HWND      main_window_handle;


LPDIRECTINPUT8        lpdi      = NULL;    // dinput object


#define TOTAL_NUM_ROWS 11
#define TOTAL_NUM_COLUMNS 13

Keyboard * theKeyboard;
BlitterObject * theBlitterObject_;
int mapLeftX;
int mapTopY;

int moveIncrementAmount;
int initialX;
int initialY;

Controller * theController;



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


	theBlitterObject_ = new BlitterObject(x, y, playerWidth, playerHeight, totalNumFrames,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM, DDSCAPS_VIDEOMEMORY, transparentColorKey);

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


	theBlitterObject_->Load_Frame(dds, 0, 0, 0, BITMAP_EXTRACT_MODE_CELL);

	Unload_Bitmap_File(&bitmap8bit);

	theBlitterObject_->Load_Animation(0, 1, animations);


	theBlitterObject_->Set_Animation(0);
	theBlitterObject_->Set_Anim_Speed(8);
	theBlitterObject_->Set_Vel(0, 0);

	theBlitterObject_->Set_Pos(initialX, initialY);
}



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

	CreateBlitterObject(32, 32);
	theController = theKeyboard;


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



void Mushroom_Update(int controlEvent)
{

	switch (controlEvent)
	{

	case CONTROL_EVENT_MOVE_EAST:
		theBlitterObject_->IncrementX(moveIncrementAmount);
		break;


	case CONTROL_EVENT_MOVE_WEST:
		theBlitterObject_->IncrementX(-moveIncrementAmount);
		break;

	case CONTROL_EVENT_MOVE_SOUTH:
		theBlitterObject_->IncrementY(moveIncrementAmount);
		break;

	case CONTROL_EVENT_MOVE_NORTH:
		theBlitterObject_->IncrementY(-moveIncrementAmount);
		break;

	}

}




bool Mushroom_Update()
{
	int controlEvent = CONTROL_EVENT_DO_NOTHING;

	controlEvent = theController->GetControlEvent();
	Mushroom_Update(controlEvent);

	return false;
}





void Mushroom_Draw(LPDIRECTDRAWSURFACE7 dest)
{
	theBlitterObject_->Draw(dest);
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

