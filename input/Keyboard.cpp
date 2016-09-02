#include "Keyboard.h"



#include "../gameobjects/ControlEvent.h"

Keyboard::Keyboard(LPDIRECTINPUT8 lpdi,HWND main_window_handle)
{
	if (lpdi->CreateDevice(GUID_SysKeyboard, &lpdikey, NULL)!=DI_OK)
	{
		throw "Error initializing keyboard";
	}


	// set cooperation level
	if (lpdikey->SetCooperativeLevel(main_window_handle, 
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)!=DI_OK)
	{
		throw "Error initializing keyboard";
	}


	if (lpdikey->SetDataFormat(&c_dfDIKeyboard)!=DI_OK)
	{
		throw "Error initializing keyboard";
	}


	if (lpdikey->Acquire()!=DI_OK)
	{
		throw "Error initializing keyboard";
	}


}

UCHAR *  Keyboard::GetKey()
{
	lpdikey->GetDeviceState(256, (LPVOID)keyboard_state);
	return keyboard_state;
}



int Keyboard::GetControlEvent()
{
	UCHAR * keyboard_state = this->GetKey();

	int controlEvent = CONTROL_EVENT_DO_NOTHING;
 
	if(keyboard_state[DIK_UP])
	{
		controlEvent = CONTROL_EVENT_MOVE_NORTH;
	}
	else
	if( keyboard_state[DIK_RIGHT] )
	{
		controlEvent = CONTROL_EVENT_MOVE_EAST;
	}
	else
	if( keyboard_state[DIK_DOWN] )
	{
		controlEvent = CONTROL_EVENT_MOVE_SOUTH;
	}
	else
	if( keyboard_state[DIK_LEFT] )
	{
		controlEvent = CONTROL_EVENT_MOVE_WEST;
	}

	return controlEvent;


}



bool Keyboard::IsDropBombPressed()
{

	return (bool)keyboard_state[DIK_SPACE];
}

 


Keyboard::~Keyboard()
{
	lpdikey->Unacquire();
	lpdikey->Release();

}