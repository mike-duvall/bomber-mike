#include "DestructableBlock.h"



#include "../t3dlib/t3dlib1.h"
#include "../t3dlib/ddutil.h"
#include "../bob/BlitterObject.h"
#include "../gameobjects/Explosion.h"
#include "../universe/Universe.h"


BlitterObject * DestructableBlock::theArchetypeBlitterObject_ = 0;

DestructableBlock::DestructableBlock(int x, int y)
{

	if(theArchetypeBlitterObject_ == 0)
	{

		int blockWidth = 32;
		int blockHeight = 32;
		theArchetypeBlitterObject_ = new BlitterObject(x,y,blockWidth,blockHeight,32,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY);

		int block_anims[1][4] = { {0,1,0,2}  };


		for (int direction = 0; direction < 1; direction++)
		{ 
			char filename[80];
			// build up file name
			sprintf(filename,"bitmaps/DestructBlock.BMP");

			// load in new bitmap file
			//Load_Bitmap_File(&bitmap8bit,filename);
			IDirectDrawSurface7 * dds = DDLoadBitmap(lpdd, filename, 0, 0 );
			if (dds == 0)
			{
				throw "Could not load bitmap";
			}


			theArchetypeBlitterObject_->Load_Frame(dds,0+direction*4,0,0,BITMAP_EXTRACT_MODE_CELL);  
			theArchetypeBlitterObject_->Load_Frame(dds,1+direction*4,1,0,BITMAP_EXTRACT_MODE_CELL);  
			theArchetypeBlitterObject_->Load_Frame(dds,2+direction*4,2,0,BITMAP_EXTRACT_MODE_CELL);  
			theArchetypeBlitterObject_->Load_Frame(dds,3+direction*4,0,1,BITMAP_EXTRACT_MODE_CELL);  


			// unload the bitmap file
			Unload_Bitmap_File(&bitmap8bit);

			// set the animation sequences
			theArchetypeBlitterObject_->Load_Animation(direction,4,block_anims[direction]);

		} // end for direction


		theArchetypeBlitterObject_->Set_Animation( 0);
		theArchetypeBlitterObject_->Set_Anim_Speed(4);
		theArchetypeBlitterObject_->Set_Vel(0,0);
	}

	theBlitterObject_ = theArchetypeBlitterObject_->Clone();
	theBlitterObject_->Set_Pos(x,y);
	theBlitterObject_->Set_Anim_Speed(4);


	


}


DestructableBlock::~DestructableBlock()
{

}



bool DestructableBlock::Update()
{
//	bool shouldRemove = Explosion::IsBlitterObjectInAnyExplosion(this );
	bool shouldRemove = ExplosionPart::IsGameObjectInAnyExplosionPart(this );
	return shouldRemove;

}
