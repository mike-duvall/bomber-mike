#include "Playing.h"


#include "../t3dlib/t3dlib1.h"

#include "../gameobjects/SimpleGameObject.h"


#include "../universe/Universe.h"
#include "../bob/BlitterObject.h"

#include <iostream>
#include <sstream>
using namespace std;

extern Player * thePlayer;








void Playing::Update()
{
	DWORD backgroundColor = _RGB32BIT(0,0,107,0);
	// clear the drawing surface
	DDraw_Fill_Surface(lpddsback,backgroundColor );

	thePlayer->Update();
	thePlayer->Draw(lpddsback);

	DDraw_Flip();

}
