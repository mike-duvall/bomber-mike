#include "Selector.h"


#include "../main/Globals.h"

#include "../t3dlib/t3dlib1.h"
#include "../t3dlib/ddutil.h"
#include "../bob/BlitterObject.h"



#define NUM_FRAMES_PER_ANIMATION 5
#define NUM_ANIMATIONS 2

Selector::Selector()
{
	int blockWidth = 52;
	int blockHeight = 44;

	theBlitterObject_ = new BlitterObject(0,0,blockWidth,blockHeight,32,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM | BOB_ATTR_ANIM_ONE_SHOT,DDSCAPS_VIDEOMEMORY, TRANSPARENT_COLOR_KEY);



//	int animations[] = { 0,1,0,2,0 };

	int animations[NUM_ANIMATIONS][NUM_FRAMES_PER_ANIMATION] =
	{
		{ 0,0,0,0,0 },
		{ 0,1,0,2,0 }

	};



	string filename = "bitmaps/Selecting/Selector-New.bmp";

	// load in new bitmap file
	IDirectDrawSurface7 * dds = DDLoadBitmap(lpdd, filename.c_str(), 0, 0 );
	if (dds == 0)
	{
		throw "Could not load bitmap";
	}


	theBlitterObject_->Load_Frame(dds,0,0,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,1,1,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,2,2,0,BITMAP_EXTRACT_MODE_CELL);  

	Unload_Bitmap_File(&bitmap8bit);

//	theBlitterObject_->Load_Animation(0,4,animations);
	theBlitterObject_->Load_Animation(0,NUM_FRAMES_PER_ANIMATION, animations[0] );
	theBlitterObject_->Load_Animation(1,NUM_FRAMES_PER_ANIMATION, animations[1] );

	theBlitterObject_->Set_Animation( 0);
	theBlitterObject_->Set_Anim_Speed(8);
	theBlitterObject_->Set_Vel(0,0);
}




Selector::~Selector()
{
	
}


bool Selector::Update()
{

	this->GetBlitterObject()->Animate();

	return true;
}


