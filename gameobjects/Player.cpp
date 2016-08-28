#include "Player.h"


#include "../t3dlib/t3dlib1.h"
#include "../t3dlib/ddutil.h"
#include "../bob/BlitterObject.h"



#include "../input/Controller.h"


#include "ControlEvent.h"


#include <iostream>
#include <sstream>
using namespace std;


#define EAST         0
#define NORTH        1
#define WEST         2
#define SOUTH        3

#define NUM_FRAMES_PER_ANIMATION 4
#define NUM_ANIMATIONS 4



void Player::HandleMoveDown()
{
	theBlitterObject_->IncrementY(moveIncrementAmount);
	// check animation needs to change
	if (theBlitterObject_->Get_Current_Animation() != SOUTH)
		theBlitterObject_->Set_Animation(SOUTH);
	theBlitterObject_->Animate();
}



void Player::HandleMoveUp()
{
	theBlitterObject_->IncrementY(-moveIncrementAmount);
	// check animation needs to change
	if (theBlitterObject_->Get_Current_Animation() != NORTH)
		theBlitterObject_->Set_Animation(NORTH);
	theBlitterObject_->Animate();
}


void Player::HandleMoveRight(int controlEvent)
{
	theBlitterObject_->IncrementX(moveIncrementAmount);
}


void Player::HandleMoveLeft(int controlEvent)
{
	theBlitterObject_->IncrementX(-moveIncrementAmount);
	// check animation needs to change
	if (theBlitterObject_->Get_Current_Animation() != WEST)
		theBlitterObject_->Set_Animation(WEST);
	theBlitterObject_->Animate();
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

	int playerWidth = 44;
	int playerHeight = 44;

	int totalNumFrames = 12;
	int transparentColorKey = RGB(0,107,0);


	theBlitterObject_ = new BlitterObject(x,y,playerWidth,playerHeight,totalNumFrames,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY, transparentColorKey);

	int animations[NUM_ANIMATIONS][NUM_FRAMES_PER_ANIMATION] =
	{
			{0,1,0,2},
			{3,4,3,5},
			{6,7,6,8},
			{9,10,9,11}
	 };


	string shortFileName = "WhitePlayer.bmp";
	

	string pathPrefix = "";
	string longFilename = "bitmaps/" + shortFileName;

	// load in new bitmap file
	IDirectDrawSurface7 * dds = DDLoadBitmap(lpdd, longFilename.c_str(), 0, 0 );
	if (dds == 0)
	{
		throw "Could not load bitmap";
	}


	int frameNumber = 0;
	for(int row = 0; row < 4; row++)
	{ 
		for(int column = 0; column < 3; column++)
		{
		theBlitterObject_->Load_Frame(dds,frameNumber,column, row,BITMAP_EXTRACT_MODE_CELL);  
		frameNumber++;
		}

	}

	Unload_Bitmap_File(&bitmap8bit);

	// set the animation sequences

	for(int animation = 0; animation < 4; animation++)
	{
		theBlitterObject_->Load_Animation(animation,NUM_FRAMES_PER_ANIMATION, animations[animation]);
	}


	theBlitterObject_->Set_Animation(0);
	theBlitterObject_->Set_Anim_Speed(8);
	theBlitterObject_->Set_Vel(0,0);

	theBlitterObject_->Set_Pos(initialX, initialY);

	theBlitterObject_->Set_Animation(SOUTH);

	BOB * bob = theBlitterObject_->getTheBOB();
	bob->curr_frame = bob->animations[bob->curr_animation][bob->anim_index];



}



Player::~Player()
{
	delete theBlitterObject_;
}




