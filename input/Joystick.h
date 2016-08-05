#ifndef JOYSTICK_H
#define JOYSTICK_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include <vector>

using namespace std;


class Joystick;

typedef vector<Joystick *> JOYSTICK_VECTOR;


#define POV_NORTH 0
#define POV_NORTH_EAST  4500
#define POV_EAST  9000
#define POV_SOUTH_EAST  13500
#define POV_SOUTH  18000
#define POV_SOUTH_WEST  22500
#define POV_WEST  27000
#define POV_NORTH_WEST  31500


#include "Controller.h"

class Joystick : public Controller
{
public:
	Joystick(LPDIRECTINPUT8 lpdi,HWND main_window_handle, GUID joystickGUID);
	DIJOYSTATE GetJoystickState();
	boolean IsJoystickAttached() { return joystickAttached; }

	virtual ~Joystick();

	int GetControlEvent();
	bool IsDropBombPressed();

	static void InitializeJoysticks(LPDIRECTINPUT8 lpdi,HWND main_window_handle);
	static GUID joystick_GUID_Array[10];
	static int numJoysticks;
	static JOYSTICK_VECTOR allAttachedJoysticks;


private:
	LPDIRECTINPUTDEVICE8 lpdijoy;
	//		GUID joystickGUID;
	//		GUID joystickGUID2;

	DIJOYSTATE joy_state;
	boolean joystickAttached;





public:
};

#endif
