#include "ControllerSelector.h"



#include "../t3dlib/ddutil.h"
//#include "../bob/BlitterObject.h"
#include "../gameobjects/SimpleGameObject.h"



ControllerSelector::ControllerSelector(int x, int y)
{

	selection = CONTROLLER_COMPUTER;

	computerSelection = new SimpleGameObject(x,y,78,30, "bitmaps/PickControl/Computer.bmp");
	gamepadSelection  = new SimpleGameObject(x,y,78,30, "bitmaps/PickControl/GamePad.bmp");
	keyboardSelection  = new SimpleGameObject(x,y,78,30, "bitmaps/PickControl/Keyboard.bmp");


}



void ControllerSelector::Draw(LPDIRECTDRAWSURFACE7 dest)
{
	switch(selection)
	{
	case CONTROLLER_COMPUTER:
		computerSelection->Draw(dest);
		break;

	case CONTROLLER_GAMEPAD:
		gamepadSelection->Draw(dest);
		break;

	case CONTROLLER_KEYBOARD:
		keyboardSelection->Draw(dest);
		break;

	}
}



ControllerSelector::~ControllerSelector()
{


}