#include "BlitterObject.h"

#include "../universe/Universe.h"


BlitterObject::BlitterObject(
			   int x, int y,          // initial posiiton
			   int width, int height, // size of bob
			   int num_frames,        // number of frames
			   int attr,              // attrs
			   int mem_flags,         // memory flags in DD format
			   DWORD color_key_value, // default color key
			   int bpp)                // bits per pixel
{
	theBOB_ = new BOB();
	if (!Create_BOB(theBOB_,x,y,width,height,num_frames,attr, mem_flags,color_key_value,bpp))
	{
		throw "Unable to create BOB";
	}
}


BlitterObject::~BlitterObject()
{
	::Destroy_BOB(theBOB_);
	delete theBOB_;
}

int BlitterObject::Load_Frame(BITMAP_FILE_PTR bitmap, int frame, int cx,int cy,int mode)
{
	return ::Load_Frame_BOB(theBOB_,bitmap, frame, cx, cy, mode);
}

int BlitterObject::Load_Frame(IDirectDrawSurface7 * dds, int frame, int cx,int cy,int mode)
{
	return ::Load_Frame_BOB(theBOB_,dds, frame, cx, cy, mode);
}




int BlitterObject::Set_Animation(int anim_index)
{
	return ::Set_Animation_BOB(theBOB_, anim_index);
}

int BlitterObject::Set_Anim_Speed(int speed)
{
	return ::Set_Anim_Speed_BOB(theBOB_, speed);
}


int BlitterObject::Set_Vel(int xv, int yv)
{
	return ::Set_Vel_BOB(theBOB_, xv, yv);
}


int BlitterObject::Set_Pos(int x, int y)
{
	return ::Set_Pos_BOB(theBOB_, x, y);
}


int BlitterObject::Load_Animation(
				   int anim_index, 
				   int num_frames, 
				   int *sequence)
{
	return ::Load_Animation_BOB(theBOB_, anim_index, num_frames, sequence);
}



int BlitterObject::Animate()
{
	return ::Animate_BOB(theBOB_);
}

int BlitterObject::Draw(LPDIRECTDRAWSURFACE7 dest)
{
//	return ::Draw_BOB(theBOB_,dest);
	return ::Draw_BOB_To_Relative_Coordinates(theBOB_,dest, Universe::GetMapLeftX(), Universe::GetMapTopY() );
}



BlitterObject * BlitterObject::Clone()
{

	
	BOB * newBob = new BOB();
	Clone_BOB(theBOB_, newBob );


	BlitterObject * newBlitter = new BlitterObject(newBob);
	return newBlitter;




}

