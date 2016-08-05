#ifndef BLITTEROBJECT_H
#define BLITTEROBJECT_H

#include "../t3dlib/t3dlib1.h"

class BlitterObject
{



public:

	BlitterObject(BOB * aBob){ theBOB_ = aBob;};
	BlitterObject(
		int x, int y,          // initial posiiton
		int width, int height, // size of bob
		int num_frames,        // number of frames
		int attr,              // attrs
		int mem_flags=0,         // memory flags in DD format
		DWORD color_key_value=0, // default color key
		int bpp=8);               // bits per pixel


	virtual ~BlitterObject();


	BlitterObject * Clone();

    int Load_Frame(BITMAP_FILE_PTR bitmap, int frame, int cx,int cy,int mode);              
	int Load_Frame(IDirectDrawSurface7 * dds, int frame, int cx,int cy,int mode);

	int Set_Animation(int anim_index);
	int Set_Anim_Speed(int speed);

	int Set_Vel(int xv, int yv);
	int Set_Pos(int x, int y);

	int Load_Animation(
			int anim_index, 
			int num_frames, 
			int *sequence);


	void IncrementX(int amount) { theBOB_->x += amount; }
	void IncrementY(int amount) { theBOB_->y += amount; }


	int Get_Current_Animation() { return theBOB_->curr_animation; };
	int Animate();

	int GetX() { return theBOB_->x; }
	int GetY() { return theBOB_->y; }
	int GetWidth() { return theBOB_->width; }
	int GetHeight() { return theBOB_->height; }

	int Draw(LPDIRECTDRAWSURFACE7 dest);


	BOB * getTheBOB() { return theBOB_; }



private:
	BOB * theBOB_;
};

#endif
