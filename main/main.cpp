
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
#include "../input/Joystick.h"

#include "../universe/Universe.h"
#include "../universe/Point.h"
#include "../gamestate/TitleGameState.h"
#include "../gamestate/SelectingNumPlayers.h"

#include "../sound/MSound.h"


using namespace std;



extern HINSTANCE main_instance;
extern HWND      main_window_handle;


#include "../gameobjects/ControlEvent.h"


LPDIRECTINPUT8        lpdi      = NULL;    // dinput object
GameState * currentGameState;



void Set_Pallete_From_Bitmap(string filename)
{
	Load_Bitmap_File(&bitmap8bit, (char *)filename.c_str());
	Set_Palette(bitmap8bit.palette);
	Unload_Bitmap_File(&bitmap8bit);

}


#define TOTAL_NUM_ROWS 11
#define TOTAL_NUM_COLUMNS 13


void CreateIndestructableBlocks()
{

	// top row
// 	int x = Universe::GetMapLeftX();
// 	int y = Universe::GetMapTopY();

	int x = 0;
	int y = 0;



//	BombPowerup * aBombPowerup = new BombPowerup(x + 64 + 32, y + 32 + 32);
//	Universe::GetPowerups().push_back(aBombPowerup);
//
//	FlamePowerup * aFlamePowerup = new FlamePowerup(x + 64 + 32, y + 32 + 32 + 64);
//	Universe::GetPowerups().push_back(aFlamePowerup);
//
//	aBombPowerup = new BombPowerup(x + 5 * 32, y + 5 * 32);
//	Universe::GetPowerups().push_back(aBombPowerup);
//
//	aFlamePowerup = new FlamePowerup(x + 7 * 32, y + 9 * 32);
//	Universe::GetPowerups().push_back(aFlamePowerup);
//
//
//	aBombPowerup = new BombPowerup(x + 13 * 32, y + 8 * 32);
//	Universe::GetPowerups().push_back(aBombPowerup);
//
//	aFlamePowerup = new FlamePowerup(x + 5 * 32, y + 11 * 32);
//	Universe::GetPowerups().push_back(aFlamePowerup);
//
//
//
//
//	// top row
//	Block * aBlock = 0;
//	for(int i = 0; i < 15; i++)
//	{
//		aBlock = new IndestructableBlock(x, y );
//		Universe::GetAllBlocks().push_back(aBlock);
//		x += 32;
//	}
//
//	// left column
////	x = Universe::GetMapLeftX();
//	x = 0;
//	y = 32;
//	for(int i = 0; i < 12; i++)
//	{
//		aBlock = new IndestructableBlock(x, y );
//		Universe::GetAllBlocks().push_back(aBlock);
//		y += 32;
//	}
//
//	// bottom row
//	x = 32;
//	y = 32 * 12;
//	for(int i = 0; i < 14; i++)
//	{
//		aBlock = new IndestructableBlock(x, y );
//		Universe::GetAllBlocks().push_back(aBlock);
//		x += 32;
//	}
//
//
//	// right row
//	x = 14*32;
//	y = 32;
//	for(int i = 0; i < 11; i++)
//	{
//		aBlock = new IndestructableBlock(x, y );
//		Universe::GetAllBlocks().push_back(aBlock);
//		y += 32;
//	}
//
//
//	y = 32 + 32;
//
//	for(int row = 0; row < 5; row++, y += 64)
//	{
//		x =  32 + 32;
//		for(int i = 0; i < 6; i++)
//		{
//			aBlock = new IndestructableBlock(x, y );
//			Universe::GetAllBlocks().push_back(aBlock);
//			x += 64;
//		}
//
//	}


}


