#include "IndestructableBlock.h"



#include "../t3dlib/t3dlib1.h"
#include "../t3dlib/ddutil.h"
#include "../bob/BlitterObject.h"
#include "../universe/Universe.h"



BlitterObject * IndestructableBlock::theArchetypeBlitterObject_ = 0;


IndestructableBlock::IndestructableBlock(int x, int y)
{

	if(theArchetypeBlitterObject_ == 0)
	{

		int blockWidth = MAP_BLOCK_WIDTH;
		int blockHeight = MAP_BLOCK_HEIGHT;
		theArchetypeBlitterObject_ = new BlitterObject(x,y,blockWidth,blockHeight,32,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY);

		int animations[] = {0};

		string filename = "bitmaps/IndestructBlock.bmp";

		IDirectDrawSurface7 * dds = DDLoadBitmap(lpdd, filename.c_str(), 0, 0 );
		if (dds == 0)
		{
			throw "Could not load bitmap";
		}


		theArchetypeBlitterObject_->Load_Frame(dds,0,0,0,BITMAP_EXTRACT_MODE_CELL);  

		// unload the bitmap file
		Unload_Bitmap_File(&bitmap8bit);

		theArchetypeBlitterObject_->Load_Animation(0, 1,animations);


		theArchetypeBlitterObject_->Set_Animation( 0);
		theArchetypeBlitterObject_->Set_Anim_Speed(4);
		theArchetypeBlitterObject_->Set_Vel(0,0);
	}

	theBlitterObject_ = theArchetypeBlitterObject_->Clone();
	theBlitterObject_->Set_Pos(x,y);
	theBlitterObject_->Set_Anim_Speed(4);


	int xx = 3;

}




IndestructableBlock::~IndestructableBlock()
{

}