#include "Player.h"


#include "../t3dlib/t3dlib1.h"
#include "../t3dlib/ddutil.h"
#include "../bob/BlitterObject.h"
#include "../universe/Universe.h"

#include "SimpleGameObject.h"
#include "Number.h"
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
	this->GetBlitterObject()->IncrementY(moveIncrementAmount);
	// check animation needs to change
	if (this->GetBlitterObject()->Get_Current_Animation() != SOUTH)
		this->GetBlitterObject()->Set_Animation(SOUTH);
	this->GetBlitterObject()->Animate();
}



void Player::HandleMoveUp()
{
	this->GetBlitterObject()->IncrementY(-moveIncrementAmount);
	// check animation needs to change
	if (this->GetBlitterObject()->Get_Current_Animation() != NORTH)
		this->GetBlitterObject()->Set_Animation(NORTH);
	this->GetBlitterObject()->Animate();

}


bool Player::HandleMoveRight(int controlEvent)
{
	this->GetBlitterObject()->IncrementX(moveIncrementAmount);
	return true;
}


void Player::HandleMoveLeft(int controlEvent)
{
	this->GetBlitterObject()->IncrementX(-moveIncrementAmount);
	// check animation needs to change
	if (this->GetBlitterObject()->Get_Current_Animation() != WEST)
		this->GetBlitterObject()->Set_Animation(WEST);
	this->GetBlitterObject()->Animate();

}




bool Player::Update()
{
	int controlEvent = CONTROL_EVENT_DO_NOTHING;
	bool playerMoved = FALSE;

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

	int drawBoundingBox = 0;

	if(drawBoundingBox)
	{
		this->DrawCollisionBox(dest);
	}
}


string Player::GetNameFromPlayerType()
{
	int aPlayerType = this->GetPlayerType();
	switch(aPlayerType)
	{
	case WHITE_PLAYER:
		return "White";
		break;
	case BLACK_PLAYER:
		return "Black";
		break;
	case RED_PLAYER:
		return "Red";
		break;
	case BLUE_PLAYER:
		return "Blue";
		break;

	}
	return "";
}


string Player::GetBitmapFilenameFromPlayerType(int aPlayerType)
{
 	return  GetNameFromPlayerType() + string("Player.bmp");
}






void Player::SetInitialValuesForNewMatch()
{
	numberOfWins = 0;
}

void Player::SetInitialValuesForNewRound()
{
	playerState = PLAYER_STATE_ALIVE;

	this->GetBlitterObject()->Set_Pos(initialX, initialY);

	theBlitterObject_->Set_Animation(SOUTH);

	BOB * bob = theBlitterObject_->getTheBOB();
	bob->curr_frame = bob->animations[bob->curr_animation][bob->anim_index];

}


Player::Player()
{

	theBlitterObject_ = 0;
}

Player::Player(int x, int y, int aPlayerType)
{

	x -= 6;
	y -= 12;



	initialX = x;
	initialY = y;

	playerType = aPlayerType;
	name = 	GetNameFromPlayerType();
	moveIncrementAmount = 2;
	playerState = PLAYER_STATE_ALIVE;
	numberOfWins = 0;

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


	string shortFileName = GetBitmapFilenameFromPlayerType(playerType);
	

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

	theCollisionBOB_  = new BOB();


}




