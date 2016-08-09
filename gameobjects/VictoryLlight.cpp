#include "VictoryLight.h"


#include "../main/Globals.h"

#include "../t3dlib/t3dlib1.h"
#include "../t3dlib/ddutil.h"
#include "../bob/BlitterObject.h"
#include "../universe/Universe.h"


#include <iostream>
#include <sstream>
using namespace std;


BlitterObject * VictoryLight::theBlueArchetypeBlitterObject_ = 0;
BlitterObject * VictoryLight::theRedArchetypeBlitterObject_ = 0;
BlitterObject * VictoryLight::theGreenArchetypeBlitterObject_ = 0;
BlitterObject * VictoryLight::theOrangeArchetypeBlitterObject_ = 0;

VictoryLight::VictoryLight(int x, int y, int color  )
{

	countdownTimerInitialValue = 10;
	countdownTimer = countdownTimerInitialValue;
	if(theBlueArchetypeBlitterObject_ == 0)
	{

		SetupArchetypes();
	}

	switch(color)
	{
	case VICTORY_LIGHT_COLOR_BLUE:
		theBlitterObject_ = theBlueArchetypeBlitterObject_->Clone();
		break;


	case VICTORY_LIGHT_COLOR_RED:
		theBlitterObject_ = theRedArchetypeBlitterObject_->Clone();
		break;

	case VICTORY_LIGHT_COLOR_GREEN:
		theBlitterObject_ = theGreenArchetypeBlitterObject_->Clone();
		break;

	case VICTORY_LIGHT_COLOR_ORANGE:
		theBlitterObject_ = theOrangeArchetypeBlitterObject_->Clone();
		break;

	}

	theBlitterObject_->Set_Pos(x,y);
	theBlitterObject_->Set_Anim_Speed(30);


}


//#define NUM_FRAMES_PER_ANIMATION 4



void VictoryLight::SetupArchetypes()
{
	int width = 12;
	int height = 12;


	theBlueArchetypeBlitterObject_ = new BlitterObject(0,0,width,height,2,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY, TRANSPARENT_COLOR_KEY);

	theRedArchetypeBlitterObject_ = new BlitterObject(0,0,width,height,2,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY, TRANSPARENT_COLOR_KEY);

	theGreenArchetypeBlitterObject_ = new BlitterObject(0,0,width,height,2,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY, TRANSPARENT_COLOR_KEY);

	theOrangeArchetypeBlitterObject_ = new BlitterObject(0,0,width,height,2,
		BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_VIDEOMEMORY, TRANSPARENT_COLOR_KEY);



	string blueFilename = string("bitmaps/EndOfRound/BlueLight.bmp");
	string redFilename = string("bitmaps/EndOfRound/RedLight.bmp");
	string greenFilename = string("bitmaps/EndOfRound/GreenLight.bmp");
	string orangeFilename = string("bitmaps/EndOfRound/OrangeLight.bmp");

	{
	int blueAnimations[] = {0,1,0,0,1};
	IDirectDrawSurface7 * blueDds = DDLoadBitmap(lpdd, blueFilename.c_str(), 0, 0 );
	if (blueDds == 0)
	{
		throw "Could not load bitmap";
	}

	theBlueArchetypeBlitterObject_->Load_Frame(blueDds,0,0,0,BITMAP_EXTRACT_MODE_CELL);  
	theBlueArchetypeBlitterObject_->Load_Frame(blueDds,1,1,0,BITMAP_EXTRACT_MODE_CELL);  
	Unload_Bitmap_File(&bitmap8bit);
	theBlueArchetypeBlitterObject_->Load_Animation(0,5,blueAnimations);
	theBlueArchetypeBlitterObject_->Set_Animation( 0);
	theBlueArchetypeBlitterObject_->Set_Anim_Speed(1);
	theBlueArchetypeBlitterObject_->Set_Vel(0,0);
	}


	{
	int redAnimations[] = {0,1,0,0,0,1};
	IDirectDrawSurface7 * redDds = DDLoadBitmap(lpdd, redFilename.c_str(), 0, 0 );
	if (redDds == 0)
	{
		throw "Could not load bitmap";
	}


	theRedArchetypeBlitterObject_->Load_Frame(redDds,0,0,0,BITMAP_EXTRACT_MODE_CELL);  
	theRedArchetypeBlitterObject_->Load_Frame(redDds,1,1,0,BITMAP_EXTRACT_MODE_CELL);  
	Unload_Bitmap_File(&bitmap8bit);
	theRedArchetypeBlitterObject_->Load_Animation(0,6,redAnimations);
	theRedArchetypeBlitterObject_->Set_Animation( 0);
	theRedArchetypeBlitterObject_->Set_Anim_Speed(1);
	theRedArchetypeBlitterObject_->Set_Vel(0,0);
	}

	{
	int greenAnimations[] = {0,0,1,0,0,1,};
	IDirectDrawSurface7 * greenDds = DDLoadBitmap(lpdd, greenFilename.c_str(), 0, 0 );
	if (greenDds == 0)
	{
		throw "Could not load bitmap";
	}

	theGreenArchetypeBlitterObject_->Load_Frame(greenDds,0,0,0,BITMAP_EXTRACT_MODE_CELL);  
	theGreenArchetypeBlitterObject_->Load_Frame(greenDds,1,1,0,BITMAP_EXTRACT_MODE_CELL);  
	Unload_Bitmap_File(&bitmap8bit);
	theGreenArchetypeBlitterObject_->Load_Animation(0,6,greenAnimations);
	theGreenArchetypeBlitterObject_->Set_Animation( 0);
	theGreenArchetypeBlitterObject_->Set_Anim_Speed(1);
	theGreenArchetypeBlitterObject_->Set_Vel(0,0);
	}

	{
	int orangeAnimations[] = {1,0,0,1,0,0,1,0};
	IDirectDrawSurface7 * orangeDds = DDLoadBitmap(lpdd, orangeFilename.c_str(), 0, 0 );
	if (orangeDds == 0)
	{
		throw "Could not load bitmap";
	}


	theOrangeArchetypeBlitterObject_->Load_Frame(orangeDds,0,0,0,BITMAP_EXTRACT_MODE_CELL);  
	theOrangeArchetypeBlitterObject_->Load_Frame(orangeDds,1,1,0,BITMAP_EXTRACT_MODE_CELL);  
	Unload_Bitmap_File(&bitmap8bit);
	theOrangeArchetypeBlitterObject_->Load_Animation(0,8,orangeAnimations);
	theOrangeArchetypeBlitterObject_->Set_Animation( 0);
	theOrangeArchetypeBlitterObject_->Set_Anim_Speed(1);
	theOrangeArchetypeBlitterObject_->Set_Vel(0,0);
	}

}


void  VictoryLight::Update()
{
// 	if(countdownTimer < 0)
// 	{
// 		countdownTimer = countdownTimerInitialValue;
// 		int currentAnimation = theBlitterObject_->Get_Current_Animation();
// 		if(currentAnimation == 0)
// 		{
// 
// 			theBlitterObject_->Set_Animation(1);
// 		}
// 		else
// 		{
// 			theBlitterObject_->Set_Animation(0);
// 		}
//  
// 		theBlitterObject_->Animate();
// 
// 	}
// 	countdownTimer--;
	theBlitterObject_->Animate();
}