void CreateDestructableBlocks()
{

//	int blockMap[TOTAL_NUM_ROWS][TOTAL_NUM_COLUMNS] = {
//			{0,0,0,1,1,1,1,1,1,1,0,0,0},
// 			{0,0,1,0,1,0,1,0,1,0,1,0,0},
//			{0,0,1,1,1,1,1,1,1,1,1,1,0},
//			{1,0,1,0,1,0,0,0,1,0,1,0,1},
//			{1,1,1,1,1,1,0,1,1,1,1,1,1},
//			{1,0,0,0,0,0,0,0,0,0,1,0,1},
//			{1,1,1,1,1,1,0,1,1,1,0,1,1},
//			{1,0,1,0,1,0,0,0,1,0,1,0,1},
//			{0,1,1,0,1,0,1,1,1,1,1,1,0},
//			{0,0,1,0,1,0,1,0,1,0,1,0,0},
//			{0,0,0,1,1,0,1,1,1,1,0,0,0},
//
//	};
//
//
//// 	 	int blockMap[TOTAL_NUM_ROWS][TOTAL_NUM_COLUMNS] = {
//// 	 			{0,0,0,0,1,0,0,0,0,0,0,0,0},
//// 	 			{0,0,0,0,0,0,0,0,0,0,0,0,0},
//// 	 			{1,0,0,0,1,0,0,0,0,0,0,0,0},
//// 	 			{0,0,0,0,0,0,0,0,0,0,0,0,0},
//// 	 			{0,0,0,0,1,0,0,0,0,0,0,0,0},
//// 	 			{0,0,0,0,0,0,0,0,0,0,0,0,0},
//// 	 			{0,0,0,0,1,0,0,0,0,0,1,0,0},
//// 	 			{0,0,0,0,0,0,0,0,0,0,0,0,0},
//// 	 			{0,0,0,0,1,0,0,0,0,0,1,0,0},
//// 	 			{0,0,0,0,1,0,0,0,0,0,0,0,0},
//// 	 			{0,0,0,0,1,0,0,0,0,0,1,0,0},
//// 	 
//// 	 	};
//
//
//
//
//	for(int row = 0; row < TOTAL_NUM_ROWS; row++ )
//	{
//		for(int column = 0; column < TOTAL_NUM_COLUMNS; column++)
//		{
//			if( blockMap[row][column] )
//			{
//				DestructableBlock * aDestructableBlock;
//				int x = (column + 1) * 32;
//				int y = (row + 1) * 32;
//
//				aDestructableBlock = new DestructableBlock(x,y );
//				Universe::GetAllBlocks().push_back(aDestructableBlock);
//
//			}
//		}
//	}


}

void BuildMap()
{
	CreateIndestructableBlocks();
	CreateDestructableBlocks();
}




int Game_Init(void *parms,  int num_parms)
{

//	srand((unsigned)time(NULL));

// 	for (int x = 0; x <= mapWidth; x++){
// 		for (int y = 0; y <= mapHeight; y++){
// 			walkability [x][y] = walkable;
// 		}
// 	}
// 
// 	int pathfinderID = 1;
// 	int startingX = 16;
// 	int startingY = 16;
//     int targetX = 120;
// 	int targetY = 120;
// 
// 	int result = FindPath (pathfinderID, startingX, startingY, targetX,  targetY);
// 
// 
// 	ReadPath(pathfinderID, startingX ,startingY, 32);
// 




	int windowed = true;
	DDraw_Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, windowed);

	// first create the direct input object
	if (DirectInput8Create(main_instance,DIRECTINPUT_VERSION,IID_IDirectInput8, (void **)&lpdi,NULL)!=DI_OK)
		return(0);

	Universe::SetKeyboard(new Keyboard(lpdi, main_window_handle) );

	Joystick::InitializeJoysticks(lpdi, main_window_handle);




	// set the palette to background image palette
//	Set_Pallete_From_Bitmap("../bitmaps/WhitePlayer.bmp");



	
	// set clipping rectangle to screen extents so mouse cursor
	// doens't mess up at edges
	RECT screen_rect = {0,0,screen_width,screen_height};
	lpddclipper = DDraw_Attach_Clipper(lpddsback,1,&screen_rect);

	// hide the mouse
	ShowCursor(FALSE);


	Sound::InitSounds();

	//currentGameState = new TitleGameState();
	currentGameState = new SelectingNumPlayers();


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

//	Sound::InitSounds();
// 
// 
// 	Sound::PlaySound(soundId);
	

	// start the timing clock
	Start_Clock();

	currentGameState = currentGameState->Update();


	// sync to 30 fps
//	Wait_Clock(30);
//	Wait_Clock(20);
	Wait_Clock(1);


	return(1);

} 


