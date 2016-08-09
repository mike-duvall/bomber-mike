#include "ExplodingPlayer.h"


#include "../t3dlib/t3dlib1.h"
#include "../t3dlib/ddutil.h"
#include "../bob/BlitterObject.h"
#include "../universe/Universe.h"




string GetExplodingBitmapFilenameFromPlayerType(int aPlayerType)
{
	switch(aPlayerType)
	{
	case WHITE_PLAYER:
		return "WhitePlayerExploding.bmp";
		break;
	case BLACK_PLAYER:
		return "BlackPlayerExploding.bmp";
		break;
	case RED_PLAYER:
		return "RedPlayerExploding.bmp";
		break;
	case BLUE_PLAYER:
		return "BluePlayerExploding.bmp";
		break;

	}
	return "";
}



ExplodingPlayer::ExplodingPlayer(int x, int y, int aPlayerType)
{

	x -= 6;
	y -= 12;


	int playerWidth = 44;
	int playerHeight = 46;

	int numFrames = 9;
	int transparentColorKey = RGB(0,107,0);


	state = EXPLODING_PLAYER_STATE_WIGGLING;
	wiggleCountdownInitialValue = 50;
	wiggleCountdownTimer = wiggleCountdownInitialValue;

	explodionCountdownInitialValue = 50;
	explosionCountdownTimer = explodionCountdownInitialValue;


	theBlitterObject_ = new BlitterObject(x,y,playerWidth,playerHeight,numFrames,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY, transparentColorKey);


	int animation[2][8] = {
		{ 0,1,0,1,0,1,0,1},
		{ 1,2,3,4,5,6,7,8}
	};

	string shortFileName = GetExplodingBitmapFilenameFromPlayerType(aPlayerType);

	string pathPrefix = "bitmaps/";
	string longFilename = pathPrefix.operator +=(shortFileName);


	IDirectDrawSurface7 * dds = DDLoadBitmap(lpdd, longFilename.c_str(), 0, 0 );
	if (dds == 0)
	{
		throw "Could not load bitmap";
	}


	theBlitterObject_->Load_Frame(dds,0,0,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,1,1,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,2,2,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,3,0,1,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,4,1,1,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,5,2,1,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,6,0,2,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,7,1,2,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,8,2,2,BITMAP_EXTRACT_MODE_CELL);  

	Unload_Bitmap_File(&bitmap8bit);

	theBlitterObject_->Load_Animation(0,8,animation[0]);
	theBlitterObject_->Load_Animation(1,8,animation[1]);
	
	theBlitterObject_->Set_Animation(0);
	theBlitterObject_->Set_Anim_Speed(8);
	theBlitterObject_->Set_Vel(0,0);

	theBlitterObject_->Set_Pos(x,y);

}


bool ExplodingPlayer::Update()
{
  bool remove = FALSE;
  if(state == EXPLODING_PLAYER_STATE_WIGGLING)
  {
	wiggleCountdownTimer--;
	if(wiggleCountdownTimer <= 0)
	{
		state = EXPLODING_PLAYER_STATE_EXPLODING;
		this->GetBlitterObject()->Set_Animation(1);
	}
  }
  else
  if( state == EXPLODING_PLAYER_STATE_EXPLODING)
  {
	  explosionCountdownTimer--;
	  if(explosionCountdownTimer <= 0)
	  {
		  remove = TRUE;
	  }
		  
  }

  this->theBlitterObject_->Animate();

  return remove;


}

