#include "SimpleGameObject.h"



#include "../t3dlib/ddutil.h"
#include "../bob/BlitterObject.h"



SimpleGameObject::SimpleGameObject(int x, int y, int blockWidth, int blockHeight, const string & shortFilename,DWORD colorKey)
{

	theBlitterObject_ = new BlitterObject(x,y,blockWidth,blockHeight,32,
	BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY,colorKey);

	int animations[] = {0};

	string filename = string("../bitmaps/").operator +=(shortFilename);

	IDirectDrawSurface7 * dds = DDLoadBitmap(lpdd, filename.c_str(), 0, 0 );

	if(dds == 0)
	{
		throw "Could not load bitmap";
	}
	theBlitterObject_->Load_Frame(dds,0,0,0,BITMAP_EXTRACT_MODE_CELL);  

	// unload the bitmap file
	Unload_Bitmap_File(&bitmap8bit);

	theBlitterObject_->Load_Animation(0, 1,animations);


	theBlitterObject_->Set_Animation( 0);
	theBlitterObject_->Set_Anim_Speed(4);
	theBlitterObject_->Set_Vel(0,0);

	theBlitterObject_->Set_Pos(x,y);


	int xx = 3;

}




SimpleGameObject::~SimpleGameObject()
{


}