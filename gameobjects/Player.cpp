#include "Player.h"


#include "../t3dlib/t3dlib1.h"
#include "../t3dlib/ddutil.h"
#include "../bob/BlitterObject.h"



#include "../input/Controller.h"


#include "ControlEvent.h"


#include <iostream>
#include <sstream>
using namespace std;







void Player::HandleMoveDown()
{
	theBlitterObject_->IncrementY(moveIncrementAmount);
}



void Player::HandleMoveUp()
{
	theBlitterObject_->IncrementY(-moveIncrementAmount);
}


void Player::HandleMoveRight(int controlEvent)
{
	theBlitterObject_->IncrementX(moveIncrementAmount);
}


void Player::HandleMoveLeft(int controlEvent)
{
	theBlitterObject_->IncrementX(-moveIncrementAmount);
}




bool Player::Update()
{
	int controlEvent = CONTROL_EVENT_DO_NOTHING;

	controlEvent = this->theController->GetControlEvent();
	this->Update(controlEvent);

	return false;
}



void Player::Update(int controlEvent)
{

	switch(controlEvent)
	{

	case CONTROL_EVENT_MOVE_EAST:
		HandleMoveRight(controlEvent);
		break;


	case CONTROL_EVENT_MOVE_WEST:
		HandleMoveLeft(controlEvent);
		break;

	case CONTROL_EVENT_MOVE_SOUTH:
		HandleMoveDown();
		break;

	case CONTROL_EVENT_MOVE_NORTH:
		HandleMoveUp();
		break;

	}
	
}



void Player::Draw(LPDIRECTDRAWSURFACE7 dest)
{
	theBlitterObject_->Draw(dest);
}



Player::Player()
{

	theBlitterObject_ = 0;
}

Player::Player(int x, int y)
{
	x -= 6;
	y -= 12;

	initialX = x;
	initialY = y;

	moveIncrementAmount = 2;

	//int playerWidth = 44;
	//int playerHeight = 44;

	int playerWidth = 128;
	int playerHeight = 128;


	//int totalNumFrames = 12;
	int totalNumFrames = 1;
	int transparentColorKey = RGB(0,107,0);


	theBlitterObject_ = new BlitterObject(x,y,playerWidth,playerHeight,totalNumFrames,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY, transparentColorKey);

	int animations[] = { 0 };

	string shortFileName = "WhitePlayerMushroom.bmp";
	

	string pathPrefix = "";
	string longFilename = "bitmaps/" + shortFileName;

	// load in new bitmap file
	IDirectDrawSurface7 * dds = DDLoadBitmap(lpdd, longFilename.c_str(), 0, 0 );
	if (dds == 0)
	{
		throw "Could not load bitmap";
	}


	theBlitterObject_->Load_Frame(dds, 0,0,0,  BITMAP_EXTRACT_MODE_CELL);

	Unload_Bitmap_File(&bitmap8bit);

	theBlitterObject_->Load_Animation(0, 1, animations);


	theBlitterObject_->Set_Animation(0);
	theBlitterObject_->Set_Anim_Speed(8);
	theBlitterObject_->Set_Vel(0,0);

	theBlitterObject_->Set_Pos(initialX, initialY);
}



Player::~Player()
{
	delete theBlitterObject_;
}




