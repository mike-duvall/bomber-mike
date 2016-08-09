#include "FlamePowerup.h"



#include "../t3dlib/t3dlib1.h"
#include "../t3dlib/ddutil.h"
#include "../bob/BlitterObject.h"
#include "../gameobjects/Player.h"

BlitterObject * FlamePowerup::theArchetypeBlitterObject_ = 0;

FlamePowerup::FlamePowerup(int x, int y ) : Powerup(x,y)
{

	if(theArchetypeBlitterObject_ == 0)
	{

		SetupArchetype();
	}

	theBlitterObject_ = theArchetypeBlitterObject_->Clone();
	theBlitterObject_->Set_Pos(x,y);

}



void FlamePowerup::Activate(Player * aPlayer)
{
	int currentExplosionSize = aPlayer->GetExplosionSize();
	currentExplosionSize++;
	aPlayer->SetExplosionSize(currentExplosionSize);
}



void FlamePowerup::SetupArchetype()
{
	int blockWidth = 32;
	int blockHeight = 32;

	int transparentColorKey = RGB(0,107,0);

	theArchetypeBlitterObject_ = new BlitterObject(0,0,blockWidth,blockHeight,32,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY, transparentColorKey);


	int block_anims[8][4] = { {0,1,0,1},
	{0+4,1+4,0+4,2+4},
	{0+8,1+8,0+8,2+8},
	{0+12,1+12,0+12,2+12},
	{0+16,1+16,0+16,2+16},
	{0+20,1+20,0+20,2+20},
	{0+24,1+24,0+24,2+24},
	{0+28,1+28,0+28,2+28}, };


	// load the frames in 8 directions, 4 frames each
	// each set of frames has a walk and a fire, frame sets
	// are loaded in counter clockwise order looking down
	// from a birds eys view or the x-z plane
	for (int direction = 0; direction < 1; direction++)
	{ 
		char filename[80];
		// build up file name
		sprintf(filename,"bitmaps/FlamePowerup.BMP",direction);

		// load in new bitmap file
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


		theArchetypeBlitterObject_->Load_Animation(direction,4,block_anims[direction]);

	} // end for direction


	theArchetypeBlitterObject_->Set_Animation( 0);
	theArchetypeBlitterObject_->Set_Anim_Speed(6);
	theArchetypeBlitterObject_->Set_Vel(0,0);

}



