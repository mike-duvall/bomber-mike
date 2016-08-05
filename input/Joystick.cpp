#include "JoyStick.h"


char                 joyname[80];         // name of joystick
// boolean enumCalled = false;
// int numTimesCalled = 0;

GUID Joystick::joystick_GUID_Array[10];
int Joystick::numJoysticks = 0;
JOYSTICK_VECTOR Joystick::allAttachedJoysticks;

#include "../gameobjects/ControlEvent.h"

BOOL CALLBACK DInput_Enum_Joysticks(LPCDIDEVICEINSTANCE lppdi, LPVOID guid_ptr)
{
//	enumCalled = true;
	Joystick::joystick_GUID_Array[Joystick::numJoysticks] = lppdi->guidInstance;
	Joystick::numJoysticks++;
//	*(GUID*)guid_ptr = lppdi->guidInstance;

//	strcpy(joyname, (char *)lppdi->tszProductName);

// 	if(numTimesCalled == 1)
// 	{
// 
// 	}
// 
// 	numTimesCalled++;
	return(DIENUM_CONTINUE);
}


void Joystick::InitializeJoysticks(LPDIRECTINPUT8 lpdi,HWND main_window_handle)
{
	GUID dummyGUID;
	lpdi->EnumDevices(
		DI8DEVCLASS_GAMECTRL,
		DInput_Enum_Joysticks,
		&dummyGUID,
		DIEDFL_ATTACHEDONLY);

	for(int i = 0; i < Joystick::numJoysticks; i++)
	{
		Joystick * nextJoystick = new Joystick(lpdi,main_window_handle, Joystick::joystick_GUID_Array[i] );
		Joystick::allAttachedJoysticks.push_back(nextJoystick);

// 		GUID nextJoystickGuid = Joystick::joystick_GUID_Array[i];
// 		if(FAILED(lpdi->CreateDevice(nextJoystickGuid,&lpdijoy, NULL)))
// 		{
// 			throw "Error initializing joystick";
// 		}
// 
// 		if(FAILED(lpdijoy->SetCooperativeLevel(main_window_handle,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
// 		{
// 			throw "Error initializing joystick";
// 		}
// 
// 
// 		if(FAILED(lpdijoy->SetDataFormat(&c_dfDIJoystick)))
// 		{
// 			throw "Error initializing joystick";
// 		}
// 
// 
// 		if(FAILED(lpdijoy->Acquire()))
// 		{
// 			throw "Error initializing joystick";
// 		}


	}

}



Joystick::Joystick(LPDIRECTINPUT8 lpdi,HWND main_window_handle, GUID joystickGUID)
{

// 	joystickAttached = false;
// 
// 	lpdi->EnumDevices(
// 		DI8DEVCLASS_GAMECTRL,
// 		DInput_Enum_Joysticks,
// 		&joystickGUID,
// 		DIEDFL_ATTACHEDONLY);
// 
// 
// // 	if(enumCalled)
// // 	{
// 		joystickAttached = true;
		if(FAILED(lpdi->CreateDevice(joystickGUID,&lpdijoy, NULL)))
		{
			throw "Error initializing joystick";
		}

		if(FAILED(lpdijoy->SetCooperativeLevel(main_window_handle,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
		{
			throw "Error initializing joystick";
		}


		if(FAILED(lpdijoy->SetDataFormat(&c_dfDIJoystick)))
		{
			throw "Error initializing joystick";
		}


		if(FAILED(lpdijoy->Acquire()))
		{
			throw "Error initializing joystick";
		}

//	}



}


int Joystick::GetControlEvent()
{
	int controlEvent = CONTROL_EVENT_DO_NOTHING;
 	DWORD povState = -1;
 	DIJOYSTATE joy_state;

	joy_state.rgbButtons[0] = 0;

	joy_state = this->GetJoystickState();
	povState = joy_state.rgdwPOV[0];

	switch(povState)
	{
	case POV_NORTH:
		controlEvent = CONTROL_EVENT_MOVE_NORTH;
		break;
	case POV_NORTH_EAST:
		controlEvent = CONTROL_EVENT_MOVE_NORTH_EAST;
		break;
	case POV_EAST:
		controlEvent = CONTROL_EVENT_MOVE_EAST;
		break;
	case POV_SOUTH_EAST:
		controlEvent = CONTROL_EVENT_MOVE_SOUTH_EAST;
		break;
	case POV_SOUTH:
		controlEvent = CONTROL_EVENT_MOVE_SOUTH;
		break;
	case POV_SOUTH_WEST:
		controlEvent = CONTROL_EVENT_MOVE_SOUTH_WEST;
		break;
	case POV_WEST:
		controlEvent = CONTROL_EVENT_MOVE_WEST;
		break;
	case POV_NORTH_WEST:
		controlEvent = CONTROL_EVENT_MOVE_NORTH_WEST;
		break;

	}


	return controlEvent;

}



bool Joystick::IsDropBombPressed()
{
	return (joy_state.rgbButtons[0] != 0);
}





DIJOYSTATE Joystick::GetJoystickState()
{
	if(FAILED(lpdijoy->Poll()))
	{
		throw "Failed polling joystick";
	}


	lpdijoy->GetDeviceState(sizeof(DIJOYSTATE),&joy_state);

	return joy_state;

}


Joystick::~Joystick()
{
	if(IsJoystickAttached())
	{
		lpdijoy->Unacquire();
		lpdijoy->Release();
	}

}