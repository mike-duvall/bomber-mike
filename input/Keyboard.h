#ifndef KEYBOARD_H
#define KEYBOARD_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "Controller.h"

class Keyboard : public Controller
{
public:
	Keyboard(LPDIRECTINPUT8 lpdi,HWND main_window_handle);
	UCHAR *  GetKey();
	virtual ~Keyboard();

	int GetControlEvent();
	bool IsDropBombPressed();

	


private:
		LPDIRECTINPUTDEVICE8  lpdikey;
		UCHAR keyboard_state[256];

public:
};

#endif
