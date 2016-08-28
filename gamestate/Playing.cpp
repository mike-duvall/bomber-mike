#include "Playing.h"


#include "../t3dlib/t3dlib1.h"

#include "../gameobjects/SimpleGameObject.h"


#include "../universe/Universe.h"
#include "../bob/BlitterObject.h"

#include <iostream>
#include <sstream>
using namespace std;

extern Player * thePlayer;

Playing::Playing()
{

}


Playing::~Playing()
{
}




void Update_And_Draw_Players()
{
	thePlayer->Update();
	thePlayer->Draw(lpddsback);
}





void Playing::Update()
{
	DWORD backgroundColor = _RGB32BIT(0,0,107,0);
	// clear the drawing surface
	DDraw_Fill_Surface(lpddsback,backgroundColor );

	Update_And_Draw_Players();

	DDraw_Flip();


}
