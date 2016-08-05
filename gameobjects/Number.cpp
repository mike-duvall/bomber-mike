#include "Number.h"


#include "../bob/BlitterObject.h"
#include <iostream>
#include <sstream>
using namespace std;

#include "../t3dlib/ddutil.h"

#define NUM_ANIMATIONS 10
#define NUM_FRAMES_PER_ANIMATION 1



Number::Number(int x, int y)
{

	theBlitterObject_ = new BlitterObject(x,y,16, 16,10,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY);

	int animations[NUM_ANIMATIONS][NUM_FRAMES_PER_ANIMATION] =
	{
		{0},
		{1},
		{2},
		{3},
		{4},
		{5},
		{6},
		{7},
		{8},
		{9}
	};




	string filename = string("../bitmaps/InGame/Scoreboard/Numbers.bmp");

	IDirectDrawSurface7 * dds = DDLoadBitmap(lpdd, filename.c_str(), 0, 0 );

	if(dds == 0)
	{
		throw "Could not load bitmap";
	}
	theBlitterObject_->Load_Frame(dds,0,0,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,1,1,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,2,2,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,3,3,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,4,4,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,5,5,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,6,6,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,7,7,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,8,8,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlitterObject_->Load_Frame(dds,9,9,0,BITMAP_EXTRACT_MODE_CELL);  

	// unload the bitmap file
	Unload_Bitmap_File(&bitmap8bit);


	for(int animIndex = 0; animIndex < 10; animIndex++)
	{
		theBlitterObject_->Load_Animation(animIndex, 1,animations[animIndex]);
	}



	theBlitterObject_->Set_Animation( 0);
	theBlitterObject_->Set_Anim_Speed(0);
	theBlitterObject_->Set_Vel(0,0);

	theBlitterObject_->Set_Pos(x,y);

}


void Number::SetValue(int aValue)
{
	theBlitterObject_->Set_Animation( aValue);
	theBlitterObject_->Animate();
}

int Number::GetValue()
{
	return this->GetBlitterObject()->Get_Current_Animation();
}



